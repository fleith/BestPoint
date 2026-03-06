/*
 * Classes/main.cpp — standalone test entry point (no GUI, no App layer)
 */

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "chromosome.h"
#include "crossover.h"
#include "fitness.h"
#include "mutation.h"
#include "point.h"
#include "population.h"
#include "selection.h"

int main(int argc, char* argv[])
{
    srand(time(0));

    Chromosome c1(1,  40);
    Chromosome c2(10, 28);
    Chromosome c3(32, 15);
    Chromosome c4(72, 90);

    Point p1(50, 50);
    Point p2(70, 70);

    Population pop;
    pop.Add(c1);
    pop.Add(c2);
    pop.Add(c3);
    pop.Add(c4);

    Fitness fit;
    fit.AddPoint(p1);
    fit.SetDistanceFactor(1.0);
    fit.SetDistributionFactor(1.0);
    fit.SetNormalizer(200.0);

    Selection sel(fit);
    Population selected = sel.ByElitism(pop);

    std::cout << "Selected " << selected.Size() << " individuals." << std::endl;

    return 0;
}
