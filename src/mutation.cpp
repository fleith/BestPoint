#include "mutation.h"
#include <stdlib.h>
#include <cmath>

Chromosome Mutation::Mutate(Chromosome chromosome)
{
    int roll  = rand() % 101;
    double rangeX = chromosome.X() > 0 ? chromosome.X() + 1.0 : 1.0;
    double rangeY = chromosome.Y() > 0 ? chromosome.Y() + 1.0 : 1.0;

    if (roll > 75)
        return Chromosome(chromosome.X() - std::fmod(double(rand()), rangeX),
                          chromosome.Y() - std::fmod(double(rand()), rangeY));
    else if (roll > 50)
        return Chromosome(chromosome.X() + std::fmod(double(rand()), rangeX),
                          chromosome.Y() + std::fmod(double(rand()), rangeY));
    else if (roll > 25)
        return Chromosome(chromosome.X() + std::fmod(double(rand()), rangeX),
                          chromosome.Y() - std::fmod(double(rand()), rangeY));
    else if (roll > 5)
        return Chromosome(chromosome.X() - std::fmod(double(rand()), rangeX),
                          chromosome.Y() + std::fmod(double(rand()), rangeY));
    else
        return Chromosome(chromosome.Y(), chromosome.X());
}

