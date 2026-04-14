#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

int main() {
  int32_t t;
  scanf("%d", &t);

  struct arvoreB *arv = criarArvoreB(t);

  int32_t x;
  do {
      scanf("%d", &x);
      inserirArvoreB(arv, x);
  } while (x != -1)
    
  imprimirArvoreB(arv);
  imprimirEmOrdem(arv);

  deletarArvore(arv);
  
  return 0;
}
