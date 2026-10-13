#include "point.h"

Point::~Point() {}

Point::Point(const Chromosome& chromosome) : x(chromosome.X()), y(chromosome.Y()) {}

Point::Point(double x, double y) : x(x), y(y) {}

double Point::X() { return x; }

double Point::Y() { return y; }

