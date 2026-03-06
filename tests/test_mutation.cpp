#include "test_runner.h"
#include "mutation.h"

TEST(Mutation_Mutate_ReturnsChromosome) {
    Chromosome c(50.0, 50.0);
    Chromosome m = Mutation::Mutate(c);
    // Just verify it runs — result is a valid Chromosome
    CHECK(m.X() == m.X()); // NaN check
    CHECK(m.Y() == m.Y());
}

TEST(Mutation_Mutate_ProducesVariation) {
    Chromosome c(50.0, 50.0);
    bool anyDifferent = false;
    for (int i = 0; i < 200; i++) {
        Chromosome m = Mutation::Mutate(c);
        if (m.X() != c.X() || m.Y() != c.Y()) {
            anyDifferent = true;
            break;
        }
    }
    CHECK(anyDifferent);
}

TEST(Mutation_Mutate_ZeroPosition) {
    // rangeX/Y should clamp to 1 to avoid modulo-by-zero
    Chromosome c(0.0, 0.0);
    for (int i = 0; i < 50; i++) {
        Chromosome m = Mutation::Mutate(c);
        CHECK(m.X() == m.X()); // NaN check
        CHECK(m.Y() == m.Y());
    }
}

TEST(Mutation_Mutate_SmallPosition) {
    Chromosome c(1.0, 1.0);
    for (int i = 0; i < 50; i++) {
        Chromosome m = Mutation::Mutate(c);
        CHECK(m.X() == m.X());
        CHECK(m.Y() == m.Y());
    }
}
