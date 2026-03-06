#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "ui.h"
#include "app.h"
#include "cli_config.h"

CLIConfig cliConfig;

// ---------------------------------------------------------------------------

static void printHelp(const char* prog)
{
    std::printf(
        "Usage: %s [options]\n"
        "\n"
        "Finds the 2D point that best minimises distance and spread\n"
        "to a set of randomly generated base points.\n"
        "\n"
        "Options:\n"
        "  -p,  --pop    <n>     Population size          (default: 50)\n"
        "  -g,  --gen    <n>     Number of generations    (default: 100)\n"
        "  -c,  --cross  <n>     Crossover rate %%         (default: 70)\n"
        "  -m,  --mut    <n>     Mutation rate %%          (default: 10)\n"
        "       --minx   <n>     Min X bound              (default: 0)\n"
        "       --maxx   <n>     Max X bound              (default: 100)\n"
        "       --miny   <n>     Min Y bound              (default: 0)\n"
        "       --maxy   <n>     Max Y bound              (default: 100)\n"
        "       --points <n>     Number of base points    (default: 5)\n"
        "       --sel    <type>  Selection method         (default: elitism)\n"
        "                          elitism | roulette | rank\n"
        "                          steady-state | hybrid\n"
        "       --ctype  <type>  Crossover type           (default: random)\n"
        "                          random | sequential\n"
        "       --fdist  <f>     Distance factor          (default: 1.0)\n"
        "       --fdist2 <f>     Distribution factor      (default: 1.0)\n"
        "  -h,  --help           Show this help\n",
        prog
    );
}

static bool parseArgs(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i];

        auto next = [&](const char* name) -> const char* {
            if (i + 1 >= argc) {
                std::fprintf(stderr, "error: '%s' requires a value\n", name);
                return nullptr;
            }
            return argv[++i];
        };

        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
            return false;
        }
        else if (strcmp(arg, "-p") == 0 || strcmp(arg, "--pop") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.populationSize = atoi(v);
        }
        else if (strcmp(arg, "-g") == 0 || strcmp(arg, "--gen") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.maxGenerations = atoi(v);
        }
        else if (strcmp(arg, "-c") == 0 || strcmp(arg, "--cross") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.crossoverRate = atoi(v);
        }
        else if (strcmp(arg, "-m") == 0 || strcmp(arg, "--mut") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.mutationRate = atoi(v);
        }
        else if (strcmp(arg, "--minx") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.minX = atoi(v);
        }
        else if (strcmp(arg, "--maxx") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.maxX = atoi(v);
        }
        else if (strcmp(arg, "--miny") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.minY = atoi(v);
        }
        else if (strcmp(arg, "--maxy") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.maxY = atoi(v);
        }
        else if (strcmp(arg, "--points") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.basePointCount = atoi(v);
        }
        else if (strcmp(arg, "--fdist") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.distanceFactor = atof(v);
        }
        else if (strcmp(arg, "--fdist2") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.distributionFactor = atof(v);
        }
        else if (strcmp(arg, "--sel") == 0) {
            const char* v = next(arg); if (!v) return false;
            if      (strcmp(v, "elitism")      == 0) cliConfig.selectionMethod = ELITISM;
            else if (strcmp(v, "roulette")     == 0) cliConfig.selectionMethod = ROULETTE;
            else if (strcmp(v, "rank")         == 0) cliConfig.selectionMethod = RANK;
            else if (strcmp(v, "steady-state") == 0) cliConfig.selectionMethod = STEADY_STATE;
            else if (strcmp(v, "hybrid")       == 0) cliConfig.selectionMethod = HYBRID;
            else { std::fprintf(stderr, "error: unknown selection type '%s'\n", v); return false; }
        }
        else if (strcmp(arg, "--ctype") == 0) {
            const char* v = next(arg); if (!v) return false;
            if      (strcmp(v, "random")     == 0) cliConfig.crossoverMethod = RANDOM;
            else if (strcmp(v, "sequential") == 0) cliConfig.crossoverMethod = SEQUENTIAL;
            else { std::fprintf(stderr, "error: unknown crossover type '%s'\n", v); return false; }
        }
        else {
            std::fprintf(stderr, "error: unknown option '%s'\n", arg);
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------

static void separator() { std::printf("================================================\n"); }

static const char* selectionName(SelectionMethod m)
{
    switch (m) {
        case ELITISM:     return "elitism";
        case ROULETTE:    return "roulette";
        case RANK:        return "rank";
        case STEADY_STATE:return "steady-state";
        case HYBRID:      return "hybrid";
        default:          return "?";
    }
}

static const char* crossoverName(CrossoverMethod m)
{
    return (m == RANDOM) ? "random" : "sequential";
}

// ---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    if (!parseArgs(argc, argv)) {
        printHelp(argv[0]);
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));

    separator();
    std::printf("  BestPoint - Genetic Algorithm\n");
    separator();
    std::printf("  Population     : %d\n",   cliConfig.populationSize);
    std::printf("  Generations    : %d\n",   cliConfig.maxGenerations);
    std::printf("  Crossover      : %d%%\n", cliConfig.crossoverRate);
    std::printf("  Mutation       : %d%%\n", cliConfig.mutationRate);
    std::printf("  Bounds X       : [%d, %d]\n", cliConfig.minX, cliConfig.maxX);
    std::printf("  Bounds Y       : [%d, %d]\n", cliConfig.minY, cliConfig.maxY);
    std::printf("  Base points    : %d\n",   cliConfig.basePointCount);
    std::printf("  Selection      : %s\n",   selectionName(cliConfig.selectionMethod));
    std::printf("  Crossover type : %s\n",   crossoverName(cliConfig.crossoverMethod));
    std::printf("  Dist factor    : %.2f\n", cliConfig.distanceFactor);
    std::printf("  Distr factor   : %.2f\n", cliConfig.distributionFactor);
    separator();

    UI::InitializeApp();
    UI::GenerateBasePoints();

    std::printf("  Base points:\n");
    for (int i = 0; i < app.CMDGetBasePointCount(); i++) {
        Point p = app.CMDGetBasePoint(i);
        std::printf("    [%d] (%.2f, %.2f)\n", i + 1, p.X(), p.Y());
    }
    separator();

    UI::GeneratePopulationAuto();

    std::printf("  Running %d generations...\n", cliConfig.maxGenerations);
    separator();
    UI::RunAllGenerations();

    separator();
    std::printf("  Result\n");
    separator();
    Chromosome best = app.CMDGetBest();
    std::printf("  Best individual : (%.4f, %.4f)\n", best.X(), best.Y());
    separator();

    return 0;
}
