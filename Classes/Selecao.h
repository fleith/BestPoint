/*
 * Selecao.h
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#ifndef SELECAO_H_
#define SELECAO_H_

#include "Fitness.h"
#include "Populacao.h"

class Selecao
{
public:
	Selecao(Fitness fit);

	Populacao SelecionaHibrido(Populacao populacao);
	Populacao SelecionaPorElitismo(Populacao populacao);
	Populacao SelecionaPorEstadoEstacionario(Populacao populacao);
	Populacao SelecionaPorClassificacao(Populacao populacao);
	Populacao SelecionaPorRoleta(Populacao populacao);

private:
	Fitness fitness;

};

#endif /* SELECAO_H_ */
