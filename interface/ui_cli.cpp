#include "ui.h"
#include "cli_config.h"
#include "app.h"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <utility>
#include <string>

static int generationNumber = 0;

// ---------------------------------------------------------------------------
// Per-generation snapshot for the HTML visualiser
// ---------------------------------------------------------------------------

struct GenSnapshot {
    std::vector<std::pair<double,double>> individuals;
    std::pair<double,double> best, worst;
    bool hasBest, hasWorst;
    double bestFitness, worstFitness, avgFitness;
    GenSnapshot()
        : best(0,0), worst(0,0), hasBest(false), hasWorst(false)
        , bestFitness(0), worstFitness(0), avgFitness(0) {}
};

static std::vector<GenSnapshot>              snapshots;
static GenSnapshot                           current;
static std::vector<std::pair<double,double>> basePoints;
static bool                                  basePointsDone = false;

// Reverse App::ScaleX / ScaleY to recover raw GA coordinates
static double unscaleX(double sx)
{
    double cw = UI::CanvasWidth() - 6.0;
    return (sx - 3.0) * (cliConfig.maxX - cliConfig.minX) / cw + cliConfig.minX;
}
static double unscaleY(double sy)
{
    double ch = UI::CanvasHeight() - 6.0;
    return (sy - 3.0) * (cliConfig.maxY - cliConfig.minY) / ch + cliConfig.minY;
}

// ---------------------------------------------------------------------------
// Chart / drawing
// ---------------------------------------------------------------------------

void UI::AddFitnessStats(double best, double worst, double avg)
{
    generationNumber++;
    std::printf("  Gen %4d/%d  |  best=%10.4f  worst=%10.4f  avg=%10.4f\n",
        generationNumber, cliConfig.maxGenerations, best, worst, avg);

    current.bestFitness  = best;
    current.worstFitness = worst;
    current.avgFitness   = avg;
    snapshots.push_back(current);
    current       = GenSnapshot();
    basePointsDone = true;          // base points are fixed after first render
}

void UI::ClearFitnessChart()
{
    generationNumber = 0;
    snapshots.clear();
    current        = GenSnapshot();
    basePoints.clear();
    basePointsDone = false;
}

void UI::ClearCanvas() {}

void UI::DrawBasePoint(double x, double y)
{
    if (!basePointsDone)
        basePoints.push_back(std::make_pair(unscaleX(x), unscaleY(y)));
}

void UI::DrawIndividual(double x, double y)
{
    current.individuals.push_back(std::make_pair(unscaleX(x), unscaleY(y)));
}

void UI::DrawBestIndividual(double x, double y)
{
    current.best    = std::make_pair(unscaleX(x), unscaleY(y));
    current.hasBest = true;
}

void UI::DrawWorstIndividual(double x, double y)
{
    current.worst    = std::make_pair(unscaleX(x), unscaleY(y));
    current.hasWorst = true;
}

// ---------------------------------------------------------------------------
// Config getters — read from CLIConfig
// ---------------------------------------------------------------------------

int    UI::CrossoverRate()      { return cliConfig.crossoverRate; }
int    UI::MutationRate()       { return cliConfig.mutationRate; }
int    UI::PopulationSize()     { return cliConfig.populationSize; }
int    UI::MaxGenerations()     { return cliConfig.maxGenerations; }
int    UI::MaxX()               { return cliConfig.maxX; }
int    UI::MaxY()               { return cliConfig.maxY; }
int    UI::MinX()               { return cliConfig.minX; }
int    UI::MinY()               { return cliConfig.minY; }
int    UI::BasePointCount()     { return cliConfig.basePointCount; }
double UI::DistanceFactor()     { return cliConfig.distanceFactor; }
double UI::DistributionFactor() { return cliConfig.distributionFactor; }
int    UI::CanvasWidth()        { return 500; }
int    UI::CanvasHeight()       { return 500; }

