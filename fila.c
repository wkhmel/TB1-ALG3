#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* cria uma fila sem nada */
struct fila_t *fila_cria() {
        struct fila_t *fila_vazia = malloc(sizeof(struct fila_t));
        if (!fila_vazia)
                return NULL;
        fila_vazia->prim = NULL;
        fila_vazia->ult = NULL;
        fila_vazia->num = 0;
        return fila_vazia;
};

/* retorna uma fila vazia, com todos os elementos e estruturas destruidos */
struct fila_t *fila_destroi(struct fila_t *f) {
        if (f == NULL){
                return NULL;
        }
        struct fila_nodo_t *aux_atual = f->prim;
        struct fila_nodo_t *aux_prox;
        while (aux_atual != NULL){
                aux_prox = aux_atual->prox;
                free(aux_atual);
                aux_atual = aux_prox;
                (f->num)--;
        }
        free(f);
        return NULL;
};

/* insere um elemento no fim da fila */
int fila_insere(struct fila_t *f, int item){
        struct fila_nodo_t *nodo = malloc(sizeof(struct fila_nodo_t));
        if (!(f) || !(nodo))
                return 0;
        nodo->item = item;
        nodo->prox = NULL;
        if (f->num == 0)
                f->prim = nodo;
        else
                f->ult->prox = nodo;
        f->ult = nodo;
        f->num++;
        return 1;
}

/* retira um elemento do comeco da fila, por ordem de chegada */
int fila_retira(struct fila_t *f, int *item){
        if (!(f) || !(item) || f->num == 0)
                return 0;
        *item = f->prim->item;
        struct fila_nodo_t *aux = f->prim;
        f->prim = aux->prox;
        free(aux);
        f->num--;

        if (f->prim == NULL)
                f->ult = NULL;
        return 1;
}

/* retorna o tamanho da fila */
int fila_tamanho(struct fila_t *f){
        if (f == NULL)
                return -1;
        return f->num;
}

/* imprime todos os elementos da fila */
void fila_imprime(struct fila_t *f){
        if (f == NULL || f->num == 0)
                return;
        struct fila_nodo_t *aux = f->prim;
        while (aux->prox != NULL){
                printf("%d ", aux->item);
                aux = aux->prox;
        }
        printf("%d", aux->item);
}
