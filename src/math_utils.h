#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include <vector>
#include "point.h"

class MathUtils
{
public:
    static double Distance(Point& a, Point& b);
    static double MeanDeviation(std::vector<double>& values);

private:
    MathUtils();
};

#endif /* MATHUTILS_H_ */
