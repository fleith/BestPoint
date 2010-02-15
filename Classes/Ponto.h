/*
 * Ponto.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef PONTO_H_
#define PONTO_H_

#include "Cromossomo.h"

class Ponto
{
public:
	~Ponto();
 	Ponto(Cromossomo& cromossomo);
	Ponto(double posX,double posY);

	double PosicaoX();
	double PosicaoY();

private:
	double posicaoX;
	double posicaoY;
};

#endif /* PONTO_H_ */
