#include "TestRunner.h"
#include "MathUtils.h"
#include <vector>

TEST(MathUtils_Distance_PythagoreanTriple) {
    Point a(0.0, 0.0), b(3.0, 4.0);
    CHECK_NEAR(MathUtils::Distance(a, b), 5.0, 1e-9);
}

TEST(MathUtils_Distance_SamePoint) {
    Point a(7.0, 3.0), b(7.0, 3.0);
    CHECK_NEAR(MathUtils::Distance(a, b), 0.0, 1e-9);
}

TEST(MathUtils_Distance_Symmetric) {
    Point a(1.0, 2.0), b(4.0, 6.0);
    CHECK_NEAR(MathUtils::Distance(a, b), MathUtils::Distance(b, a), 1e-9);
}

TEST(MathUtils_Distance_Horizontal) {
    Point a(0.0, 5.0), b(10.0, 5.0);
    CHECK_NEAR(MathUtils::Distance(a, b), 10.0, 1e-9);
}

TEST(MathUtils_Distance_Vertical) {
    Point a(3.0, 0.0), b(3.0, 7.0);
    CHECK_NEAR(MathUtils::Distance(a, b), 7.0, 1e-9);
}

TEST(MathUtils_MeanDeviation_Uniform) {
    std::vector<double> v;
    v.push_back(5.0); v.push_back(5.0); v.push_back(5.0);
    CHECK_NEAR(MathUtils::MeanDeviation(v), 0.0, 1e-9);
}

TEST(MathUtils_MeanDeviation_TwoValues) {
    // [0, 2] → mean=1, deviations=[1,1], mean deviation=1
    std::vector<double> v;
    v.push_back(0.0); v.push_back(2.0);
    CHECK_NEAR(MathUtils::MeanDeviation(v), 1.0, 1e-9);
}

TEST(MathUtils_MeanDeviation_SingleValue) {
    std::vector<double> v;
    v.push_back(42.0);
    CHECK_NEAR(MathUtils::MeanDeviation(v), 0.0, 1e-9);
}

TEST(MathUtils_MeanDeviation_Symmetric) {
    // [-1, 0, 1] → mean=0, deviations=[1,0,1], mean deviation=2/3
    std::vector<double> v;
    v.push_back(-1.0); v.push_back(0.0); v.push_back(1.0);
    CHECK_NEAR(MathUtils::MeanDeviation(v), 2.0 / 3.0, 1e-9);
}
