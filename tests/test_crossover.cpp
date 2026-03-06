#include "test_runner.h"
#include "crossover.h"

TEST(Crossover_Cross_ResultInRange) {
    Chromosome a(10.0, 20.0), b(30.0, 40.0);
    for (int i = 0; i < 100; i++) {
        Chromosome c = Crossover::Cross(a, b);
        CHECK(c.X() >= 10.0 && c.X() <= 30.0);
        CHECK(c.Y() >= 20.0 && c.Y() <= 40.0);
    }
}

TEST(Crossover_Cross_SameParents) {
    // When parents are identical, delta=0, offset=0 → child equals parents
    Chromosome a(15.0, 25.0);
    Chromosome c = Crossover::Cross(a, a);
    CHECK_NEAR(c.X(), 15.0, 1e-9);
    CHECK_NEAR(c.Y(), 25.0, 1e-9);
}

TEST(Crossover_Cross_OrderIndependent_Range) {
    // Cross(a,b) and Cross(b,a) both produce values within [min,max] of each coord
    Chromosome a(5.0, 60.0), b(55.0, 10.0);
    for (int i = 0; i < 50; i++) {
        Chromosome c1 = Crossover::Cross(a, b);
        Chromosome c2 = Crossover::Cross(b, a);
        CHECK(c1.X() >= 5.0  && c1.X() <= 55.0);
        CHECK(c1.Y() >= 10.0 && c1.Y() <= 60.0);
        CHECK(c2.X() >= 5.0  && c2.X() <= 55.0);
        CHECK(c2.Y() >= 10.0 && c2.Y() <= 60.0);
    }
}

TEST(Crossover_CrossRandom_PreservesSize) {
    Population pop;
    for (int i = 0; i < 10; i++)
        pop.Add(Chromosome(i * 10.0, i * 5.0));
    Population result = Crossover::CrossRandom(pop, 70, 10);
    CHECK_EQ(result.Size(), 10);
}

TEST(Crossover_CrossSequential_PreservesSize) {
    Population pop;
    for (int i = 0; i < 10; i++)
        pop.Add(Chromosome(i * 10.0, i * 5.0));
    Population result = Crossover::CrossSequential(pop, 70, 10);
    CHECK_EQ(result.Size(), 10);
}

TEST(Crossover_CrossRandom_NoCrossover_Passthrough) {
    // crossoverRate=0 → no crossing, individuals passed through unchanged
    Population pop;
    pop.Add(Chromosome(1.0, 2.0));
    pop.Add(Chromosome(3.0, 4.0));
    Population result = Crossover::CrossRandom(pop, 0, 0);
    CHECK_EQ(result.Size(), 2);
    // With rate 0, both parents survive as-is
    bool found1 = false, found2 = false;
    for (int i = 0; i < result.Size(); i++) {
        if (result[i].X() == 1.0) found1 = true;
        if (result[i].X() == 3.0) found2 = true;
    }
    CHECK(found1);
    CHECK(found2);
}

TEST(Crossover_CrossRandom_OddPopulation) {
    // Odd-sized population: last individual handled alone
    Population pop;
    for (int i = 0; i < 7; i++)
        pop.Add(Chromosome(i * 10.0, i * 10.0));
    Population result = Crossover::CrossRandom(pop, 70, 0);
    CHECK_EQ(result.Size(), 7);
}
