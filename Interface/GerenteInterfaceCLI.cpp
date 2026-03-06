/*
 * GerenteInterfaceCLI.cpp
 *
 * CLI implementation of the GI facade. Replaces GerenteInterfaceAG.cpp
 * (the VCL/Borland version) for headless builds.
 */

#include "GerenteInterfaceAG.h"
#include "../CLI/CLIConfig.h"
#include "../App/AppAG.h"

#include <cstdio>

static int geracaoAtual = 0;

// ---------------------------------------------------------------------------
// Chart / drawing — no-ops in CLI
// ---------------------------------------------------------------------------

void GI::AdicionaFitnessMelhorPiorEMediaIndividuo(double melhor, double pior, double media)
{
    geracaoAtual++;
    std::printf("  Gen %4d/%d  |  best=%10.4f  worst=%10.4f  avg=%10.4f\n",
        geracaoAtual, cliConfig.numeroMaxGeracoes, melhor, pior, media);
}

void GI::LimpaGraficoMelhorPiorIndividuo()  { geracaoAtual = 0; }
void GI::LimpaTelaPontos()                  {}
void GI::AdicionaPontoBase(double, double)           {}
void GI::AdicionaPontoIndividuo(double, double)      {}
void GI::AdicionaPontoMelhorIndividuo(double, double){}
void GI::AdicionaPontoPiorIndividuo(double, double)  {}

// ---------------------------------------------------------------------------
// Config getters — read from CLIConfig
// ---------------------------------------------------------------------------

int    GI::PercentualCrossover()    { return cliConfig.taxaCrossover; }
int    GI::PercentualMutacao()      { return cliConfig.taxaMutacao; }
int    GI::TamanhoPopulacao()       { return cliConfig.tamanhoPopulacao; }
int    GI::NumeroMaximoDeGeracoes() { return cliConfig.numeroMaxGeracoes; }
int    GI::ValorMaximoEixoX()       { return cliConfig.maxX; }
int    GI::ValorMaximoEixoY()       { return cliConfig.maxY; }
int    GI::ValorMinimoEixoX()       { return cliConfig.minX; }
int    GI::ValorMinimoEixoY()       { return cliConfig.minY; }
int    GI::NumeroDePontosBase()     { return cliConfig.numeroPontosBase; }
double GI::FatorDistancia()         { return cliConfig.fatorDistancia; }
double GI::FatorDistribuicao()      { return cliConfig.fatorDistribuicao; }
int    GI::AlturaJanelaDesenho()    { return 500; }
int    GI::LarguraJanelaDesenho()   { return 500; }

TipoCross   GI::TipoDeCruzamento()  { return cliConfig.tipoCrossover; }
TipoSelecao GI::TipoDeSelecao()     { return cliConfig.tipoSelecao; }

// ---------------------------------------------------------------------------
// App commands
// ---------------------------------------------------------------------------

void GI::AtualizaInformacoesJanela()
{
    app.CMDMostraPopulacaoTela();
    app.CMDMostraMelhorPiorIndividuoTela();
}

void GI::InicializaAplicacao()     { app.CMDInicializarApp(); }
void GI::GeraPopulacaoAutomatica() { app.CMDGeraPopulacaoAuto(); GI::LimpaGraficoMelhorPiorIndividuo(); }
void GI::GeraPopulacaoManual()     { app.CMDGeraPopulacaoManual(); }
void GI::ExecutaMaisUmaGeracao()   { app.CMDExecutaUmaGeracao(); }
void GI::ExecutaMaisDezGeracoes()  { app.CMDExecutaDezGeracoes(); }
void GI::ExecutaMaisCemGeracoes()  { app.CMDExecutaCemGeracoes(); }
void GI::ExecutaAteUltimaGeracao() { app.CMDExecutaTodasGeracoes(); }
void GI::GeraPontosBase()          { app.CMDGerarPontosBase(); }
