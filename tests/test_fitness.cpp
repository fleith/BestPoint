#include "TestRunner.h"
#include "Fitness.h"

static Fitness makeFitness() {
    Fitness f;
    f.AddPoint(Point(50.0, 50.0));
    f.AddPoint(Point(70.0, 30.0));
    f.SetDistanceFactor(1.0);
    f.SetDistributionFactor(1.0);
    f.SetNormalizer(200.0);
    return f;
}

TEST(Fitness_InitiallyEmpty) {
    Fitness f;
    CHECK_EQ(f.PointCount(), 0);
}

TEST(Fitness_AddPoint) {
    Fitness f;
    f.AddPoint(Point(1.0, 2.0));
    CHECK_EQ(f.PointCount(), 1);
    f.AddPoint(Point(3.0, 4.0));
    CHECK_EQ(f.PointCount(), 2);
}

TEST(Fitness_ClearPoints) {
    Fitness f;
    f.AddPoint(Point(1.0, 2.0));
    f.AddPoint(Point(3.0, 4.0));
    f.ClearPoints();
    CHECK_EQ(f.PointCount(), 0);
}

TEST(Fitness_IndexOperator) {
    Fitness f;
    f.AddPoint(Point(11.0, 22.0));
    CHECK_NEAR(f[0].X(), 11.0, 1e-9);
    CHECK_NEAR(f[0].Y(), 22.0, 1e-9);
}

TEST(Fitness_EvaluateCloserIsBetter) {
    Fitness f = makeFitness();
    // near: between the two base points, well-placed
    Chromosome near(60.0, 40.0);
    // far: corner, far from both base points
    Chromosome far(0.0, 0.0);
    CHECK(f.Evaluate(near) > f.Evaluate(far));
}

TEST(Fitness_EvaluatePositive) {
    Fitness f = makeFitness();
    Chromosome c(40.0, 40.0);
    CHECK(f.Evaluate(c) > 0.0);
}

TEST(Fitness_ComparatorOrdering) {
    Fitness f = makeFitness();
    Chromosome near(60.0, 40.0);
    Chromosome far(0.0, 0.0);
    CHECK(f(near, far));   // near ranks higher
    CHECK(!f(far, near));  // far does not rank higher
}

TEST(Fitness_ComparatorReflexive) {
    Fitness f = makeFitness();
    Chromosome c(50.0, 50.0);
    // strict weak ordering: c is not greater than itself
    // (both directions false OR one direction false, depending on equal fitness)
    // We just verify both can't be true simultaneously
    CHECK(!(f(c, c) && f(c, c))); // trivially true, but guards against NaN
}
