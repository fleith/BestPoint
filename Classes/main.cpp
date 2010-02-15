/*
 * main.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#include <iostream>

#include "Cromossomo.h"
#include "Crossover.h"
#include "Fitness.h"
#include "Mutacao.h"
#include "Ponto.h"
#include "Populacao.h"
#include "Selecao.h"

int main(int argc,char* argv[])
{
	srand(time(0));

	Cromossomo c1(1,40);
	Cromossomo c2(10,28);
	Cromossomo c3(32,15);
	Cromossomo c4(72,90);

	Ponto p1(50,50);
	Ponto p2(70,70);

	Populacao pop;
	pop.InsereIndividuo(c1);
	pop.InsereIndividuo(c2);
	pop.InsereIndividuo(c3);
	pop.InsereIndividuo(c4);

	Fitness fit;
	fit.InserePonto(p1);

	Selecao seleciona(fit);
	Populacao selecionados= seleciona.SelecionaPorElitismo(pop);



	//Cromossomo csaida= Crossover::Cruza(crom1,crom2);
	//Cromossomo mutado= Mutacao::Mutar(csaida);

}
