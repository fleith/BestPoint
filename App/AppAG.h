/*
 * AppAG.h
 *
 *  Created on: Jul 8, 2008
 *      Author: alvaro
 */

#ifndef APPAG_H_
#define APPAG_H_

#include "../Classes/Fitness.h"
#include "../Classes/Populacao.h"

class AppAG
{
public:
	~AppAG();
	AppAG();

	void CMDInicializarApp();

	void CMDGeraPopulacaoAuto();
	void CMDGeraPopulacaoManual();

	void CMDExecutaUmaGeracao();
	void CMDExecutaDezGeracoes();
	void CMDExecutaCemGeracoes();
	void CMDExecutaTodasGeracoes();

   void CMDMostraPopulacaoTela();
   void CMDMostraMelhorPiorIndividuoTela();

   void CMDGerarPontosBase();

private:
   Fitness fitness;

	std::vector<Populacao> populacoes;
   std::vector<Populacao>::iterator itPopulacao;

	double maximoX;
	double minimoX;
	double maximoY;
	double minimoY;

	int taxaCrossover;
	int taxaMutacao;
	int numeroIndividuos;
	int numeroMaxGeracoes;
   int numeroGeracoesExecutadas;

	bool integridadeOk;

   void ExecutaPassosAG();
	void VerificaIntegridadeDosDados();
   int AjustaPosXEmRelacaoAoTamanhoJanela(double posX);
   int AjustaPosYEmRelacaoAoTamanhoJanela(double posY);
};

extern AppAG app;

#endif /* APPAG_H_ */
