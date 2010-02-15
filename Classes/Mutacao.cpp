/*
 * Mutacao.cpp
 *
 *  Created on: Jul 3, 2008
 *      Author: alvaro
 */

#include "Mutacao.h"
#include <stdlib.h>

Cromossomo Mutacao::Mutar(Cromossomo cromossomo)
{
   int sorteio= (rand() % 101);
   if ( sorteio > 75) {
      int sortMenosA= rand() % (static_cast<int>(cromossomo.PosicaoX())+1);
      int sortMenosB= rand() % (static_cast<int>(cromossomo.PosicaoY())+1);
      return Cromossomo(cromossomo.PosicaoX() - sortMenosA,cromossomo.PosicaoY() - sortMenosB);
   } else if (sorteio > 50) {
      int sortMaisA= rand() % (static_cast<int>(cromossomo.PosicaoX())+1);
      int sortMaisB= rand() % (static_cast<int>(cromossomo.PosicaoY())+1);
      return Cromossomo(cromossomo.PosicaoX() + sortMaisA,cromossomo.PosicaoY() + sortMaisB);
   } else if (sorteio > 25) {
      int sortMaisA= rand() % (static_cast<int>(cromossomo.PosicaoX())+1);
      int sortMenosB= rand() % (static_cast<int>(cromossomo.PosicaoY())+1);
      return Cromossomo(cromossomo.PosicaoX() + sortMaisA,cromossomo.PosicaoY() - sortMenosB);
   } else if (sorteio > 5) {
      int sortMenosA= rand() % (static_cast<int>(cromossomo.PosicaoX())+1);
      int sortMaisB= rand() % (static_cast<int>(cromossomo.PosicaoY())+1);
      return Cromossomo(cromossomo.PosicaoX() - sortMenosA,cromossomo.PosicaoY() + sortMaisB);
   } else
      return Cromossomo(cromossomo.PosicaoY(),cromossomo.PosicaoX());
}


