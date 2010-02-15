/*
 * Cromossomo.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef CROMOSSOMO_H_
#define CROMOSSOMO_H_

class Cromossomo
{
public:
	~Cromossomo();
	Cromossomo(double posX,double posY);

	const double PosicaoX() { return posicaoX; }
	const double PosicaoY() { return posicaoY; }

private:
	double posicaoX;
	double posicaoY;
};




#endif /* CROMOSSOMO_H_ */
