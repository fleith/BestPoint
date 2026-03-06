#include "TestRunner.h"
#include <cstdlib>
#include <cstdio>

int main()
{
    srand(42); // fixed seed — reproducible results

    std::printf("BestPoint Test Suite\n");
    std::printf("====================\n\n");

    return runTests();
}