CrossoverMethod UI::GetCrossoverMethod() { return cliConfig.crossoverMethod; }
SelectionMethod UI::GetSelectionMethod() { return cliConfig.selectionMethod; }

// ---------------------------------------------------------------------------
// App commands
// ---------------------------------------------------------------------------

void UI::UpdateDisplay()
{
    app.CMDRenderPopulation();
    app.CMDRenderFitnessStats();
}

void UI::InitializeApp()            { app.CMDInit(); }
void UI::GeneratePopulationAuto()   { app.CMDGeneratePopulationAuto(); UI::ClearFitnessChart(); }
void UI::GeneratePopulationManual() { app.CMDGeneratePopulationManual(); }
void UI::RunOneGeneration()         { app.CMDRunOneGeneration(); }
void UI::RunTenGenerations()        { app.CMDRunTenGenerations(); }
void UI::RunHundredGenerations()    { app.CMDRunHundredGenerations(); }
void UI::RunAllGenerations()        { app.CMDRunAllGenerations(); }
void UI::GenerateBasePoints()       { app.CMDGenerateBasePoints(); }

// ---------------------------------------------------------------------------
// HTML visualiser
// ---------------------------------------------------------------------------

static std::string buildJson()
{
    std::ostringstream j;
    j << std::fixed << std::setprecision(4);

    j << "{\"bounds\":{\"minX\":" << cliConfig.minX << ",\"maxX\":" << cliConfig.maxX
      << ",\"minY\":" << cliConfig.minY << ",\"maxY\":" << cliConfig.maxY << "},";

    j << "\"basePoints\":[";
    for (size_t i = 0; i < basePoints.size(); i++) {
        if (i) j << ",";
        j << "[" << basePoints[i].first << "," << basePoints[i].second << "]";
    }
    j << "],\"generations\":[";

    for (size_t g = 0; g < snapshots.size(); g++) {
        if (g) j << ",";
        const GenSnapshot& s = snapshots[g];

        j << "{\"individuals\":[";
        for (size_t i = 0; i < s.individuals.size(); i++) {
            if (i) j << ",";
            j << "[" << s.individuals[i].first << "," << s.individuals[i].second << "]";
        }
        j << "]";
        j << ",\"best\":"  << (s.hasBest  ? "" : "null");
        if (s.hasBest)  j << "[" << s.best.first  << "," << s.best.second  << "]";
        j << ",\"worst\":" << (s.hasWorst ? "" : "null");
        if (s.hasWorst) j << "[" << s.worst.first << "," << s.worst.second << "]";
        j << ",\"bestFitness\":"  << s.bestFitness;
        j << ",\"worstFitness\":" << s.worstFitness;
        j << ",\"avgFitness\":"   << s.avgFitness;
        j << "}";
    }
    j << "]}";
    return j.str();
}

