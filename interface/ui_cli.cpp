#include "ui.h"
#include "cli_config.h"
#include "app.h"

#include <cstdio>

static int generationNumber = 0;

// ---------------------------------------------------------------------------
// Chart / drawing — no-ops in CLI
// ---------------------------------------------------------------------------

void UI::AddFitnessStats(double best, double worst, double avg)
{
    generationNumber++;
    std::printf("  Gen %4d/%d  |  best=%10.4f  worst=%10.4f  avg=%10.4f\n",
        generationNumber, cliConfig.maxGenerations, best, worst, avg);
}

void UI::ClearFitnessChart()                     { generationNumber = 0; }
void UI::ClearCanvas()                           {}
void UI::DrawBasePoint(double, double)           {}
void UI::DrawIndividual(double, double)          {}
void UI::DrawBestIndividual(double, double)      {}
void UI::DrawWorstIndividual(double, double)     {}

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
