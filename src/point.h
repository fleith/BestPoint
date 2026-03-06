#ifndef POINT_H_
#define POINT_H_

#include "chromosome.h"

class Point
{
public:
    ~Point();
    Point(Chromosome& chromosome);
    Point(double x, double y);

    double X();
    double Y();

private:
    double x;
    double y;
};

#endif /* POINT_H_ */