void WriteHtmlReport(const std::string& filename)
{
    std::string data = buildJson();

    // Single-file HTML — DATA placeholder is replaced with the JSON
    static const char HTML[] = R"HTMLEND(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>BestPoint GA Visualiser</title>
<style>
*{box-sizing:border-box;margin:0;padding:0}
body{background:#0d1117;color:#c9d1d9;font-family:'Segoe UI',system-ui,sans-serif;
     display:flex;flex-direction:column;align-items:center;padding:24px;gap:12px}
h1{font-size:1.25rem;color:#58a6ff;letter-spacing:.4px}
canvas{border:1px solid #30363d;border-radius:6px;display:block}
.row{display:flex;align-items:center;gap:10px;width:620px}
input[type=range]{flex:1;accent-color:#58a6ff;cursor:pointer}
button{background:#21262d;color:#c9d1d9;border:1px solid #30363d;
       border-radius:6px;padding:4px 14px;cursor:pointer;font-size:.82rem}
button:hover{background:#30363d}
.stats{display:flex;gap:20px;font-size:.82rem;color:#8b949e;flex-wrap:wrap;justify-content:center}
.gb{color:#3fb950;font-weight:600}.gw{color:#f85149}.ga{color:#d29922}.gp{color:#c9d1d9}
.legend{display:flex;gap:14px;font-size:.76rem;color:#8b949e}
.dot{display:inline-block;width:10px;height:10px;border-radius:50%;
     vertical-align:middle;margin-right:3px}
</style>
</head>
<body>
<h1>BestPoint &mdash; Genetic Algorithm Visualiser</h1>
<canvas id="main" width="620" height="520"></canvas>
<canvas id="chart" width="620" height="150"></canvas>
<div class="row">
  <button id="btn">&#9654; Play</button>
  <input type="range" id="slider" min="0" value="0" step="1">
  <span id="lbl" style="min-width:90px;text-align:right;font-size:.82rem">Gen 1 / ?</span>
</div>
<div class="stats">
  <span>Best fitness: <span class="gb" id="sb">&mdash;</span></span>
  <span>Worst: <span class="gw" id="sw">&mdash;</span></span>
  <span>Avg: <span class="ga" id="sa">&mdash;</span></span>
  <span>Best pos: <span class="gp" id="sp">&mdash;</span></span>
</div>
<div class="legend">
  <span><span class="dot" style="background:#f0a500"></span>Base point</span>
  <span><span class="dot" style="background:rgba(88,166,255,.6)"></span>Individual</span>
  <span><span class="dot" style="background:#3fb950"></span>Best</span>
  <span><span class="dot" style="background:#f85149"></span>Worst</span>
</div>
<script>
const D = /*DATA*/;

// ---- main canvas ----
const mc = document.getElementById('main'), mx = mc.getContext('2d');
const W = mc.width, H = mc.height, P = 44;

function tx(x){ return P + (x-D.bounds.minX)/(D.bounds.maxX-D.bounds.minX)*(W-2*P); }
function ty(y){ return H - P - (y-D.bounds.minY)/(D.bounds.maxY-D.bounds.minY)*(H-2*P); }

function dot(x,y,r,fill,stroke,lw){
  mx.beginPath(); mx.arc(tx(x),ty(y),r,0,2*Math.PI);
  mx.fillStyle=fill; mx.fill();
  if(stroke){ mx.strokeStyle=stroke; mx.lineWidth=lw||2; mx.stroke(); }
}

function drawGrid(){
  mx.strokeStyle='#21262d'; mx.lineWidth=1;
  mx.fillStyle='#6e7681'; mx.font='11px sans-serif';
  const steps=5;
  const dx=(D.bounds.maxX-D.bounds.minX)/steps, dy=(D.bounds.maxY-D.bounds.minY)/steps;
  mx.textAlign='center';
  for(let i=0;i<=steps;i++){
    const v=D.bounds.minX+i*dx, px=tx(v);
    mx.beginPath(); mx.moveTo(px,P); mx.lineTo(px,H-P); mx.stroke();
    mx.fillText(v.toFixed(0), px, H-P+16);
  }
  mx.textAlign='right';
  for(let i=0;i<=steps;i++){
    const v=D.bounds.minY+i*dy, py=ty(v);
    mx.beginPath(); mx.moveTo(P,py); mx.lineTo(W-P,py); mx.stroke();
    mx.fillText(v.toFixed(0), P-6, py+4);
  }
}

function renderMain(idx){
  mx.clearRect(0,0,W,H);
  drawGrid();
  const g = D.generations[idx];
  g.individuals.forEach(([x,y]) => dot(x,y,3,'rgba(88,166,255,.45)'));
  if(g.worst) dot(g.worst[0],g.worst[1],7,'rgba(248,81,73,.7)','#f85149');
  if(g.best)  dot(g.best[0], g.best[1], 9,'#3fb950','#2ea043',2);
  D.basePoints.forEach(([x,y]) => dot(x,y,10,'#f0a500','#d4870d',2));
  document.getElementById('lbl').textContent = `Gen ${idx+1} / ${D.generations.length}`;
  document.getElementById('sb').textContent  = g.bestFitness.toFixed(4);
  document.getElementById('sw').textContent  = g.worstFitness.toFixed(4);
  document.getElementById('sa').textContent  = g.avgFitness.toFixed(4);
  document.getElementById('sp').textContent  = g.best
    ? `(${g.best[0].toFixed(1)}, ${g.best[1].toFixed(1)})` : '—';
}

// ---- fitness chart ----
const cc = document.getElementById('chart'), cx = cc.getContext('2d');
const CW = cc.width, CH = cc.height, CP = 24;

let minF=Infinity, maxF=-Infinity;
D.generations.forEach(g=>{
  minF=Math.min(minF,g.worstFitness);
  maxF=Math.max(maxF,g.bestFitness);
});
const fRange = maxF-minF || 1;
function fy(f){ return CH-CP-(f-minF)/fRange*(CH-2*CP); }
function fx(i){ return CP + i/(D.generations.length-1||1)*(CW-2*CP); }

function drawChart(curIdx){
  cx.clearRect(0,0,CW,CH);
  cx.fillStyle='#161b22'; cx.fillRect(0,0,CW,CH);
  // grid lines
  cx.strokeStyle='#21262d'; cx.lineWidth=1;
  for(let i=0;i<=4;i++){
    const y=CP+i*(CH-2*CP)/4;
    cx.beginPath(); cx.moveTo(CP,y); cx.lineTo(CW-CP,y); cx.stroke();
  }
  // series
  const series=[
    {key:'worstFitness',color:'rgba(248,81,73,.55)',lw:1.5},
    {key:'avgFitness',  color:'rgba(210,153,34,.8)', lw:1.5},
    {key:'bestFitness', color:'#3fb950',             lw:2},
  ];
  series.forEach(({key,color,lw})=>{
    cx.beginPath();
    D.generations.forEach((g,i)=>{
      i===0 ? cx.moveTo(fx(i),fy(g[key])) : cx.lineTo(fx(i),fy(g[key]));
    });
    cx.strokeStyle=color; cx.lineWidth=lw; cx.stroke();
  });
  // labels
  cx.fillStyle='#6e7681'; cx.font='10px sans-serif';
  cx.textAlign='left';  cx.fillText('Fitness', CP, CP-6);
  cx.textAlign='right';
  cx.fillText(maxF.toFixed(2), CW-CP, CP+10);
  cx.fillText(minF.toFixed(2), CW-CP, CH-CP+2);
  // cursor line
  if(curIdx !== undefined){
    const x = fx(curIdx);
    cx.strokeStyle='rgba(255,255,255,.25)'; cx.lineWidth=1;
    cx.beginPath(); cx.moveTo(x,CP); cx.lineTo(x,CH-CP); cx.stroke();
  }
}

function render(idx){
  renderMain(idx);
  drawChart(idx);
}

// ---- controls ----
const slider = document.getElementById('slider');
slider.max = D.generations.length - 1;
slider.addEventListener('input', () => render(+slider.value));

let playing=false, timer=null;
const btn = document.getElementById('btn');
btn.addEventListener('click', ()=>{
  playing = !playing;
  btn.textContent = playing ? '\u23F8 Pause' : '\u25B6 Play';
  if(playing){
    timer = setInterval(()=>{
      let v = +slider.value + 1;
      if(v >= D.generations.length) v = 0;
      slider.value = v; render(v);
    }, 80);
  } else {
    clearInterval(timer);
  }
});

render(0);
</script>
</body>
</html>
)HTMLEND";

    // Inject JSON data
    std::string html(HTML);
    const std::string marker = "/*DATA*/";
    size_t pos = html.find(marker);
    if (pos != std::string::npos)
        html.replace(pos, marker.size(), data);

    std::ofstream out(filename.c_str());
    if (!out) {
        std::fprintf(stderr, "error: cannot write '%s'\n", filename.c_str());
        return;
    }
    out << html;
    std::printf("  HTML report  : %s\n", filename.c_str());
}
