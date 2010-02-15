/*
 * AGUtil.h
 *
 *  Created on: Jul 8, 2008
 *      Author: alvaro
 */

#ifndef AGUTIL_H_
#define AGUTIL_H_

#include "../Classes/Ponto.h"
#include "../Classes/Fitness.h"
#include "../Classes/Populacao.h"
#include "../Classes/Cromossomo.h"

class AGUtil
{
public:

   static int Fatorial(Populacao& pop);
   static double FitnessMelhorIndividuo(Populacao& pop,Fitness& fit);
   static double FitnessPiorIndividuo(Populacao& pop,Fitness& fit);
   static double FitnessMediaIndividuos(Populacao& pop,Fitness& fit);
   static double FitnessSomaDosFitness(Populacao&pop,Fitness& fit);
   static Ponto GeraPontoAleatorio(int minX,int maxX,int minY,int maxY);
	static Cromossomo GeraIndividuoAleatorio(int minX,int maxX,int minY,int maxY);
   static Cromossomo MelhorIndividuo(Populacao& pop,Fitness& fit);
   static Cromossomo PiorIndividuo(Populacao& pop,Fitness& fit);
   static Cromossomo RetiraERetornaMelhorIndividuo(Populacao& pop,Fitness& fit);
   static void RetiraEColocaElitista(Populacao& popCruzada,Populacao& popElitista,Fitness& fit);

   //static void CruzamentoPopulacao(Populacao& pop,int taxaCrossover);
   //static void MutacaoPopulacao(Populacao& pop,int taxaMutacao);

private:
	AGUtil();
};


#endif /* AGUTIL_H_ */
