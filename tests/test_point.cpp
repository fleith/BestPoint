#include "test_runner.h"
#include "point.h"

TEST(Point_DoubleConstructor) {
    Point p(4.0, 8.0);
    CHECK_NEAR(p.X(), 4.0, 1e-9);
    CHECK_NEAR(p.Y(), 8.0, 1e-9);
}

TEST(Point_ChromosomeConstructor) {
    Chromosome c(1.5, 2.5);
    Point p(c);
    CHECK_NEAR(p.X(), 1.5, 1e-9);
    CHECK_NEAR(p.Y(), 2.5, 1e-9);
}

TEST(Point_ChromosomeConstructorCopiesValues) {
    Chromosome c(10.0, 20.0);
    Point p(c);
    // Point should be independent of chromosome
    CHECK_NEAR(p.X(), 10.0, 1e-9);
    CHECK_NEAR(p.Y(), 20.0, 1e-9);
}
