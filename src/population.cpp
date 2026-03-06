#include "population.h"

Population::~Population() {}

Population::Population() {}

Population::Population(std::vector<Chromosome>& individuals) : individuals(individuals) {}

void Population::Add(Chromosome chromosome)
{
    individuals.push_back(chromosome);
}
