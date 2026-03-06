#include "Selection.h"
#include <stdlib.h>
#include <algorithm>
#include "GAUtils.h"

////////////////////////////////////////////////////////////////////////////////

Selection::Selection(Fitness fitness) : fitness(fitness) {}

////////////////////////////////////////////////////////////////////////////////

Population Selection::ByElitism(Population population)
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

Population Selection::BySteadyState(Population population)
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

    int linearSum = GAUtils::LinearSum(population);

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

Population Selection::Hybrid(Population population)
{
    std::vector<Chromosome>& individuals = population.individuals;
    std::sort(individuals.begin(), individuals.end(), fitness);

    int topThird = individuals.size() / 3;

    std::vector<Chromosome> selected;
    selected.insert(selected.end(),
                    individuals.begin(),
                    individuals.begin() + topThird);

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
