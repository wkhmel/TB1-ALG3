#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "arvoreB.h"

/* cria uma fila sem nada */
struct fila_t *fila_cria() {
        struct fila_t *vazia = malloc(sizeof(struct fila_t));
        verificaMemoria(vazia);
        
        vazia->prim = vazia->ult = NULL;
        vazia->num = 0;
        
        return vazia;
}

/* retorna uma fila vazia, com todos os elementos e estruturas destruidos */
void fila_destroi(struct fila_t *f) {
        if (f == NULL)
                return;
        
        struct nodofila *atual = f->prim;
        struct nodofila *aux_prox;
        
        while (atual != NULL) {
                aux_prox = atual->prox;
                free(atual);
                atual = aux_prox;
        }
        
        free(f);     
}

/* insere um elemento no fim da fila */
void fila_insere(struct fila_t *f, struct nodo *item) {
        if (!f)
                return;
        
        struct nodofila *novo = malloc(sizeof(struct nodofila));
        verificaMemoria(novo);
        
        novo->item = item;
        novo->prox = NULL;
        
        if (f->num == 0)
                f->prim = novo;
        else
                f->ult->prox = novo;
        
        f->ult = novo;
        f->num++;
}

/* retira um elemento do começo da fila, por ordem de chegada, e o retorna */
struct nodo *fila_retira(struct fila_t *f) {
        
        if (!f || f->num == 0)
                return NULL;
        
        struct nodo *removido = f->prim->item;
        struct nodofila *aux = f->prim;
        f->prim = aux->prox;
        free(aux);
        f->num--;

        if (f->prim == NULL)
                f->ult = NULL;
        
        return removido;
}

/* retorna o tamanho da fila */
int fila_tamanho(struct fila_t *f) {
        if (!f)
                return -1;
        
        return f->num;
}
