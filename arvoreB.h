#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdint.h>

struct nodo {
    int32_t n; 
    /* vetor que guarda as n chaves desse nodo */
    int32_t *chaves;
    bool ehfolha; 
    /* vetor de ponteiros para os filhos */
    struct nodo **filhos;
};

struct arvoreB {
  struct nodo* raiz;
  int32_t t_arvore;
};

/* a partir de um t >= 2, cria uma árvore b sem nodos e a retorna. */
struct arvoreB* criarArvoreB(int32_t t_arvore);

/* reparte um filho de índice idxSplit do nó e passa a chave mediana, bem como seus filhos (se houver), para o pai. */
struct nodo *repartirFilho(struct nodo *no, int32_t idxSplit, int32_t t_arvore);

/* recebe um nodo garantidamente não cheio para inserir a chave passada, chamando a função repartirFilho quando necessário. */
void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t_arvore);

/* vai do começo da árvore repartindo todos os nodos cheios que for encontrando e usando a função inserirNaoCheio para colocar a chave passada na árvore. */
void inserirArvoreB(struct arvoreB* arvore, int32_t chave);

/* imprime uma árvore B em largura (Breadth-First Search), isto é, imprime todos os nodos de um nível da esquerda para a direita. */
void imprimirArvoreB(struct arvoreB* arvore);

/* essa função auxiliar imprime os nodos recursivamente em ordem não decrescente: esquerda -> atual -> direita. */
void imprimirNodoOrdem(struct nodo *no) {

/* imprime uma árvore B por meio da função acima. */
void imprimirEmOrdem(struct arvoreB* arvore);

/* essa função auxiliar recebe uma chave e procura em qual nodo ela está e em qual índice se situa no vetor de chaves. */
struct nodo *buscarNodoB(struct nodo *no, int32_t chave, int32_t *idxEncontrado);

/* usa a função acima para percorrer todos os nodos da árvore em busca da chave passada e coloca no conteúdo do ponteiro idxEncontrado o índice no vetor de chaves. */
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado);

/* libera cada um dos nodos da árvore (diferente da função excluir, pois esta deleta só um de cada vez e procura manter as propriedades da árvore B). */
/* passa em pós-ordem, ou seja: primeiro exclui os filhos dos lados para não perder seus ponteiros e em seguida exclui o próprio pai. */
void liberarNodo(struct nodo *no);

/* exclui a memória alocada em todas as estruturas internas da árvore (seus nodos) e libera a árvore. */
void deletarArvore(struct arvoreB* arvore);

#endif
