#include "crossover.h"
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include "mutation.h"

////////////////////////////////////////////////////////////////////////////////

Population Crossover::CrossRandom(Population pop, int crossoverRate, int mutationRate)
{
    Population newPop;

    while (pop.Size()) {
        int roll = rand() % 101;

        Chromosome parentA = pop.individuals.front();
        pop.individuals.erase(pop.individuals.begin());

        if (pop.Size()) {
            int idx = rand() % pop.individuals.size();
            Chromosome parentB = pop.individuals.at(idx);
            pop.individuals.erase(pop.individuals.begin() + idx);

            if (roll < crossoverRate) {
                Chromosome childA = Cross(parentA, parentB);
                Chromosome childB = Cross(parentB, parentA);

                childA = (rand() % 101 < mutationRate) ? Mutation::Mutate(childA) : childA;
                childB = (rand() % 101 < mutationRate) ? Mutation::Mutate(childB) : childB;

                newPop.Add(childA);
                newPop.Add(childB);
            } else {
                newPop.Add(parentA);
                newPop.Add(parentB);
            }
        } else {
            if (roll < crossoverRate) {
                Chromosome childA = Cross(parentA, parentA);
                childA = (rand() % 101 < mutationRate) ? Mutation::Mutate(childA) : childA;
                newPop.Add(childA);
            } else {
                newPop.Add(parentA);
            }
        }
    }

    return newPop;
}

////////////////////////////////////////////////////////////////////////////////

Population Crossover::CrossSequential(Population pop, int crossoverRate, int mutationRate)
{
    Population newPop;

    while (pop.Size()) {
        int roll = rand() % 101;

        Chromosome parentA = pop.individuals.front();
        pop.individuals.erase(pop.individuals.begin());

        if (pop.Size()) {
            Chromosome parentB = pop.individuals.front();
            pop.individuals.erase(pop.individuals.begin());

            if (roll < crossoverRate) {
                Chromosome childA = Cross(parentA, parentB);
                Chromosome childB = Cross(parentB, parentA);

                childA = (rand() % 101 < mutationRate) ? Mutation::Mutate(childA) : childA;
                childB = (rand() % 101 < mutationRate) ? Mutation::Mutate(childB) : childB;

                newPop.Add(childA);
                newPop.Add(childB);
            } else {
                newPop.Add(parentA);
                newPop.Add(parentB);
            }
        } else {
            if (roll < crossoverRate) {
                Chromosome childA = Cross(parentA, parentA);
                childA = (rand() % 101 < mutationRate) ? Mutation::Mutate(childA) : childA;
                newPop.Add(childA);
            } else {
                newPop.Add(parentA);
            }
        }
    }

    return newPop;
}

////////////////////////////////////////////////////////////////////////////////

Chromosome Crossover::Cross(Chromosome parentA, Chromosome parentB)
{
    int ax = static_cast<int>(parentA.X());
    int ay = static_cast<int>(parentA.Y());
    int bx = static_cast<int>(parentB.X());
    int by = static_cast<int>(parentB.Y());

    long long deltaX = std::llabs(static_cast<long long>(ax) - bx);
    long long deltaY = std::llabs(static_cast<long long>(ay) - by);

    int offsetX = deltaX ? rand() % deltaX : 0;
    int offsetY = deltaY ? rand() % deltaY : 0;

    double newX = (parentA.X() < parentB.X()) ? (parentA.X() + offsetX) : (parentB.X() + offsetX);
    double newY = (parentA.Y() < parentB.Y()) ? (parentA.Y() + offsetY) : (parentB.Y() + offsetY);

    return Chromosome(newX, newY);
}

