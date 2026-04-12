#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>

struct nodofila {
        struct nodo *item;
        struct nodofila *prox;
};

/* descreve uma fila */
struct fila_t
{
        struct nodofila *prim;            
        struct nodofila *ult; 
        int num; /* número de itens na fila */
};

/* cria uma fila vazia, retornando um ponteiro para a fila criada ou NULL se erro. */
struct fila_t *fila_cria ();

/* libera todas as estruturas de dados da fila, inclusive os itens. */
/* retorna NULL */
void fila_destroi (struct fila_t *f);

/* insere um nodo no final da fila seguindo a politica FIFO. */
void fila_insere (struct fila_t *f, struct nodofila *item);

/* retira o primeiro nodo da fila e o retorna */
struct nodo *fila_retira (struct fila_t *f);

/* retorna o número de itens na fila ou -1 em caso de erro. */
int fila_tamanho (struct fila_t *f);

#endif
