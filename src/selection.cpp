#include "selection.h"
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>
#include "ga_utils.h"

// Seed from the application's random source; sample without integer scaling.
static std::vector<double> selectionWeights(const std::vector<Chromosome>& individuals, Fitness& fitness)
{
    std::vector<double> weights;
    double largest = 0.0;
    for (const Chromosome& individual : individuals) {
        double weight = fitness.Evaluate(individual);
        if (!std::isfinite(weight) || weight < 0.0)
            throw std::invalid_argument("selection requires finite, nonnegative fitness");
        weights.push_back(weight);
        largest = std::max(largest, weight);
    }
    // Normalization prevents overflow in the distribution's sum.
    for (double& weight : weights) weight = largest > 0.0 ? weight / largest : 1.0;
    return weights;
}

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
    std::vector<double> weights = selectionWeights(individuals, fitness);
    std::mt19937 engine(static_cast<unsigned>(rand()));
    std::discrete_distribution<size_t> pick(weights.begin(), weights.end());
    while (selected.size() < individuals.size())
        selected.push_back(individuals[pick(engine)]);

    return Population(selected);
}

////////////////////////////////////////////////////////////////////////////////

Population Selection::ByRoulette(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    std::vector<double> weights = selectionWeights(individuals, fitness);
    std::mt19937 engine(static_cast<unsigned>(rand()));
    std::discrete_distribution<size_t> pick(weights.begin(), weights.end());
    std::vector<Chromosome> selected;
    while (selected.size() < individuals.size())
        selected.push_back(individuals[pick(engine)]);

    return Population(selected);
}

