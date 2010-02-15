/*
 * Calculo.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#include "Calculo.h"

#include "math.h"

////////////////////////////////////////////////////////////////////////////////

double Calculo::DistanciaPontos(Ponto & pontoA, Ponto & pontoB)
{
	double deltaX= fabs(pontoA.PosicaoX() - pontoB.PosicaoX());
	double deltaY= fabs(pontoA.PosicaoY() - pontoB.PosicaoY());

	double deltaXElevado2= pow(deltaX,2);
	double deltaYElevado2= pow(deltaY,2);

	double distanciaEntreOsPontos= sqrt(deltaXElevado2 + deltaYElevado2);

	return distanciaEntreOsPontos;
}

////////////////////////////////////////////////////////////////////////////////

double Calculo::DesvioMedio(std::vector<double>& distancias)
{
   double somaDistancias= 0;
   for(std::vector<double>::iterator it= distancias.begin(); it != distancias.end(); it++) {
      somaDistancias+= (*it);
   }
   double mediaDistancias= somaDistancias / distancias.size();

   double somaDesvio= 0;
   for(std::vector<double>::iterator it= distancias.begin(); it != distancias.end(); it++) {
      somaDesvio+= fabs((*it) - mediaDistancias);
   }
   //double desvioMedio= somaDesvio / distancias.size();

   return somaDesvio;//desvioMedio;
}

////////////////////////////////////////////////////////////////////////////////
