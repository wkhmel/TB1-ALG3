#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "arvoreB.h"

/* cria uma fila sem nada */
struct fila_t *fila_cria() {
        if (!(struct fila_t *vazia = malloc(sizeof(struct fila_t)))) {
                fprintf(stderr, "Falha ao alocar memoria.\n");
                exit(1);
        }

        vazia->prim = vazia->ult = NULL;
        vazia->num = 0;
        
        return vazia;
};

/* retorna uma fila vazia, com todos os elementos e estruturas destruidos */
struct fila_t *fila_destroi(struct fila_t *f) {
        if (f == NULL) {
                return NULL;
        }
        
        struct nodofila *atual = f->prim;
        struct nodofila *aux_prox;
        
        while (atual != NULL) {
                aux_prox = atual->prox;
                free(atual);
                atual = aux_prox;
        }
        
        free(f);
        return NULL;
};


/* insere um elemento no fim da fila */
int fila_insere(struct fila_t *f, struct nodo *item) {
        if (!f)
                return 0;
        
        if (!(struct nodofila *novo = malloc(sizeof(struct nodofila)))) {
                fprintf(stderr, "Falha ao alocar memoria.\n");
                exit(1);
        }
        
        novo->item = item;
        novo->prox = NULL;
        
        if (f->num == 0)
                f->prim = novo;
        else
                f->ult->prox = novo;
        
        f->ult = novo;
        f->num++;
        
        return 1;
}

/* retira um elemento do começo da fila, por ordem de chegada, e o retorna */
struct nodo *fila_retira(struct fila_t *f) {
        
        if (!f || !item || f->num == 0)
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

/* imprime todos os elementos da fila */
void fila_imprime(struct fila_t *f) {
        if (f == NULL || f->num == 0)
                return;

        struct nodofila *aux = f->prim;
        while (aux != NULL) {
                for (int i = 0; i < aux->item->; i++) {
                        printf("%d ", aux->item->chaves[i];
                }
                aux = aux->prox;
        }
        printf("\n");
}
