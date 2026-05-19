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
       
       	char ch = 'i';	
        do {
                printf("'i': inserir;\n");
		printf("'r': remover;\n");
		printf("'b': buscar;\n");
		printf("'s': sair;\n");

		printf("Qual operacao voce deseja executar? ");

		scanf(" %c", &ch);

		if (ch == 'i') {

			printf("Qual valor deseja inserir? ");
			scanf("%d", &x);
			printf("\n");

			inserirArvoreB(arv, x);
			printf("\n");
			imprimirArvoreB(arv);
			printf("\n");
			imprimirEmOrdem(arv);
			printf("\n");	
		} else if (ch == 'b') {

			printf("Qual elemento deseja buscar? ");
			scanf("%d", &x);
			printf("\n");
			
			if (buscarArvoreB(arv, x, &indice)) {
				printf("A chave %d foi encontrada com sucesso no indice %d de seu nodo.\n", x, indice);
			} else {
				printf("A chave %d nao foi encontrada.\n", x);
			}
		} else if (ch == 'r') {
		
			printf("Qual elemento deseja excluir? ");
			scanf("%d", &x);
			printf("\n");

			if (removerChaveArvoreB(arv, x)) {
				printf("A chave %d foi removida com sucesso.\n", x);
			} else {
				printf("A chave %d nao foi removida.\n", x);
			}

			imprimirArvoreB(arv);
			printf("\n");
			imprimirEmOrdem(arv);
			printf("\n");
		}

        } while (ch == 'i' || ch == 'r' || ch == 'b');

        deletarArvore(arv);

        return 0;
}
