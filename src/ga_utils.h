#ifndef GAUTILS_H_
#define GAUTILS_H_

#include "point.h"
#include "fitness.h"
#include "population.h"
#include "chromosome.h"

class GAUtils
{
public:
    static int    RankSum(Population& pop);

    static double BestFitness(Population& pop, Fitness& fit);
    static double WorstFitness(Population& pop, Fitness& fit);
    static double AverageFitness(Population& pop, Fitness& fit);
    static double TotalFitness(Population& pop, Fitness& fit);

    static Point      RandomPoint(int minX, int maxX, int minY, int maxY);
    static Chromosome RandomIndividual(int minX, int maxX, int minY, int maxY);

    static Chromosome  Best(Population& pop, Fitness& fit);
    static Chromosome  Worst(Population& pop, Fitness& fit);
    static Chromosome  RemoveAndReturnBest(Population& pop, Fitness& fit);
    static void        ReplaceWithElite(Population& crossed, Population& elite, Fitness& fit);

private:
    GAUtils();
};

#endif /* GAUTILS_H_ */
