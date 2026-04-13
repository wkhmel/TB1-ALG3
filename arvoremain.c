#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

int main() {
  int32_t t;
  scanf("%d", &t);

  struct arvoreB *arv = criarArvoreB(t);

  inserirArvoreB(arv, 67);
  inserirArvoreB(arv, 89);
  inserirArvoreB(arv, 44);
  inserirArvoreB(arv, 11);
  inserirArvoreB(arv, 10);
  inserirArvoreB(arv, 99);

  imprimirNodoLargura(arv->raiz);

  return 0;
}
