/*
 * CLI/main.cpp
 *
 * Command-line entry point for BestPoint.
 * Finds the 2D point that minimises total distance + spread
 * to a set of base points, using a Genetic Algorithm.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>

#include "../Interface/GerenteInterfaceAG.h"
#include "../App/AppAG.h"
#include "CLIConfig.h"

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
        "       --sel    <type>  Selection method         (default: elitismo)\n"
        "                          elitismo | roleta | classificacao\n"
        "                          estacionaria | hibrido\n"
        "       --ctype  <type>  Crossover type           (default: aleatorio)\n"
        "                          aleatorio | sequencial\n"
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

        // helper: consume next argument or error
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
            cliConfig.tamanhoPopulacao = atoi(v);
        }
        else if (strcmp(arg, "-g") == 0 || strcmp(arg, "--gen") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.numeroMaxGeracoes = atoi(v);
        }
        else if (strcmp(arg, "-c") == 0 || strcmp(arg, "--cross") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.taxaCrossover = atoi(v);
        }
        else if (strcmp(arg, "-m") == 0 || strcmp(arg, "--mut") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.taxaMutacao = atoi(v);
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
            cliConfig.numeroPontosBase = atoi(v);
        }
        else if (strcmp(arg, "--fdist") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.fatorDistancia = atof(v);
        }
        else if (strcmp(arg, "--fdist2") == 0) {
            const char* v = next(arg); if (!v) return false;
            cliConfig.fatorDistribuicao = atof(v);
        }
        else if (strcmp(arg, "--sel") == 0) {
            const char* v = next(arg); if (!v) return false;
            if      (strcmp(v, "elitismo")      == 0) cliConfig.tipoSelecao = ELITISMO;
            else if (strcmp(v, "roleta")        == 0) cliConfig.tipoSelecao = ROLETA;
            else if (strcmp(v, "classificacao") == 0) cliConfig.tipoSelecao = CLASSIFICACAO;
            else if (strcmp(v, "estacionaria")  == 0) cliConfig.tipoSelecao = ESTACIONARIA;
            else if (strcmp(v, "hibrido")       == 0) cliConfig.tipoSelecao = ALVAROS;
            else { std::fprintf(stderr, "error: unknown selection type '%s'\n", v); return false; }
        }
        else if (strcmp(arg, "--ctype") == 0) {
            const char* v = next(arg); if (!v) return false;
            if      (strcmp(v, "aleatorio")  == 0) cliConfig.tipoCrossover = ALEATORIO;
            else if (strcmp(v, "sequencial") == 0) cliConfig.tipoCrossover = SEQUENCIAL;
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

static const char* selName(TipoSelecao t)
{
    switch (t) {
        case ELITISMO:      return "elitismo";
        case ROLETA:        return "roleta";
        case CLASSIFICACAO: return "classificacao";
        case ESTACIONARIA:  return "estacionaria";
        case ALVAROS:       return "hibrido";
        default:            return "?";
    }
}

static const char* crossName(TipoCross t)
{
    return (t == ALEATORIO) ? "aleatorio" : "sequencial";
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
    std::printf("  Population     : %d\n",   cliConfig.tamanhoPopulacao);
    std::printf("  Generations    : %d\n",   cliConfig.numeroMaxGeracoes);
    std::printf("  Crossover      : %d%%\n", cliConfig.taxaCrossover);
    std::printf("  Mutation       : %d%%\n", cliConfig.taxaMutacao);
    std::printf("  Bounds X       : [%d, %d]\n", cliConfig.minX, cliConfig.maxX);
    std::printf("  Bounds Y       : [%d, %d]\n", cliConfig.minY, cliConfig.maxY);
    std::printf("  Base points    : %d\n",   cliConfig.numeroPontosBase);
    std::printf("  Selection      : %s\n",   selName(cliConfig.tipoSelecao));
    std::printf("  Crossover type : %s\n",   crossName(cliConfig.tipoCrossover));
    std::printf("  Dist factor    : %.2f\n", cliConfig.fatorDistancia);
    std::printf("  Distr factor   : %.2f\n", cliConfig.fatorDistribuicao);
    separator();

    // 1. Initialise app parameters
    GI::InicializaAplicacao();

    // 2. Generate random base points
    GI::GeraPontosBase();
    std::printf("  Base points:\n");
    for (int i = 0; i < app.CMDGetNumeroPontosBase(); i++) {
        Ponto p = app.CMDGetPontoBase(i);
        std::printf("    [%d] (%.2f, %.2f)\n", i + 1, p.PosicaoX(), p.PosicaoY());
    }
    separator();

    // 3. Generate initial population
    GI::GeraPopulacaoAutomatica();

    // 4. Run all generations
    std::printf("  Running %d generations...\n", cliConfig.numeroMaxGeracoes);
    separator();
    GI::ExecutaAteUltimaGeracao();

    // 5. Report final result
    separator();
    std::printf("  Result\n");
    separator();
    Cromossomo best = app.CMDGetMelhorIndividuo();
    std::printf("  Best individual : (%.4f, %.4f)\n", best.PosicaoX(), best.PosicaoY());
    separator();

    return 0;
}
