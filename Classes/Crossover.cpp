/*
 * Crossover.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#include "Crossover.h"

//#include <vcl.h>
#include "Math.h"
#include <stdlib.h>
#include "Mutacao.h"

////////////////////////////////////////////////////////////////////////////////

Populacao Crossover::CruzaAleatoria(Populacao pop,int taxaCrossover,int taxaMutacao)
{
   Populacao novaPop;

   while (pop.NumeroDeIndividuos()) {
      int valorSorteado= rand() % 101;

      Cromossomo cromossomoA= pop.individuos.front();
      pop.individuos.erase(pop.individuos.begin());

      if (pop.NumeroDeIndividuos()) {
         int elementoSort= rand() % pop.individuos.size();
         Cromossomo cromossomoB= pop.individuos.at(elementoSort);
         pop.individuos.erase(pop.individuos.begin() + elementoSort);
         if (valorSorteado < taxaCrossover) {
            Cromossomo newA= Cruza(cromossomoA,cromossomoB);
            Cromossomo newB= Cruza(cromossomoB,cromossomoA);

            int sorteio= (rand() % 101);
            newA= ( sorteio < taxaMutacao ) ?  Mutacao::Mutar(newA): newA;
            sorteio= (rand() % 101);
            newB= (sorteio < taxaMutacao)?  Mutacao::Mutar(newB): newB;

            novaPop.InsereIndividuo(newA);
            novaPop.InsereIndividuo(newB);
         } else {
            novaPop.InsereIndividuo(cromossomoA);
            novaPop.InsereIndividuo(cromossomoB);
         }
      } else {
         Cromossomo cromossomoB= cromossomoA;
         if (valorSorteado < taxaCrossover) {
            Cromossomo newA= Cruza(cromossomoA,cromossomoB);
            int sorteio= (rand() % 101);
            newA= (sorteio < taxaMutacao)?  Mutacao::Mutar(newA): newA;

            novaPop.InsereIndividuo(newA);
         } else {
            novaPop.InsereIndividuo(cromossomoA);
         }
      }
   }

   return novaPop;
}

////////////////////////////////////////////////////////////////////////////////

Populacao Crossover::CruzaSequencial(Populacao pop,int taxaCrossover,int taxaMutacao)
{
   Populacao novaPop;

   while (pop.NumeroDeIndividuos()) {
      int valorSorteado= rand() % 101;

      Cromossomo cromossomoA= pop.individuos.front();
      pop.individuos.erase(pop.individuos.begin());

      if (pop.NumeroDeIndividuos()) {
         Cromossomo cromossomoB= pop.individuos.front();
         pop.individuos.erase(pop.individuos.begin());
         if (valorSorteado < taxaCrossover) {
            Cromossomo newA= Cruza(cromossomoA,cromossomoB);
            Cromossomo newB= Cruza(cromossomoB,cromossomoA);

            int sorteio= (rand() % 101);
            newA= ( sorteio < taxaMutacao ) ?  Mutacao::Mutar(newA): newA;
            sorteio= (rand() % 101);
            newB= (sorteio < taxaMutacao)?  Mutacao::Mutar(newB): newB;

            novaPop.InsereIndividuo(newA);
            novaPop.InsereIndividuo(newB);
         } else {
            novaPop.InsereIndividuo(cromossomoA);
            novaPop.InsereIndividuo(cromossomoB);
         }
      } else {
         Cromossomo cromossomoB= cromossomoA;
         if (valorSorteado < taxaCrossover) {
            Cromossomo newA= Cruza(cromossomoA,cromossomoB);
            int sorteio= (rand() % 101);
            newA= (sorteio < taxaMutacao)?  Mutacao::Mutar(newA): newA;

            novaPop.InsereIndividuo(newA);
         } else {
            novaPop.InsereIndividuo(cromossomoA);
         }
      }
   }

   return novaPop;
}

////////////////////////////////////////////////////////////////////////////////

Cromossomo Crossover::Cruza(Cromossomo individuoA,Cromossomo individuoB)
{
   int posAX= static_cast<int>(individuoA.PosicaoX());
   int posAY= static_cast<int>(individuoA.PosicaoY());
   int posBX= static_cast<int>(individuoB.PosicaoX());
   int posBY= static_cast<int>(individuoB.PosicaoY());
	int deltaX= abs(posAX - posBX);
	int deltaY= abs(posAY - posBY);

	int acrescentarMenorX= (deltaX) ? rand() % deltaX : 0;
	int acrescentarMenorY= (deltaY)? rand() % deltaY : 0;

	double novaPosicaoX= (individuoA.PosicaoX() < individuoB.PosicaoX()) ?
								(individuoA.PosicaoX() + acrescentarMenorX) :
								(individuoB.PosicaoX() + acrescentarMenorX);

	double novaPosicaoY= (individuoA.PosicaoY() < individuoB.PosicaoY()) ?
								(individuoA.PosicaoY() + acrescentarMenorY) :
								(individuoB.PosicaoY() + acrescentarMenorY);

	return Cromossomo(novaPosicaoX,novaPosicaoY);
}

////////////////////////////////////////////////////////////////////////////////

