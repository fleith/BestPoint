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
   int baseX= static_cast<int>(cromossomo.PosicaoX());
   int baseY= static_cast<int>(cromossomo.PosicaoY());
   int rangeX= (baseX > 0) ? baseX + 1 : 1;
   int rangeY= (baseY > 0) ? baseY + 1 : 1;

   if ( sorteio > 75) {
      int sortMenosA= rand() % rangeX;
      int sortMenosB= rand() % rangeY;
      return Cromossomo(cromossomo.PosicaoX() - sortMenosA,cromossomo.PosicaoY() - sortMenosB);
   } else if (sorteio > 50) {
      int sortMaisA= rand() % rangeX;
      int sortMaisB= rand() % rangeY;
      return Cromossomo(cromossomo.PosicaoX() + sortMaisA,cromossomo.PosicaoY() + sortMaisB);
   } else if (sorteio > 25) {
      int sortMaisA= rand() % rangeX;
      int sortMenosB= rand() % rangeY;
      return Cromossomo(cromossomo.PosicaoX() + sortMaisA,cromossomo.PosicaoY() - sortMenosB);
   } else if (sorteio > 5) {
      int sortMenosA= rand() % rangeX;
      int sortMaisB= rand() % rangeY;
      return Cromossomo(cromossomo.PosicaoX() - sortMenosA,cromossomo.PosicaoY() + sortMaisB);
   } else
      return Cromossomo(cromossomo.PosicaoY(),cromossomo.PosicaoX());
}


