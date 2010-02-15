/*
 * Fitness.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */
#include "Fitness.h"

#include "Calculo.h"

////////////////////////////////////////////////////////////////////////////////

Fitness::~Fitness()
{
}

////////////////////////////////////////////////////////////////////////////////

Fitness::Fitness()
{
}

////////////////////////////////////////////////////////////////////////////////

void Fitness::InserePonto(Ponto pt)
{
	pontos.push_back(pt);
}

////////////////////////////////////////////////////////////////////////////////


void Fitness::SetFatorDistancia(double fator)
{
   fatorDistancia= fator;
}

////////////////////////////////////////////////////////////////////////////////

void Fitness::SetFatotDistribuicao(double fator)
{
   fatorDistribuicao= fator;
}

////////////////////////////////////////////////////////////////////////////////

void Fitness::SetNumeroNormalizador(double numero)
{
   normalizador= numero;
}

////////////////////////////////////////////////////////////////////////////////

double Fitness::FitnessCromossomo(Cromossomo & cromossomo)
{
	Ponto posicaoCromossomo(cromossomo);

	double somaDistancias= 0;
   std::vector<double> distancias;
	for(std::vector<Ponto>::iterator it= pontos.begin(); it != pontos.end(); it++) {
		 double distanciaPonto= Calculo::DistanciaPontos((*it),posicaoCromossomo);
       distancias.push_back(distanciaPonto);
       somaDistancias+= distanciaPonto;
	}

   double desvioMedio= Calculo::DesvioMedio(distancias);
   double numerador= normalizador * (pontos.size() * 2);
	double maiorMelhor= numerador/((somaDistancias * fatorDistancia) + (desvioMedio * fatorDistribuicao));

	return maiorMelhor;
}

////////////////////////////////////////////////////////////////////////////////

bool Fitness::operator ()(Cromossomo & A, Cromossomo & B)
{
	return FitnessCromossomo(A) > FitnessCromossomo(B);
}

////////////////////////////////////////////////////////////////////////////////

