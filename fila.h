#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>

/* representa cada elemento da fila. */
/* contém cada nodo como item e um ponteiro para o próximo elemento */
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
struct fila_t *criarFila ();

/* libera todas as estruturas de dados da fila, inclusive os itens. */
/* retorna NULL */
void destruirFila (struct fila_t *f);

/* insere um nodo no final da fila seguindo a politica FIFO. */
void inserirFila (struct fila_t *f, struct nodo *item);

/* retira o primeiro nodo da fila e o retorna */
struct nodo *retirarFila (struct fila_t *f);

#endif
