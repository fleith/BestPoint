#include "test_runner.h"
#include "ga_utils.h"

static Fitness makeGAFitness() {
    Fitness f;
    f.AddPoint(Point(50.0, 50.0));
    f.AddPoint(Point(70.0, 30.0));
    f.SetDistanceFactor(1.0);
    f.SetDistributionFactor(1.0);
    f.SetNormalizer(200.0);
    return f;
}

TEST(GAUtils_LinearSum_Four) {
    // 4 + 3 + 2 + 1 = 10
    Population pop;
    for (int i = 0; i < 4; i++) pop.Add(Chromosome(i * 1.0, i * 1.0));
    CHECK_EQ(GAUtils::LinearSum(pop), 10);
}

TEST(GAUtils_LinearSum_One) {
    Population pop;
    pop.Add(Chromosome(0.0, 0.0));
    CHECK_EQ(GAUtils::LinearSum(pop), 1);
}

TEST(GAUtils_LinearSum_Zero) {
    Population pop;
    CHECK_EQ(GAUtils::LinearSum(pop), 0);
}

TEST(GAUtils_Best_ReturnsHighestFitness) {
    Fitness f = makeGAFitness();
    Population pop;
    pop.Add(Chromosome(60.0, 40.0)); // near centroid of base points
    pop.Add(Chromosome(0.0,  0.0));  // far away
    pop.Add(Chromosome(100.0, 100.0)); // also far

    Chromosome best = GAUtils::Best(pop, f);
    double bestScore = f.Evaluate(best);

    // verify all others score lower
    for (int i = 0; i < pop.Size(); i++)
        CHECK(f.Evaluate(pop[i]) <= bestScore + 1e-9);
}

TEST(GAUtils_Worst_ReturnsLowestFitness) {
    Fitness f = makeGAFitness();
    Population pop;
    pop.Add(Chromosome(60.0, 40.0));
    pop.Add(Chromosome(0.0,  0.0));
    pop.Add(Chromosome(100.0, 100.0));

    Chromosome worst = GAUtils::Worst(pop, f);
    double worstScore = f.Evaluate(worst);

    for (int i = 0; i < pop.Size(); i++)
        CHECK(f.Evaluate(pop[i]) >= worstScore - 1e-9);
}

TEST(GAUtils_RemoveAndReturnBest) {
    Fitness f = makeGAFitness();
    Population pop;
    pop.Add(Chromosome(60.0, 40.0)); // best
    pop.Add(Chromosome(0.0,  0.0));
    pop.Add(Chromosome(100.0, 100.0));

    int sizeBefore = pop.Size();
    Chromosome best = GAUtils::RemoveAndReturnBest(pop, f);

    CHECK_EQ(pop.Size(), sizeBefore - 1);
    CHECK_NEAR(best.X(), 60.0, 1e-9);
}

TEST(GAUtils_BestFitness_GreaterThanWorst) {
    Fitness f = makeGAFitness();
    Population pop;
    pop.Add(Chromosome(60.0, 40.0));
    pop.Add(Chromosome(0.0,  0.0));

    double best  = GAUtils::BestFitness(pop, f);
    double worst = GAUtils::WorstFitness(pop, f);
    CHECK(best > worst);
}

TEST(GAUtils_AverageFitness_InRange) {
    Fitness f = makeGAFitness();
    Population pop;
    pop.Add(Chromosome(60.0, 40.0));
    pop.Add(Chromosome(0.0,  0.0));

    double avg   = GAUtils::AverageFitness(pop, f);
    double best  = GAUtils::BestFitness(pop, f);
    double worst = GAUtils::WorstFitness(pop, f);
    CHECK(avg >= worst - 1e-9);
    CHECK(avg <= best  + 1e-9);
}

TEST(GAUtils_RandomIndividual_InBounds) {
    for (int i = 0; i < 200; i++) {
        Chromosome c = GAUtils::RandomIndividual(10, 90, 20, 80);
        CHECK(c.X() >= 10.0 && c.X() < 90.0);
        CHECK(c.Y() >= 20.0 && c.Y() < 80.0);
    }
}

TEST(GAUtils_RandomPoint_InBounds) {
    for (int i = 0; i < 200; i++) {
        Point p = GAUtils::RandomPoint(5, 50, 10, 60);
        CHECK(p.X() >= 5.0 && p.X() < 50.0);
        CHECK(p.Y() >= 10.0 && p.Y() < 60.0);
    }
}
