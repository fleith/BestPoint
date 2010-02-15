/*
 * Populacao.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef POPULACAO_H_
#define POPULACAO_H_

#include <vector>
#include "Cromossomo.h"

class Populacao
{
public:
	~Populacao();
	Populacao();
	Populacao(std::vector<Cromossomo>& populacao);

	void InsereIndividuo(Cromossomo cromossomo);

   int NumeroDeIndividuos() { return individuos.size(); }
   Cromossomo operator[](int pos) { return individuos[pos]; }

private:
	std::vector<Cromossomo> individuos;

	friend class Selecao;
   friend class AGUtil;
   friend class Crossover;
};


#endif /* POPULACAO_H_ */
