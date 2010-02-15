/*
 * Crossover.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef CROSSOVER_H_
#define CROSSOVER_H_

#include "Populacao.h"
#include "Cromossomo.h"

class Crossover
{
public:

   static Populacao CruzaAleatoria(Populacao pop,int taxaCrossover,int taxaMutacao);
   static Populacao CruzaSequencial(Populacao pop,int taxaCrossover,int taxaMutacao);
	static Cromossomo Cruza(Cromossomo individuoA,Cromossomo individuoB);

private:
	Crossover();
};


#endif /* CROSSOVER_H_ */
