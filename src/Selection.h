#ifndef SELECTION_H_
#define SELECTION_H_

#include "Fitness.h"
#include "Population.h"

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
