#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

int main() {
    int32_t t;
    scanf("%d", &t);
    printf("\n");

  struct arvoreB *arv = criarArvoreB(t);
  
    int32_t x;
    do {
        scanf("%d", &x);
        printf(" ");
        inserirArvoreB(arv, x);
        imprimirArvoreB(arv);
        imprimirEmOrdem(arv);
        printf("\n");
    } while (x != -1);

    deletarArvore(arv);
  
    return 0;
}
