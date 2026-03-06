#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>
#include "Chromosome.h"

class Population
{
public:
    ~Population();
    Population();
    Population(std::vector<Chromosome>& individuals);

    void Add(Chromosome chromosome);

    int        Size()            { return individuals.size(); }
    Chromosome operator[](int i) { return individuals[i]; }

private:
    std::vector<Chromosome> individuals;

    friend class Selection;
    friend class GAUtils;
    friend class Crossover;
};

#endif /* POPULATION_H_ */
