#include "test_runner.h"
#include "population.h"

TEST(Population_InitiallyEmpty) {
    Population p;
    CHECK_EQ(p.Size(), 0);
}

TEST(Population_AddIncreasesSize) {
    Population p;
    p.Add(Chromosome(1.0, 2.0));
    CHECK_EQ(p.Size(), 1);
    p.Add(Chromosome(3.0, 4.0));
    CHECK_EQ(p.Size(), 2);
}

TEST(Population_IndexOperator) {
    Population p;
    p.Add(Chromosome(10.0, 20.0));
    p.Add(Chromosome(30.0, 40.0));
    CHECK_NEAR(p[0].X(), 10.0, 1e-9);
    CHECK_NEAR(p[0].Y(), 20.0, 1e-9);
    CHECK_NEAR(p[1].X(), 30.0, 1e-9);
    CHECK_NEAR(p[1].Y(), 40.0, 1e-9);
}

TEST(Population_VectorConstructor) {
    std::vector<Chromosome> v;
    v.push_back(Chromosome(5.0, 6.0));
    v.push_back(Chromosome(7.0, 8.0));
    Population p(v);
    CHECK_EQ(p.Size(), 2);
    CHECK_NEAR(p[0].X(), 5.0, 1e-9);
    CHECK_NEAR(p[1].X(), 7.0, 1e-9);
}
