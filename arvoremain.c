#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

int main() 
{
        int32_t t, x, indice;
        struct arvoreB *arv;
        
        printf("Insira um valor para t (minimo 2):\n");
        scanf("%d", &t);
        
        arv = criarArvoreB(t);
        if (!arv)
                return 1;
        
        do {
                printf("Insira um elemento (-1 para sair): ");
                scanf("%d", &x);
                if (x == -1)
                        break;
                printf(" ");
                inserirArvoreB(arv, x);
                imprimirArvoreB(arv);
                printf("\n");
                imprimirEmOrdem(arv);
                printf("\n");
        } while (x != -1);

        printf("Qual elemento deseja buscar? ");

        scanf("%d", &x);

        if (x < 0)
                return 1;
        
        printf("\n");

        if (buscarArvoreB(arv, x, &indice)) {
                printf("A chave %d foi encontrada com sucesso e esta no indice %d de seu nodo.", x, indice);
        } else {
                printf("A chave %d nao foi encontrada.", x);
        }

        deletarArvore(arv);
  
        return 0;
}
