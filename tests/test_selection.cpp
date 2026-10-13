#include "test_runner.h"
#include "selection.h"

static Fitness makeSelFitness() {
    Fitness f;
    f.AddPoint(Point(50.0, 50.0));
    f.AddPoint(Point(70.0, 30.0));
    f.SetDistanceFactor(1.0);
    f.SetDistributionFactor(1.0);
    f.SetNormalizer(200.0);
    return f;
}

static Population makeSelPop(int n = 10) {
    Population p;
    for (int i = 0; i < n; i++)
        p.Add(Chromosome(i * 10.0, i * 10.0));
    return p;
}

TEST(Selection_ByTruncation_PreservesSize) {
    Fitness f = makeSelFitness();
    Selection sel(f);
    Population pop = makeSelPop();
    int sz = pop.Size();
    Population result = sel.ByTruncation(pop);
    CHECK_EQ(result.Size(), sz);
}

TEST(Selection_ByRoulette_PreservesSize) {
    Fitness f = makeSelFitness();
    Selection sel(f);
    Population pop = makeSelPop();
    int sz = pop.Size();
    Population result = sel.ByRoulette(pop);
    CHECK_EQ(result.Size(), sz);
}

TEST(Selection_ByRank_PreservesSize) {
    Fitness f = makeSelFitness();
    Selection sel(f);
    Population pop = makeSelPop();
    int sz = pop.Size();
    Population result = sel.ByRank(pop);
    CHECK_EQ(result.Size(), sz);
}

TEST(Selection_ByElitistReplacement_PreservesSize) {
    Fitness f = makeSelFitness();
    Selection sel(f);
    Population pop = makeSelPop(20); // needs at least 20 for 5% = 1
    int sz = pop.Size();
    Population result = sel.ByElitistReplacement(pop);
    CHECK_EQ(result.Size(), sz);
}

TEST(Selection_ByHybrid_PreservesSize) {
    Fitness f = makeSelFitness();
    Selection sel(f);
    Population pop = makeSelPop();
    int sz = pop.Size();
    Population result = sel.ByHybrid(pop);
    CHECK_EQ(result.Size(), sz);
}

TEST(Selection_ByTruncation_BestIsIncluded) {
    Fitness f = makeSelFitness();
    Selection sel(f);
    Population pop = makeSelPop(9); // divisible by 3
    // chromosome closest to (50,50) and (70,30) is around (50,40) or (60,40)
    // our population has (50,50) which is closest
    double bestFitnessBefore = f.Evaluate(pop[5]); // (50,50)
    Population result = sel.ByTruncation(pop);
    // at least one individual in result must have fitness >= best before
    bool foundGood = false;
    for (int i = 0; i < result.Size(); i++) {
        if (f.Evaluate(result[i]) >= bestFitnessBefore - 1e-9)
            foundGood = true;
    }
    CHECK(foundGood);
}


TEST(Selection_ExactMatchAndZeroWeights) {
    Fitness f;
    f.SetNormalizer(200.0);
    f.AddPoint(Point(0, 0));
    Population pop;
    for (int i = 0; i < 10; ++i) pop.Add(Chromosome(0, 0));
    Selection exact(f);
    CHECK_EQ(exact.ByRoulette(pop).Size(), 10);
    CHECK_EQ(exact.ByHybrid(pop).Size(), 10);
    f.ClearPoints();
    Selection zero(f);
    CHECK_EQ(zero.ByRoulette(pop).Size(), 10);
    CHECK_EQ(zero.ByHybrid(pop).Size(), 10);
}

TEST(Selection_RouletteSamplesBeyondFirstIndividual) {
    Fitness f;
    f.SetNormalizer(200.0);
    f.AddPoint(Point(0, 0));
    Population pop;
    // Equal weights, each larger than Windows RAND_MAX after old scaling.
    for (int i = 0; i < 100; ++i)
        pop.Add(Chromosome(i % 2 == 0 ? 1 : -1, 0));
    Selection selection(f);
    Population selected = selection.ByRoulette(pop);
    bool positive = false, negative = false;
    for (int i = 0; i < selected.Size(); ++i) {
        positive = positive || selected[i].X() > 0;
        negative = negative || selected[i].X() < 0;
    }
    CHECK(positive && negative);
}
