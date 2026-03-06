#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "Population.h"
#include "Chromosome.h"

class Crossover
{
public:
    static Population  CrossRandom(Population pop, int crossoverRate, int mutationRate);
    static Population  CrossSequential(Population pop, int crossoverRate, int mutationRate);
    static Chromosome  Cross(Chromosome parentA, Chromosome parentB);

private:
    Crossover();
};

#endif /* CROSSOVER_H_ */
