/*
 * Calculo.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef CALCULO_H_
#define CALCULO_H_

#include <vector>
#include "Ponto.h"

class Calculo
{
public:

   static double DesvioMedio(std::vector<double>& distancias);
	static double DistanciaPontos(Ponto& pontoA,Ponto& pontoB);

private:
	Calculo();
};

#endif /* CALCULO_H_ */
