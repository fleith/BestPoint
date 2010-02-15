/*
 * AppAG.cpp
 *
 *  Created on: Jul 8, 2008
 *      Author: alvaro
 */

#include "AppAG.h"

////////////////////////////////////////////////////////////////////////////////
AppAG app;
////////////////////////////////////////////////////////////////////////////////

#include "../Util/AGUtil.h"
#include "../Classes/Selecao.h"
#include "../Classes/Crossover.h"
#include "../Interface/GerenteInterfaceAG.h"


////////////////////////////////////////////////////////////////////////////////

AppAG::~AppAG()
{
}

////////////////////////////////////////////////////////////////////////////////

AppAG::AppAG()
{
	integridadeOk= false;
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDInicializarApp()
{
	maximoX= GI::ValorMaximoEixoX();
	maximoY= GI::ValorMaximoEixoY();
	minimoX= GI::ValorMinimoEixoX();
	minimoY= GI::ValorMinimoEixoY();

	numeroIndividuos= GI::TamanhoPopulacao();
	numeroMaxGeracoes= GI::NumeroMaximoDeGeracoes();
	taxaCrossover= GI::PercentualCrossover();
	taxaMutacao= GI::PercentualMutacao();

   fitness.SetFatorDistancia(GI::FatorDistancia());
   fitness.SetFatotDistribuicao(GI::FatorDistribuicao());
   double numeroDivisaoFitness= (maximoX - minimoX) + (maximoY - minimoY);
   fitness.SetNumeroNormalizador(numeroDivisaoFitness);

	VerificaIntegridadeDosDados();
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDGeraPopulacaoAuto()
{
	if(integridadeOk == false) return;

	Populacao popInicial;
	for(int i= 1; i <= GI::TamanhoPopulacao(); i++) {
		popInicial.InsereIndividuo(AGUtil::GeraIndividuoAleatorio(minimoX,maximoX,
																					 minimoY,maximoY));
	}

   numeroGeracoesExecutadas= numeroMaxGeracoes;

   populacoes.clear();
	populacoes.push_back(popInicial);
   itPopulacao= populacoes.begin();
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDGeraPopulacaoManual()
{
	if(integridadeOk == false) return;
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDExecutaUmaGeracao()
{
	if(integridadeOk == false) return;
   if (numeroGeracoesExecutadas == 0) return;

   ExecutaPassosAG();
   GI::AtualizaInformacoesJanela();
   numeroGeracoesExecutadas--;
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDExecutaDezGeracoes()
{
	if(integridadeOk == false) return;

   for (int i= 1; i <= 10; i++) {
      CMDExecutaUmaGeracao();
   }
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDExecutaCemGeracoes()
{
	if(integridadeOk == false) return;

   for (int i= 1; i <= 100; i++) {
      CMDExecutaUmaGeracao();
   }
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDExecutaTodasGeracoes()
{
	if(integridadeOk == false) return;

   for (int i= 1; i <= numeroMaxGeracoes; i++) {
      CMDExecutaUmaGeracao();
   }
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDMostraPopulacaoTela()
{
   if(integridadeOk == false) return;

   GI::LimpaTelaPontos();

   if (!populacoes.empty()) {
      Populacao& popAtual= populacoes.back(); //(*itPopulacao);
      for (int i= 0; i < popAtual.NumeroDeIndividuos(); i++) {
         int posAjustadaX= AjustaPosXEmRelacaoAoTamanhoJanela(popAtual[i].PosicaoX());
         int posAjustadaY= AjustaPosYEmRelacaoAoTamanhoJanela(popAtual[i].PosicaoY());
         GI::AdicionaPontoIndividuo(posAjustadaX,posAjustadaY);
      }

      if (popAtual.NumeroDeIndividuos()) {
         Cromossomo& pior= AGUtil::PiorIndividuo(populacoes.back(),fitness);
         int posAjustadaX= AjustaPosXEmRelacaoAoTamanhoJanela(pior.PosicaoX());
         int posAjustadaY= AjustaPosYEmRelacaoAoTamanhoJanela(pior.PosicaoY());
         GI::AdicionaPontoPiorIndividuo(posAjustadaX,posAjustadaY);

         Cromossomo& melhor= AGUtil::MelhorIndividuo(populacoes.back(),fitness);
         posAjustadaX= AjustaPosXEmRelacaoAoTamanhoJanela(melhor.PosicaoX());
         posAjustadaY= AjustaPosYEmRelacaoAoTamanhoJanela(melhor.PosicaoY());
         GI::AdicionaPontoMelhorIndividuo(posAjustadaX,posAjustadaY);
      }
   }

   for (int i= 0; i < fitness.NumeroDePontos(); i++) {
      int posAjustadaX= AjustaPosXEmRelacaoAoTamanhoJanela(fitness[i].PosicaoX());
      int posAjustadaY= AjustaPosYEmRelacaoAoTamanhoJanela(fitness[i].PosicaoY());
      GI::AdicionaPontoBase(posAjustadaX,posAjustadaY);
   }
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDMostraMelhorPiorIndividuoTela()
{
   if(integridadeOk == false) return;

   Populacao& popAtual= populacoes.back();//(*itPopulacao);

   if (popAtual.NumeroDeIndividuos()) {
      double fitMelhor= AGUtil::FitnessMelhorIndividuo(popAtual,fitness);
      double fitPior= AGUtil::FitnessPiorIndividuo(popAtual,fitness);
      double fitMedia= AGUtil::FitnessMediaIndividuos(popAtual,fitness);
      GI::AdicionaFitnessMelhorPiorEMediaIndividuo(fitMelhor,fitPior,fitMedia);
   }
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::CMDGerarPontosBase()
{
   if(integridadeOk == false) return;

   fitness.ExcluirPontos();
   for(int i= 1; i <= GI::NumeroDePontosBase(); i++) {
      fitness.InserePonto(AGUtil::GeraPontoAleatorio(minimoX,maximoX,
                                                     minimoY,maximoY));
   }   
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::VerificaIntegridadeDosDados()
{
	integridadeOk= true;
	if (maximoX < minimoX) integridadeOk= false;
	if (maximoY < minimoY) integridadeOk= false;
	if (numeroIndividuos <= 0) integridadeOk= false;
	if (numeroMaxGeracoes <= 0) integridadeOk= false;
	if ((taxaCrossover > 100) || (taxaCrossover < 0)) integridadeOk= false;
	if ((taxaMutacao > 100) || (taxaMutacao < 0)) integridadeOk= false;
}

////////////////////////////////////////////////////////////////////////////////

int AppAG::AjustaPosXEmRelacaoAoTamanhoJanela(double posX)
{
   const double tamanhoJanelaX= GI::LarguraJanelaDesenho() - 6;
   int deltaX= maximoX - minimoX;
   double relacaoJanela= tamanhoJanelaX / deltaX;

   return (((posX - minimoX) * relacaoJanela) + 3);
}

////////////////////////////////////////////////////////////////////////////////

int AppAG::AjustaPosYEmRelacaoAoTamanhoJanela(double posY)
{
   const double tamanhoJanelaY= GI::AlturaJanelaDesenho() - 6;
   int deltaY= maximoY - minimoY;
   double relacaoJanela= tamanhoJanelaY / deltaY;

   return (((posY - minimoY) * relacaoJanela) + 3);
}

////////////////////////////////////////////////////////////////////////////////

void AppAG::ExecutaPassosAG()
{
   Selecao selecao(fitness);
   TipoSelecao tpSel= GI::TipoDeSelecao();

   Cromossomo melhor(0,0);
   Populacao popSelecionada;
   switch (tpSel) {
      case ELITISMO:
         popSelecionada= selecao.SelecionaPorElitismo(populacoes.back());
         melhor= AGUtil::RetiraERetornaMelhorIndividuo(popSelecionada,fitness);
      break;
      case ROLETA:
         popSelecionada= selecao.SelecionaPorRoleta(populacoes.back());
      break;
      case CLASSIFICACAO:
         popSelecionada= selecao.SelecionaPorClassificacao(populacoes.back());
      break;
      case ESTACIONARIA:
         popSelecionada= selecao.SelecionaPorEstadoEstacionario(populacoes.back());
      break;
      case ALVAROS:
         popSelecionada= selecao.SelecionaHibrido(populacoes.back());
      break;
   }

   Populacao popCruzada;
   if (GI::TipoDeCruzamento() == ALEATORIO)
      popCruzada= Crossover::CruzaAleatoria(popSelecionada,taxaCrossover,taxaMutacao);
   else
      popCruzada= Crossover::CruzaSequencial(popSelecionada,taxaCrossover,taxaMutacao);

   if (tpSel == ELITISMO) popCruzada.InsereIndividuo(melhor);
   //AGUtil::RetiraEColocaElitista(popCruzada,popElitista,fitness);
   populacoes.push_back(popCruzada);
}

////////////////////////////////////////////////////////////////////////////////


