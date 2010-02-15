/*
 * AGUtil.cpp
 *
 *  Created on: Jul 8, 2008
 *      Author: alvaro
 */

#include "AGUtil.h"


#include "../Classes/Crossover.h"
#include <stdlib.h>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

double AGUtil::FitnessMelhorIndividuo(Populacao& pop,Fitness& fit)
{
   if (pop.individuos.empty()) return 0;
   std::vector<Cromossomo>& individuos= pop.individuos;
   std::sort(individuos.begin(),individuos.end(),fit);

   return fit.FitnessCromossomo(individuos.front());
}

////////////////////////////////////////////////////////////////////////////////

double AGUtil::FitnessPiorIndividuo(Populacao& pop,Fitness& fit)
{
   if (pop.individuos.empty()) return 0;
   std::vector<Cromossomo>& individuos= pop.individuos;
   std::sort(individuos.begin(),individuos.end(),fit);

   return fit.FitnessCromossomo(individuos.back());
}

////////////////////////////////////////////////////////////////////////////////

Cromossomo AGUtil::RetiraERetornaMelhorIndividuo(Populacao& pop,Fitness& fit)
{
   if (pop.individuos.empty()) return Cromossomo(0,0);

   std::vector<Cromossomo>& individuos= pop.individuos;
   std::sort(individuos.begin(),individuos.end(),fit);

   Cromossomo melhor= individuos.front();
   individuos.erase(individuos.begin());

   return melhor;
}

////////////////////////////////////////////////////////////////////////////////

double AGUtil::FitnessMediaIndividuos(Populacao& pop,Fitness& fit)
{
   std::vector<Cromossomo>& individuos= pop.individuos;

   double totalFitness= 0;
   for(std::vector<Cromossomo>::iterator it=individuos.begin(); it != individuos.end(); it++) {
      totalFitness+= fit.FitnessCromossomo(*it);
   }

   double mediaFitness= totalFitness / individuos.size();

   return mediaFitness;
}

////////////////////////////////////////////////////////////////////////////////

double AGUtil::FitnessSomaDosFitness(Populacao&pop,Fitness& fit)
{
   std::vector<Cromossomo>& individuos= pop.individuos;

   double totalFitness= 0;
   for(std::vector<Cromossomo>::iterator it=individuos.begin(); it != individuos.end(); it++) {
      totalFitness+= fit.FitnessCromossomo(*it);
   }

   return totalFitness;
}

////////////////////////////////////////////////////////////////////////////////

static int fatorial(int value)
{
   if (value)
      return (value + fatorial(value - 1));
   else
      return value;
}

////////////////////////////////////////////////////////////////////////////////

int AGUtil::Fatorial(Populacao& pop)
{
  int numFat= pop.NumeroDeIndividuos();

  return fatorial(numFat);
}

////////////////////////////////////////////////////////////////////////////////

Cromossomo AGUtil::MelhorIndividuo(Populacao& pop,Fitness& fit)
{
   std::vector<Cromossomo>& individuos= pop.individuos;
   std::sort(individuos.begin(),individuos.end(),fit);

   return individuos.front();
}

////////////////////////////////////////////////////////////////////////////////

Cromossomo AGUtil::PiorIndividuo(Populacao& pop,Fitness& fit)
{
   std::vector<Cromossomo>& individuos= pop.individuos;
   std::sort(individuos.begin(),individuos.end(),fit);

   return individuos.back();
}

////////////////////////////////////////////////////////////////////////////////

void AGUtil::RetiraEColocaElitista(Populacao& popCruzada,Populacao& popElitista,Fitness& fit)
{
   std::vector<Cromossomo>& individuos= popCruzada.individuos;
   std::sort(individuos.begin(),individuos.end(),fit);

   int individuoMediano= static_cast<int>(individuos.size()/2);
   individuos.erase(individuos.begin()+individuoMediano);

   std::vector<Cromossomo>& indiEli= popElitista.individuos;
   if (!indiEli.empty()) individuos.push_back(indiEli.front());
}

////////////////////////////////////////////////////////////////////////////////

Ponto AGUtil::GeraPontoAleatorio(int minX,int maxX,int minY,int maxY)
{
   int valorX= (rand() % (maxX-minX)) + minX;
	int valorY= (rand() % (maxY-minY)) + minY;

	return Ponto(valorX,valorY);
}


////////////////////////////////////////////////////////////////////////////////

Cromossomo AGUtil::GeraIndividuoAleatorio(int minX, int maxX, int minY, int maxY)
{
	int valorX= (rand() % (maxX-minX)) + minX;
	int valorY= (rand() % (maxY-minY)) + minY;

	return Cromossomo(valorX,valorY);
}

////////////////////////////////////////////////////////////////////////////////
/*
void AGUtil::CruzamentoPopulacao(Populacao& pop,int taxaCrossover)
{
   Populacao popAux= pop;
   //pop= Crossover::CruzaSequencial(popAux,taxaCrossover);
   pop= Crossover::CruzaAleatoria(popAux,taxaCrossover);
}

////////////////////////////////////////////////////////////////////////////////

void AGUtil::MutacaoPopulacao(Populacao& pop,int taxaMutacao)
{
   //in
}
 */
////////////////////////////////////////////////////////////////////////////////
