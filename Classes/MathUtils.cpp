#include "MathUtils.h"
#include <cmath>

double MathUtils::Distance(Point& a, Point& b)
{
    double dx = fabs(a.X() - b.X());
    double dy = fabs(a.Y() - b.Y());
    return sqrt(dx * dx + dy * dy);
}

double MathUtils::MeanDeviation(std::vector<double>& values)
{
    double sum = 0;
    for (std::vector<double>::iterator it = values.begin(); it != values.end(); it++)
        sum += *it;
    double mean = sum / values.size();

    double deviationSum = 0;
    for (std::vector<double>::iterator it = values.begin(); it != values.end(); it++)
        deviationSum += fabs(*it - mean);

    return deviationSum / values.size();
}
