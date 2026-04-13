#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreB.h"
#include "fila.h"

struct nodo *criarNodoB(int32_t t_arvore, bool ehfolha) {
    struct nodo *novo = malloc(sizeof(struct nodo));

    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria.\n");
        exit(1);
    }

    novo->n = 0;
    novo->ehfolha = ehfolha;

    /* alocando o maior número possível de filhos de acordo com o t passado */
    novo->chaves = calloc((2 * t_arvore - 1), sizeof(int32_t));

    if (!novo->chaves) {
        fprintf(stderr, "Falha ao alocar memoria.\n");
        exit(1);
    }

    novo->filhos = calloc((2 * t_arvore), sizeof(struct nodo*));

    if (!novo->filhos) {
        fprintf(stderr, "Falha ao alocar memoria.\n");
        exit(1);
    }

    return novo;
    
}

struct arvoreB* criarArvoreB(int32_t t_arvore) {
    /* o t tem que ser maior ou igual a 2. */
    if (t_arvore < 2)
        return NULL;
    
    struct arvoreB *b = malloc(sizeof(struct arvoreB));
    
    if (!b) {
        fprintf(stderr, "Falha ao alocar memoria.\n");
        exit(1);
    }

    b->raiz = criarNodoB(t_arvore, true);
    b->t_arvore = t_arvore;

    return b;
}

struct nodo *repartirFilho(struct nodo *no, int32_t idxSplit, int32_t t_arvore) {
    struct nodo *aux = no->filhos[idxSplit]; /* nodo cheio a ser dividido */
    
    /* chave "nova" que quero inserir no nodo pai. */
    struct nodo *div = criarNodoB(t_arvore, aux->ehfolha);
    div->n = t_arvore - 1; 

    for (int32_t i = 0; i < div->n; i++)
    /* recebendo as chaves mais à direita de aux */
        div->chaves[i] = aux->chaves[i + t_arvore];

    /* se forem nós internos, vou pegar os filhos mais à direita de aux também */
    if (!div->ehfolha) {
        for (int32_t i = 0; i < t_arvore; i++) {
            div->filhos[i] = aux->filhos[i + t_arvore];
        }
    }

    /* agora a quantidade de chaves diminuiu em aux */
    aux->n = t_arvore - 1;

    for (int32_t i = no->n; i >= idxSplit + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    no->filhos[idxSplit + 1] = div;

    /* loop para deixar espaço para a chave mediana */
    for (int32_t i = no->n - 1; i >= idxSplit; i--)
        no->chaves[i + 1] = no->chaves[i];

    no->chaves[idxSplit] = aux->chaves[t_arvore - 1]; /* chave mediana está no lugar dela */
    no->n++; /* o pai (que certamente não estava cheio) agora tem mais uma chave! */
    
    return no;
}

void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t_arvore) {
    int32_t i = no->n - 1; /* vai de 0 a n-1 para dar n chaves */
    
    /* procurando o nodo mais à direita cuja chave seja menor ou igual à chave */
    if (no->ehfolha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        
        no->chaves[i + 1] = chave;
        no->n++;
    }
    else {
        while (i >= 0 && chave < no->chaves[i])
            i--;
        i++;
        
        if (no->filhos[i]->n == 2*(t_arvore) - 1) {
            no->filhos[i] = repartirFilho(no, i, t_arvore);
        /* depois da divisão, pode ser q a chave seja maior que a chave mediana do pai (q foi dividida) */
            if (chave > no->chaves[i])
                i++;
        }

        inserirNaoCheio(no->filhos[i], chave, t_arvore);
    }

}

void inserirArvoreB(struct arvoreB* arvore, int32_t chave) {
    if (!arvore || !arvore->raiz)
        return;

    /* verificando se a raiz está cheia */
    if (arvore->raiz->n == 2*(arvore->t_arvore) - 1) {
        struct nodo *novo = criarNodoB(arvore->t_arvore, false);

        novo->filhos[0] = arvore->raiz;
        arvore->raiz = novo;

        novo = repartirFilho(novo, 0, arvore->t_arvore);
        inserirNaoCheio(novo, chave, arvore->t_arvore);
    }
    else
        inserirNaoCheio(arvore->raiz, chave, arvore->t_arvore);
}

