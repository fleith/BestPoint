#include "test_runner.h"
#include "chromosome.h"

TEST(Chromosome_ConstructorSetsCoords) {
    Chromosome c(3.5, 7.2);
    CHECK_NEAR(c.X(), 3.5, 1e-9);
    CHECK_NEAR(c.Y(), 7.2, 1e-9);
}

TEST(Chromosome_ZeroCoords) {
    Chromosome c(0.0, 0.0);
    CHECK_EQ(c.X(), 0.0);
    CHECK_EQ(c.Y(), 0.0);
}

TEST(Chromosome_NegativeCoords) {
    Chromosome c(-5.0, -3.0);
    CHECK_NEAR(c.X(), -5.0, 1e-9);
    CHECK_NEAR(c.Y(), -3.0, 1e-9);
}

TEST(Chromosome_LargeCoords) {
    Chromosome c(1e6, 1e6);
    CHECK_NEAR(c.X(), 1e6, 1e-3);
    CHECK_NEAR(c.Y(), 1e6, 1e-3);
}
