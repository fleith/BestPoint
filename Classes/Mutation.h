#ifndef MUTATION_H_
#define MUTATION_H_

#include "Chromosome.h"

class Mutation
{
public:
    static Chromosome Mutate(Chromosome chromosome);

private:
    Mutation();
};

#endif /* MUTATION_H_ */