void imprimirNodoLargura(struct nodo *no) {
    if (!no)
        return;

    /* criando fila "bfs" (breadth-first search) */
    struct fila_t *bfs = criarFila();
    inserirFila(bfs, no);

    int32_t nivel = 0;
    while (bfs->num > 0) {
        /* guardo a quantidade de nodos que espero nesse mesmo nível */
        int32_t qtdNodos = bfs->num;
        
        printf("----//----\n");
        printf("Nivel %d\n", nivel);
        printf("----//----\n");

        /* loop para printar os nodos do mesmo nível primeiro */
        /* só sai do loop quando k ultrapassa a quantidade de nodos do nível */
        for (int k = 0; k < qtdNodos; k++) {
            struct nodo *aux = retirarFila(bfs);
            
            if (aux->ehfolha)
                printf("F ");
            else
                printf("I ");

            printf("(n:%d) ", aux->n);
            
            printf("[");
            int i = 0;
            while (i < aux->n - 1) {
                printf("%d ", aux->chaves[i]);
                i++;
            }
            /* o último nodo eu imprimo para fora para não ter espaço antes do colchete */
            printf("%d]", aux->chaves[i]);

        /* inserindo nodos filhos do atual, se houver */
            if (!aux->ehfolha) {
                for (int i = 0; i <= aux->n; i++) {
                    if (aux->filhos[i] != NULL)
                            inserirFila(bfs, aux->filhos[i]);
                }   
            }

        /* desde que não seja o último nodo, colocar espaçamento entre nodos */
            if (k < qtdNodos - 1)
                printf("   ");
        }
        /* linha entre níveis */
        printf("\n");
        nivel++;
    }
    destruirFila(bfs);
}

/* impressão em largura que passa por todos os nodos por meio de uma auxiliar */
void imprimirArvoreB(struct arvoreB* arvore) {
    if (!arvore)
        return;
    
    imprimirNodoLargura(arvore->raiz);
}

void imprimirNodoOrdem(struct nodo *no) {
    if (!no)   
        return;

    int i = 0;
    while (i < no->n) {
            if (!no->ehfolha)
                imprimirNodoOrdem(no->filhos[i]);
            printf(" %d", no->chaves[i]);
            i++;
    }
    
    if (!no->ehfolha)
        imprimirNodoOrdem(no->filhos[i]);
}


/* impressão em ordem */
void imprimirEmOrdem(struct arvoreB* arvore) {
    if (!arvore)
        return;

    printf("Em ordem:");

    imprimirNodoOrdem(arvore->raiz);
}

struct nodo *buscarNodoB(struct nodo *no, int32_t chave, int32_t *idxEncontrado) {
    int i = 0;
    
    while (i < no->n && chave > no->chaves[i])
        i++;
    
    if (i < no->n && chave == no->chaves[i]) {
        *idxEncontrado = i;
        return no; 
    }

    if (no->ehfolha)
        return NULL;

    return buscarNodoB(no->filhos[i], chave, idxEncontrado);
}

struct nodo *buscarArvoreB(struct arvoreB *arvore, int32_t chave, int32_t *idxEncontrado) {
    if (!arvore || !arvore->raiz || !idxEncontrado)
        return NULL;

    return buscarNodoB(arvore->raiz, chave, idxEncontrado);
}

void liberarNodo(struct nodo *no) {
    if (!no)
        return;

    if (!no->ehfolha) {
        for (int i = 0; i <= no->n; i++)
            liberarNodo(no->filhos[i]);
    }

    free(no->filhos);
    free(no->chaves);
    free(no);
}

void deletarArvore(struct arvoreB* arvore) {
    if (!arvore)
        return;

    liberarNodo(arvore->raiz);
    arvore->raiz = NULL;

    free(arvore);
}


