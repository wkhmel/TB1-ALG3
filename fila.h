#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>
#include "arvoreB.h"

/* descreve uma fila */
struct fila_t
{
        struct nodo **nodos; /* vetor de nodos */            
        int num; /* número de itens na fila */
};

/* cria uma fila vazia, retornando um ponteiro para a fila criada ou NULL se erro. */
struct fila_t *fila_cria ();

/* libera todas as estruturas de dados da fila, inclusive os itens. */
/* retorna NULL */
struct fila_t *fila_destroi (struct fila_t *f);

/* insere um nodo no final da fila seguindo a politica FIFO. */
/* retorna 1 se tiver sucesso ou 0 se falhar. */
int fila_insere (struct fila_t *f, struct nodo *item);

/* retira o primeiro nodo da fila e o devolve, retornando 1 em sucesso e 0 c.c. */
int fila_retira (struct fila_t *f, struct nodo *item);

/* retorna o número de itens na fila ou -1 em caso de erro. */
int fila_tamanho (struct fila_t *f);

/* imprime o conteúdo da fila */
void fila_imprime (struct fila_t *f);

#endif
