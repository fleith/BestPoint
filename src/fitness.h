#ifndef FITNESS_H_
#define FITNESS_H_

#include <vector>
#include "point.h"
#include "chromosome.h"

class Fitness
{
public:
    ~Fitness();
    Fitness();

    void  AddPoint(Point pt);
    int   PointCount()       { return points.size(); }
    void  ClearPoints()      { points.clear(); }
    Point operator[](int i)  { return points[i]; }

    double Evaluate(Chromosome& chromosome);

    bool operator()(Chromosome& a, Chromosome& b);

    void SetDistanceFactor(double factor);
    void SetDistributionFactor(double factor);
    void SetNormalizer(double value);

private:
    std::vector<Point> points;

    double distanceFactor;
    double distributionFactor;
    double normalizer;
};

#endif /* FITNESS_H_ */
