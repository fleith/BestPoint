#ifndef APP_H_
#define APP_H_

#include <vector>
#include "Fitness.h"
#include "Population.h"
#include "Chromosome.h"
#include "Point.h"

class App
{
public:
    ~App();
    App();

    void CMDInit();

    void CMDGeneratePopulationAuto();
    void CMDGeneratePopulationManual();

    void CMDRunOneGeneration();
    void CMDRunTenGenerations();
    void CMDRunHundredGenerations();
    void CMDRunAllGenerations();

    void CMDRenderPopulation();
    void CMDRenderFitnessStats();

    void CMDGenerateBasePoints();

    Chromosome CMDGetBest();
    int        CMDGetBasePointCount();
    Point      CMDGetBasePoint(int i);

private:
    Fitness fitness;

    std::vector<Population> populations;

    int maxX, minX;
    int maxY, minY;

    int crossoverRate;
    int mutationRate;
    int populationSize;
    int maxGenerations;
    int remainingGenerations;

    bool configValid;

    void Step();
    void ValidateConfig();
    int  ScaleX(double x);
    int  ScaleY(double y);
};

extern App app;

#endif /* APP_H_ */
