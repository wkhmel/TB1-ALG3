#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

int main() 
{
        int32_t t;
        scanf("%d", &t);
        printf("\n");

        struct arvoreB *arv = criarArvoreB(t);
  
        int32_t x;
        do {
                printf("Insira um elemento: ");
                scanf("%d", &x);
                printf(" ");
                inserirArvoreB(arv, x);
                imprimirArvoreB(arv);
                imprimirEmOrdem(arv);
                printf("\n");
        } while (x != -1);

        printf("Qual elemento deseja buscar? ");
        scanf("%d", &x);
        printf("\n");

        int32_t *indice = malloc(sizeof(int32_t));
        
        if (!indice) {
                fprintf("Falha ao alocar memoria.\n");
                exit(1);
        }

        if (BuscarArvoreB(arv, x, indice)) {
                printf("A chave %d foi encontrada com sucesso e esta no indice %d de seu nodo.", x, indice);
        }

        free(indice);
        deletarArvore(arv);
  
        return 0;
}
