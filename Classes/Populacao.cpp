/*
 * Populacao.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#include "Populacao.h"

////////////////////////////////////////////////////////////////////////////////

Populacao::~Populacao()
{
}

////////////////////////////////////////////////////////////////////////////////

Populacao::Populacao()
{
}

////////////////////////////////////////////////////////////////////////////////

Populacao::Populacao(std::vector<Cromossomo> & populacao):individuos(populacao)
{

}

////////////////////////////////////////////////////////////////////////////////

void Populacao::InsereIndividuo(Cromossomo cromossomo)
{
	individuos.push_back(cromossomo);
}

////////////////////////////////////////////////////////////////////////////////




