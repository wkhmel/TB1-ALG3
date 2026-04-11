#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdint.h>

struct nodo {
    int32_t n; 
    int32_t *chaves;
    bool ehfolha; 
    /* vetor de ponteiros para os filhos */
    struct nodo **filhos;
};

struct arvoreB {
  struct nodo* raiz;
  int32_t t_arvore;
};

struct arvoreB* criarArvoreB(int32_t t_arvore);

void inserirArvoreB(struct arvoreB* arvore, int32_t chave);

void imprimirArvoreB(struct arvoreB* arvore);

void imprimirEmOrdem(struct arvoreB* arvore);

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado);

void deletarArvore(struct arvoreB* arvore);

#endif
