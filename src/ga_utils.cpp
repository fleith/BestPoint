#include "ga_utils.h"
#include "crossover.h"
#include <stdlib.h>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

double GAUtils::BestFitness(Population& pop, Fitness& fit)
{
    if (pop.individuals.empty()) return 0;
    std::vector<Chromosome>& individuals = pop.individuals;
    std::sort(individuals.begin(), individuals.end(), fit);
    return fit.Evaluate(individuals.front());
}

////////////////////////////////////////////////////////////////////////////////

double GAUtils::WorstFitness(Population& pop, Fitness& fit)
{
    if (pop.individuals.empty()) return 0;
    std::vector<Chromosome>& individuals = pop.individuals;
    std::sort(individuals.begin(), individuals.end(), fit);
    return fit.Evaluate(individuals.back());
}

////////////////////////////////////////////////////////////////////////////////

Chromosome GAUtils::RemoveAndReturnBest(Population& pop, Fitness& fit)
{
    if (pop.individuals.empty()) return Chromosome(0, 0);
    std::vector<Chromosome>& individuals = pop.individuals;
    std::sort(individuals.begin(), individuals.end(), fit);
    Chromosome best = individuals.front();
    individuals.erase(individuals.begin());
    return best;
}

////////////////////////////////////////////////////////////////////////////////

double GAUtils::AverageFitness(Population& pop, Fitness& fit)
{
    std::vector<Chromosome>& individuals = pop.individuals;
    double total = 0;
    for (std::vector<Chromosome>::iterator it = individuals.begin(); it != individuals.end(); it++)
        total += fit.Evaluate(*it);
    return total / individuals.size();
}

////////////////////////////////////////////////////////////////////////////////

double GAUtils::TotalFitness(Population& pop, Fitness& fit)
{
    std::vector<Chromosome>& individuals = pop.individuals;
    double total = 0;
    for (std::vector<Chromosome>::iterator it = individuals.begin(); it != individuals.end(); it++)
        total += fit.Evaluate(*it);
    return total;
}

////////////////////////////////////////////////////////////////////////////////

static int rankSum(int n)
{
    return n ? n + rankSum(n - 1) : 0;
}

int GAUtils::RankSum(Population& pop)
{
    return rankSum(pop.Size());
}

////////////////////////////////////////////////////////////////////////////////

Chromosome GAUtils::Best(Population& pop, Fitness& fit)
{
    std::vector<Chromosome>& individuals = pop.individuals;
    std::sort(individuals.begin(), individuals.end(), fit);
    return individuals.front();
}

////////////////////////////////////////////////////////////////////////////////

Chromosome GAUtils::Worst(Population& pop, Fitness& fit)
{
    std::vector<Chromosome>& individuals = pop.individuals;
    std::sort(individuals.begin(), individuals.end(), fit);
    return individuals.back();
}

////////////////////////////////////////////////////////////////////////////////

void GAUtils::ReplaceWithElite(Population& crossed, Population& elite, Fitness& fit)
{
    std::vector<Chromosome>& individuals = crossed.individuals;
    std::sort(individuals.begin(), individuals.end(), fit);
    int midpoint = static_cast<int>(individuals.size() / 2);
    individuals.erase(individuals.begin() + midpoint);
    std::vector<Chromosome>& elites = elite.individuals;
    if (!elites.empty()) individuals.push_back(elites.front());
}

////////////////////////////////////////////////////////////////////////////////

Point GAUtils::RandomPoint(int minX, int maxX, int minY, int maxY)
{
    int x = (rand() % (maxX - minX)) + minX;
    int y = (rand() % (maxY - minY)) + minY;
    return Point(x, y);
}

////////////////////////////////////////////////////////////////////////////////

Chromosome GAUtils::RandomIndividual(int minX, int maxX, int minY, int maxY)
{
    int x = (rand() % (maxX - minX)) + minX;
    int y = (rand() % (maxY - minY)) + minY;
    return Chromosome(x, y);
}
