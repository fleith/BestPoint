#include "app.h"

////////////////////////////////////////////////////////////////////////////////
App app;
////////////////////////////////////////////////////////////////////////////////

#include "ga_utils.h"
#include "selection.h"
#include "crossover.h"
#include "ui.h"

////////////////////////////////////////////////////////////////////////////////

App::~App() {}

App::App() : configValid(false) {}

////////////////////////////////////////////////////////////////////////////////

void App::CMDInit()
{
    maxX = UI::MaxX();
    maxY = UI::MaxY();
    minX = UI::MinX();
    minY = UI::MinY();

    populationSize = UI::PopulationSize();
    maxGenerations = UI::MaxGenerations();
    crossoverRate  = UI::CrossoverRate();
    mutationRate   = UI::MutationRate();

    fitness.SetDistanceFactor(UI::DistanceFactor());
    fitness.SetDistributionFactor(UI::DistributionFactor());
    double normRange = (maxX - minX) + (maxY - minY);
    fitness.SetNormalizer(normRange);

    ValidateConfig();
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDGeneratePopulationAuto()
{
    if (!configValid) return;

    Population initial;
    for (int i = 0; i < UI::PopulationSize(); i++)
        initial.Add(GAUtils::RandomIndividual(minX, maxX, minY, maxY));

    remainingGenerations = maxGenerations;
    populations.clear();
    populations.push_back(initial);
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDGeneratePopulationManual()
{
    if (!configValid) return;
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDRunOneGeneration()
{
    if (!configValid) return;
    if (remainingGenerations == 0) return;

    Step();
    UI::UpdateDisplay();
    remainingGenerations--;
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDRunTenGenerations()
{
    if (!configValid) return;
    for (int i = 0; i < 10; i++) CMDRunOneGeneration();
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDRunHundredGenerations()
{
    if (!configValid) return;
    for (int i = 0; i < 100; i++) CMDRunOneGeneration();
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDRunAllGenerations()
{
    if (!configValid) return;
    while (remainingGenerations > 0) CMDRunOneGeneration();
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDRenderPopulation()
{
    if (!configValid) return;

    UI::ClearCanvas();

    if (!populations.empty()) {
        Population& current = populations.back();
        for (int i = 0; i < current.Size(); i++) {
            int sx = ScaleX(current[i].X());
            int sy = ScaleY(current[i].Y());
            UI::DrawIndividual(sx, sy);
        }

        if (current.Size()) {
            Chromosome worst = GAUtils::Worst(populations.back(), fitness);
            UI::DrawWorstIndividual(ScaleX(worst.X()), ScaleY(worst.Y()));

            Chromosome best = GAUtils::Best(populations.back(), fitness);
            UI::DrawBestIndividual(ScaleX(best.X()), ScaleY(best.Y()));
        }
    }

    for (int i = 0; i < fitness.PointCount(); i++)
        UI::DrawBasePoint(ScaleX(fitness[i].X()), ScaleY(fitness[i].Y()));
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDRenderFitnessStats()
{
    if (!configValid) return;

    Population& current = populations.back();
    if (current.Size()) {
        double bestFit  = GAUtils::BestFitness(current, fitness);
        double worstFit = GAUtils::WorstFitness(current, fitness);
        double avgFit   = GAUtils::AverageFitness(current, fitness);
        UI::AddFitnessStats(bestFit, worstFit, avgFit);
    }
}

////////////////////////////////////////////////////////////////////////////////

void App::CMDGenerateBasePoints()
{
    if (!configValid) return;
    fitness.ClearPoints();
    for (int i = 0; i < UI::BasePointCount(); i++)
        fitness.AddPoint(GAUtils::RandomPoint(minX, maxX, minY, maxY));
}

////////////////////////////////////////////////////////////////////////////////

Chromosome App::CMDGetBest()
{
    if (populations.empty() || populations.back().Size() == 0)
        return Chromosome(0, 0);
    return GAUtils::Best(populations.back(), fitness);
}

int App::CMDGetBasePointCount()
{
    return fitness.PointCount();
}

Point App::CMDGetBasePoint(int i)
{
    return fitness[i];
}

////////////////////////////////////////////////////////////////////////////////

void App::ValidateConfig()
{
    configValid = true;
    if (maxX < minX)                              configValid = false;
    if (maxY < minY)                              configValid = false;
    if (populationSize <= 0)                      configValid = false;
    if (maxGenerations <= 0)                      configValid = false;
    if (crossoverRate < 0 || crossoverRate > 100) configValid = false;
    if (mutationRate  < 0 || mutationRate  > 100) configValid = false;
}

////////////////////////////////////////////////////////////////////////////////

int App::ScaleX(double x)
{
    const double canvasW = UI::CanvasWidth() - 6;
    int deltaX = maxX - minX;
    double scale = canvasW / deltaX;
    return static_cast<int>((x - minX) * scale + 3);
}

////////////////////////////////////////////////////////////////////////////////

int App::ScaleY(double y)
{
    const double canvasH = UI::CanvasHeight() - 6;
    int deltaY = maxY - minY;
    double scale = canvasH / deltaY;
    return static_cast<int>((y - minY) * scale + 3);
}

////////////////////////////////////////////////////////////////////////////////

void App::Step()
{
    Selection selection(fitness);
    SelectionMethod selMethod = UI::GetSelectionMethod();

    Chromosome elite(0, 0);
    Population selected;
    switch (selMethod) {
        case TRUNCATION:
            selected = selection.ByTruncation(populations.back());
            elite    = GAUtils::RemoveAndReturnBest(selected, fitness);
            break;
        case ROULETTE:
            selected = selection.ByRoulette(populations.back());
            break;
        case RANK:
            selected = selection.ByRank(populations.back());
            break;
        case ELITIST_REPLACEMENT:
            selected = selection.ByElitistReplacement(populations.back());
            break;
        case HYBRID:
            selected = selection.ByHybrid(populations.back());
            break;
    }

    Population crossed;
    if (UI::GetCrossoverMethod() == RANDOM)
        crossed = Crossover::CrossRandom(selected, crossoverRate, mutationRate);
    else
        crossed = Crossover::CrossSequential(selected, crossoverRate, mutationRate);

    if (selMethod == TRUNCATION) crossed.Add(elite);
    populations.back() = crossed;
}
