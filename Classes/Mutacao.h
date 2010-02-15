/*
 * Mutacao.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef MUTACAO_H_
#define MUTACAO_H_

#include "Cromossomo.h"

class Mutacao
{
public:
	static Cromossomo Mutar(Cromossomo cromossomo);

private:
	Mutacao();
};

#endif /* MUTACAO_H_ */
