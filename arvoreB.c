#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreB.h"

void verificaPonteiros(void *p) {
    if (!p) {
        fprintf(stderr, "Falha ao alocar memoria.\n");
        exit(1);
    }
}

struct arvoreB* criarArvoreB(int32_t t_arvore) {
    struct arvoreB *b = malloc(sizeof(struct arvoreB));
    verificaPonteiros(b);

    b->raiz = NULL;
    b->t_arvore = t_arvore;

    return b;
}

struct nodo *repartirFilho(struct nodo *no, int32_t idxSplit, int32_t t_arvore) {
    struct nodo *div = calloc(sizeof(struct nodo)); /* chave "nova" que quero colocar em no*/
    /* usei calloc para não ter que inicializar cada um dos filhos como NULL */
    verificaPonteiros(div);
  
    struct nodo *aux = no->filhos[idxSplit]; /* nodo cheio que quero dividir */
    div->ehfolha = aux->ehfolha; 
    div->n = t_arvore - 1; 

    for (int i = 0; i < div->n; i++)
    /* recebendo as chaves mais à direita de aux */
        div->chaves[i] = aux->chaves[i + t_arvore];

    /* se forem nós internos, vou pegar os filhos mais à direita de aux também */
    if (!div->ehfolha) {
        for (int i = 0; i < t_arvore; i++) {
            div->filhos[i] = aux->filhos[i + t_arvore];
        }
    }

    /* agora a quantidade de chaves diminuiu em aux */
    aux->n = t_arvore - 1;

    for (int i = no->n; i >= idxSplit + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    no->filhos[idxSplit + 1] = div;

    /* loop para deixar espaço para a chave mediana */
    for (int i = no->n - 1; i >= idxSplit; i--)
        no->chaves[i + 1] = no->chaves[i];

    no->chaves[idxSplit] = aux->chaves[t_arvore - 1]; /* chave mediana está no lugar dela */
    no->n++; /* o pai (que certamente não estava cheio) agora tem mais uma chave! */
    
    return no;
}

void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t_arvore) {
    int i = no->n - 1;
    
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
        /* depois da divisão, pode ser q a chave seja maior que a chave mediana do pai (que foi dividida) */
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
        struct nodo *novo = malloc(sizeof(struct nodo));
        
        verificaPonteiros(novo);
        
        arvore->raiz = novo;
        novo->ehfolha = false;
        novo->n = 0;
        novo->filhos[0] = aux;

        novo = repartirFilho(novo, 0, arvore->t_arvore);
        inserirNaoCheio(novo, chave, arvore->t_arvore);
    }
    else
        inserirNaoCheio(arvore->raiz, chave, arvore->t_arvore);
}

/* impressão em largura */
void imprimirArvoreB(struct arvoreB* arvore) {
    if (!arvore)
        return;
    
        
}

void imprimirNodoOrdem(struct nodo *no) {
    if (!no)   
        return;

    for (int j = 0; j < no->n; j++) {
            if (!no->ehfolha)
                imprimirNodoOrdem(no->filhos[j]);
            printf(" %d", no->chaves[j]);
        }
    if (!no->ehfolha)
        imprimirNodoOrdem(no->filhos[j])
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
    
    while (i < no->n && chave < no->chaves[i])
        i++;
    
    if (i < no->n && chave = no->chaves[i]) {
        *idxEncontrado = i;
        return no; 
    }

    if (no->ehfolha)
        return NULL;

    return buscarNodoB(no->filhos[i], chave, idxEncontrado);
}

struct nodo *buscarArvoreB(struct arvoreB *arvore, int32_t chave, int32t *idxEncontrado) {
    if (!arvore || !arvore->raiz)
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

    free(no);
}

void deletarArvore(struct arvoreB* arvore) {
    if (!arvore)
        return;

    liberarNodo(arvore->raiz);
    arvore->raiz = NULL;

    free(arvore);
}
  
}

