/*
 * Fitness.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef FITNESS_H_
#define FITNESS_H_

#include <vector>
#include "Ponto.h"
#include "Cromossomo.h"

class Fitness
{
public:
	~Fitness();
	Fitness();

	void InserePonto(Ponto pt);

   int NumeroDePontos() { return pontos.size(); }
   void ExcluirPontos() { pontos.clear(); }
   Ponto operator[](int pos) { return pontos[pos]; }

	double FitnessCromossomo(Cromossomo& cromossomo);

	bool operator() (Cromossomo& A,Cromossomo& B);

   void SetFatorDistancia(double fator);
   void SetFatotDistribuicao(double fator);
   void SetNumeroNormalizador(double numero);

private:
   std::vector<Ponto> pontos;

   double fatorDistancia;
   double fatorDistribuicao;

   double normalizador;
};

#endif /* FITNESS_H_ */
