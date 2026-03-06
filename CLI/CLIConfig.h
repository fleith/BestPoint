#ifndef CLICONFIG_H_
#define CLICONFIG_H_

#include "../Interface/GerenteInterfaceAG.h"

struct CLIConfig {
    int taxaCrossover     = 70;
    int taxaMutacao       = 10;
    int tamanhoPopulacao  = 50;
    int numeroMaxGeracoes = 100;
    int maxX = 100, minX = 0;
    int maxY = 100, minY = 0;
    int numeroPontosBase  = 5;
    double fatorDistancia    = 1.0;
    double fatorDistribuicao = 1.0;
    TipoCross   tipoCrossover = ALEATORIO;
    TipoSelecao tipoSelecao   = ELITISMO;
};

extern CLIConfig cliConfig;

#endif /* CLICONFIG_H_ */
