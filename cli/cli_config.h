#ifndef CLICONFIG_H_
#define CLICONFIG_H_

#include <string>
#include "ui.h"

struct CLIConfig {
    int crossoverRate    = 70;
    int mutationRate     = 10;
    int populationSize   = 50;
    int maxGenerations   = 100;
    int maxX = 100, minX = 0;
    int maxY = 100, minY = 0;
    int basePointCount   = 5;
    double distanceFactor    = 1.0;
    double distributionFactor = 1.0;
    CrossoverMethod crossoverMethod = RANDOM;
    SelectionMethod selectionMethod = TRUNCATION;
    std::string     htmlFile        = "";
};

extern CLIConfig cliConfig;

#endif /* CLICONFIG_H_ */
