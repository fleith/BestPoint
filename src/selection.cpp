#include "selection.h"
#include <stdlib.h>
#include <algorithm>
#include "ga_utils.h"

////////////////////////////////////////////////////////////////////////////////

Selection::Selection(Fitness fitness) : fitness(fitness) {}

////////////////////////////////////////////////////////////////////////////////

// Truncation Selection (Mühlenbein & Schlierkamp-Voosen, 1993):
// Keep the top 1/3 deterministically; fill the rest by random re-sampling.
Population Selection::ByTruncation(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    int topThird = individuals.size() / 3;

    std::vector<Chromosome> selected;
    selected.insert(selected.end(),
                    individuals.begin(),
                    individuals.begin() + topThird);

    while (selected.size() != individuals.size()) {
        int idx = rand() % individuals.size();
        selected.push_back(individuals.at(idx));
    }

    return Population(selected);
}

////////////////////////////////////////////////////////////////////////////////

// Elitist Replacement: sort population, replace the bottom 5% with copies
// of the top 5%.  A replacement strategy rather than a full selection method.
Population Selection::ByElitistReplacement(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    int bottomFive = individuals.size() / 20;

    std::vector<Chromosome> selected;
    selected.insert(selected.end(),
                    individuals.begin(),
                    individuals.end() - bottomFive);

    selected.insert(selected.end(),
                    individuals.begin(),
                    individuals.begin() + bottomFive);

    return Population(selected);
}

////////////////////////////////////////////////////////////////////////////////

Population Selection::ByRank(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    int linearSum = GAUtils::RankSum(population);

    std::vector<Chromosome> selected;
    while (selected.size() != individuals.size()) {
        int pick        = rand() % linearSum;
        int accumulated = 0;
        for (std::vector<Chromosome>::iterator it = individuals.begin(); it != individuals.end(); it++) {
            accumulated += (individuals.end() - it);
            if (pick < accumulated) {
                selected.push_back(*it);
                break;
            }
        }
    }

    return Population(selected);
}

////////////////////////////////////////////////////////////////////////////////

// Hybrid Selection: combines Truncation Selection and Fitness-Proportionate
// Selection (FPS).  The top 1/3 are preserved deterministically (truncation);
// the remaining 2/3 are drawn by roulette-wheel from the full sorted pool.
Population Selection::ByHybrid(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    int topThird = static_cast<int>(individuals.size()) / 3;

    // Phase 1 — truncation: keep elite survivors
    std::vector<Chromosome> selected;
    selected.insert(selected.end(),
                    individuals.begin(),
                    individuals.begin() + topThird);

    // Phase 2 — roulette-wheel: fill the rest proportional to fitness
    std::vector<double> fitnessCache;
    fitnessCache.reserve(individuals.size());
    for (std::vector<Chromosome>::iterator it = individuals.begin(); it != individuals.end(); it++)
        fitnessCache.push_back(fitness.Evaluate(*it));

    const int scale = 100000;
    double totalFitness = 0;
    for (std::vector<double>::iterator it = fitnessCache.begin(); it != fitnessCache.end(); it++)
        totalFitness += *it;
    totalFitness *= scale;

    while (selected.size() != individuals.size()) {
        int pick    = rand() % static_cast<int>(totalFitness);
        int running = 0;
        for (std::vector<Chromosome>::size_type i = 0; i < individuals.size(); i++) {
            running += static_cast<int>(fitnessCache[i] * scale);
            if (pick < running) {
                selected.push_back(individuals[i]);
                break;
            }
        }
    }

    return Population(selected);
}

////////////////////////////////////////////////////////////////////////////////

Population Selection::ByRoulette(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    std::vector<double> fitnessCache;
    fitnessCache.reserve(individuals.size());
    for (std::vector<Chromosome>::iterator it = individuals.begin(); it != individuals.end(); it++)
        fitnessCache.push_back(fitness.Evaluate(*it));

    const int scale = 100000;
    double totalFitness = 0;
    for (std::vector<double>::iterator it = fitnessCache.begin(); it != fitnessCache.end(); it++)
        totalFitness += *it;
    totalFitness *= scale;

    std::vector<Chromosome> selected;
    while (selected.size() != individuals.size()) {
        int pick    = rand() % static_cast<int>(totalFitness);
        int running = 0;
        for (std::vector<Chromosome>::size_type i = 0; i < individuals.size(); i++) {
            running += fitnessCache[i] * scale;
            if (pick < running) {
                selected.push_back(individuals[i]);
                break;
            }
        }
    }

    return Population(selected);
}
