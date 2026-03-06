#include "Fitness.h"
#include "MathUtils.h"

Fitness::~Fitness() {}

Fitness::Fitness() {}

void Fitness::AddPoint(Point pt)
{
    points.push_back(pt);
}

void Fitness::SetDistanceFactor(double factor)      { distanceFactor = factor; }
void Fitness::SetDistributionFactor(double factor)  { distributionFactor = factor; }
void Fitness::SetNormalizer(double value)           { normalizer = value; }

double Fitness::Evaluate(Chromosome& chromosome)
{
    Point pos(chromosome);

    double totalDist = 0;
    std::vector<double> distances;
    for (std::vector<Point>::iterator it = points.begin(); it != points.end(); it++) {
        double dist = MathUtils::Distance(*it, pos);
        distances.push_back(dist);
        totalDist += dist;
    }

    double meanDev   = MathUtils::MeanDeviation(distances);
    double numerator = normalizer * (points.size() * 2);
    double score     = numerator / ((totalDist * distanceFactor) + (meanDev * distributionFactor));

    return score;
}

bool Fitness::operator()(Chromosome& a, Chromosome& b)
{
    return Evaluate(a) > Evaluate(b);
}
