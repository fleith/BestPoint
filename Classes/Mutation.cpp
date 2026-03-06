#include "Mutation.h"
#include <stdlib.h>

Chromosome Mutation::Mutate(Chromosome chromosome)
{
    int roll  = rand() % 101;
    int baseX = static_cast<int>(chromosome.X());
    int baseY = static_cast<int>(chromosome.Y());
    int rangeX = (baseX > 0) ? baseX + 1 : 1;
    int rangeY = (baseY > 0) ? baseY + 1 : 1;

    if (roll > 75)
        return Chromosome(chromosome.X() - rand() % rangeX,
                          chromosome.Y() - rand() % rangeY);
    else if (roll > 50)
        return Chromosome(chromosome.X() + rand() % rangeX,
                          chromosome.Y() + rand() % rangeY);
    else if (roll > 25)
        return Chromosome(chromosome.X() + rand() % rangeX,
                          chromosome.Y() - rand() % rangeY);
    else if (roll > 5)
        return Chromosome(chromosome.X() - rand() % rangeX,
                          chromosome.Y() + rand() % rangeY);
    else
        return Chromosome(chromosome.Y(), chromosome.X());
}
