#ifndef SELECTION_H_
#define SELECTION_H_

#include "fitness.h"
#include "population.h"

class Selection
{
public:
    Selection(Fitness fitness);

    Population ByElitism(Population population);
    Population BySteadyState(Population population);
    Population ByRank(Population population);
    Population Hybrid(Population population);
    Population ByRoulette(Population population);

private:
    Fitness fitness;
};

#endif /* SELECTION_H_ */
