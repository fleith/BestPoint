/*
 * Selecao.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#include "Selecao.h"

#include <stdlib.h>
#include <algorithm>
#include "AGUtil.h"

////////////////////////////////////////////////////////////////////////////////

Selecao::Selecao(Fitness fit):fitness(fit)
{
}

////////////////////////////////////////////////////////////////////////////////

Populacao Selecao::SelecionaPorElitismo(Populacao populacao)
{
	std::vector<Cromossomo>& individuos= populacao.individuos;
	std::sort(individuos.begin(),individuos.end(),fitness);

	int trintaPorcentoDosMelhores= individuos.size() / 3;

	std::vector<Cromossomo> selecionados;
	selecionados.insert(selecionados.begin(),
							  individuos.begin(),
							  individuos.begin() + trintaPorcentoDosMelhores);

	while (selecionados.size() != individuos.size()) {
		int elementoSorteado= rand() % individuos.size();
		selecionados.push_back(individuos.at(elementoSorteado));
	}

	return Populacao(selecionados);
}

////////////////////////////////////////////////////////////////////////////////

Populacao Selecao::SelecionaPorEstadoEstacionario(Populacao populacao)
{
	std::vector<Cromossomo>& individuos= populacao.individuos;
	std::sort(individuos.begin(),individuos.end(),fitness);

	int cincoPorcentoDosMelhores= individuos.size() / 20;

	std::vector<Cromossomo> selecionados;
	selecionados.insert(selecionados.end(),
							  individuos.begin(),
							  individuos.end() - cincoPorcentoDosMelhores);

	selecionados.insert(selecionados.end(),
							  individuos.begin(),
							  individuos.begin() + cincoPorcentoDosMelhores);

	return Populacao(selecionados);
}

////////////////////////////////////////////////////////////////////////////////

Populacao Selecao::SelecionaPorClassificacao(Populacao populacao)
{
   std::vector<Cromossomo>& individuos= populacao.individuos;
	std::sort(individuos.begin(),individuos.end(),fitness);

   int somaLinear= AGUtil::SomaLinear(populacao);

   std::vector<Cromossomo> selecionados;
   while (selecionados.size() != individuos.size()) {
      int numeroSorteado= rand() % static_cast<int>(somaLinear);
      int somaAcumulada= 0;
      for(std::vector<Cromossomo>::iterator it= individuos.begin(); it != individuos.end(); it++) {
         somaAcumulada+= (individuos.end() - it);
         if (numeroSorteado < somaAcumulada) {
            selecionados.push_back(*it);
            break;
         }
      }
   }

   return Populacao(selecionados);
}

////////////////////////////////////////////////////////////////////////////////

Populacao Selecao::SelecionaHibrido(Populacao populacao)
{
	std::vector<Cromossomo>& individuos= populacao.individuos;
	std::sort(individuos.begin(),individuos.end(),fitness);

	int trintaPorcentoDosMelhores= individuos.size() / 3;

	std::vector<Cromossomo> selecionados;
	selecionados.insert(selecionados.end(),
							  individuos.begin(),
							  individuos.begin() + trintaPorcentoDosMelhores);

	selecionados.insert(selecionados.end(),
							  individuos.begin(),
							  individuos.begin() + trintaPorcentoDosMelhores);


	while (selecionados.size() != individuos.size()) {
		int elementoSorteado= rand() % individuos.size();
		selecionados.push_back(individuos.at(elementoSorteado));
	}

	return Populacao(selecionados);
}

////////////////////////////////////////////////////////////////////////////////

Populacao Selecao::SelecionaPorRoleta(Populacao populacao)
{
	std::vector<Cromossomo>& individuos= populacao.individuos;
	std::sort(individuos.begin(),individuos.end(),fitness);

   std::vector<double> fitnessCache;
   fitnessCache.reserve(individuos.size());
   for(std::vector<Cromossomo>::iterator it= individuos.begin(); it != individuos.end(); it++) {
      fitnessCache.push_back(fitness.FitnessCromossomo(*it));
   }

   const int aumentoValor= 100000;
   double somaFitness= 0;
   for(std::vector<double>::iterator it= fitnessCache.begin(); it != fitnessCache.end(); it++) {
      somaFitness+= (*it);
   }
   somaFitness*= aumentoValor;

   std::vector<Cromossomo> selecionados;
   while (selecionados.size() != individuos.size()) {
      int numeroSorteado= rand() % static_cast<int>(somaFitness);
      int somaDosFitness= 0;
      for(std::vector<Cromossomo>::size_type i= 0; i < individuos.size(); i++) {
         somaDosFitness+= fitnessCache[i] * aumentoValor;
         if (numeroSorteado < somaDosFitness) {
            selecionados.push_back(individuos[i]);
            break;
         }
      }
   }
 /*
   Este processo pode ser descrito pelo seguinte algoritmo:

   1. [Soma] Calcule a soma dos valores de adequa��o de todos os cromossomas da popula��o - soma S.
   2. [Sele��o] Gere um n�mero aleat�rio no intervalo (0,S) - r.
   3. [Repeti��o] Percorra toda a popula��o e some a adequa��o de 0 - soma s. Quando a soma s for maior que r, pare e retorne o cromossoma atual.

   � claro, o passo 1 somente � realizado uma vez para cada popula��o.
 */
 
	return Populacao(selecionados);
}

////////////////////////////////////////////////////////////////////////////////








