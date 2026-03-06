#ifndef SELECTION_H_
#define SELECTION_H_

#include "fitness.h"
#include "population.h"

class Selection
{
public:
    Selection(Fitness fitness);

    Population ByTruncation(Population population);
    Population ByElitistReplacement(Population population);
    Population ByRank(Population population);
    Population ByHybrid(Population population);
    Population ByRoulette(Population population);

private:
    Fitness fitness;
};

#endif /* SELECTION_H_ */
