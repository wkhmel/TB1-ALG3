/* estilo de indentação usado: Kernel do Linux */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreB.h"
#include "fila.h"

struct nodo *criarNodoB(int32_t t_arvore, bool ehfolha) 
{
        struct nodo *novo = malloc(sizeof(struct nodo));

        if (!novo) {
                fprintf(stderr, "Falha ao alocar memoria.\n");
                exit(1);
        }

        novo->n = 0;
        novo->ehfolha = ehfolha;

        /* alocando o maior número possível de chaves de acordo com o t passado */
        novo->chaves = calloc((2 * t_arvore - 1), sizeof(int32_t));

        if (!novo->chaves) {
                fprintf(stderr, "Falha ao alocar memoria.\n");
                exit(1);
        }
    
    /* alocando o maior número possível de filhos de acordo com o t passado */
        novo->filhos = calloc((2 * t_arvore), sizeof(struct nodo*));

        if (!novo->filhos) {
                fprintf(stderr, "Falha ao alocar memoria.\n");
                exit(1);
        }

        return novo;
    
}

struct arvoreB *criarArvoreB(int32_t t_arvore) 
{
        /* o t tem que ser maior ou igual a 2. */
        if (t_arvore < 2 || t_arvore > 1073741823) {
                return NULL;
        }
    
        struct arvoreB *b = malloc(sizeof(struct arvoreB));
    
        if (!b) {
                fprintf(stderr, "Falha ao alocar memoria.\n");
                exit(1);
        }

        b->raiz = criarNodoB(t_arvore, true);
        b->t_arvore = t_arvore;

        return b;
}

struct nodo *repartirFilho(struct nodo *no, int32_t idxSplit, int32_t t_arvore) 
{
        struct nodo *aux = no->filhos[idxSplit]; /* nodo cheio a ser dividido */
    
        struct nodo *div = criarNodoB(t_arvore, aux->ehfolha);
        div->n = t_arvore - 1; 

        for (int32_t i = 0; i < div->n; i++) {
        /* recebendo as chaves mais à direita (maiores) do nodo cheio */
                div->chaves[i] = aux->chaves[i + t_arvore];
        }
    
        /* se o nodo cheio for interno, pegamos os filhos mais à direita dele também */
        if (!div->ehfolha) {
                for (int32_t i = 0; i < t_arvore; i++) {
                        div->filhos[i] = aux->filhos[i + t_arvore];
                }
        }

        /* agora a quantidade de chaves diminuiu em aux */
        aux->n = t_arvore - 1;

        /* loop para deixar espaço para o novo filho, que é div */
        for (int32_t i = no->n; i >= idxSplit + 1; i--) {
                no->filhos[i + 1] = no->filhos[i];
        }

        /* div, que contém as maiores chaves que estavam no nodo cheio, agora é outro filho de "no" */
        no->filhos[idxSplit + 1] = div;

        /* loop para deixar espaço para a chave mediana, caso já haja chaves lá */
        for (int32_t i = no->n - 1; i >= idxSplit; i--) {
                no->chaves[i + 1] = no->chaves[i];
        }

        no->chaves[idxSplit] = aux->chaves[t_arvore - 1]; /* chave mediana está no lugar dela */
        no->n++; /* pai (que certamente não estava cheio) agora tem mais uma chave */
    
        return no;
}

void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t_arvore) 
{
        int32_t i = no->n - 1; /* vai de 0 a n-1 -> n chaves */
    
        /* procurando o nodo mais à direita cuja chave seja menor ou igual à chave passada */
        if (no->ehfolha) {
                while (i >= 0 && chave < no->chaves[i]) {
                        no->chaves[i + 1] = no->chaves[i];
                        i--;
                }
        
                no->chaves[i + 1] = chave;
                no->n++;
        } else {
                /* procura o lugar onde chave é igual ou maior que a chave atual */
                while (i >= 0 && chave < no->chaves[i]) {
                        i--;
                }
                i++; /* incrementa para a posição aonde a chave deve ir */

                /* reparte este filho caso ele esteja cheio */
                if (no->filhos[i]->n == 2*(t_arvore) - 1) {
                        no = repartirFilho(no, i, t_arvore);
                        /* depois da divisão, pode ser que a chave seja maior que a chave mediana do pai */
                        if (chave > no->chaves[i]) {
                                i++;
                        }
                }

                inserirNaoCheio(no->filhos[i], chave, t_arvore);
        }

}

void inserirArvoreB(struct arvoreB *arvore, int32_t chave) 
{
        if (!arvore || !arvore->raiz) {
                return;
        }

        /* verificando se a raiz está cheia */
        if (arvore->raiz->n == 2*(arvore->t_arvore) - 1) {
                struct nodo *novo = criarNodoB(arvore->t_arvore, false);

                novo->filhos[0] = arvore->raiz;
                arvore->raiz = novo;
                novo = repartirFilho(novo, 0, arvore->t_arvore);
                inserirNaoCheio(novo, chave, arvore->t_arvore);

        } else {
                inserirNaoCheio(arvore->raiz, chave, arvore->t_arvore);
        }
}

void imprimirNodoLargura(struct nodo *no) 
{
        if (!no) {
                return;
        }

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
                for (int32_t k = 0; k < qtdNodos; k++) {
                        struct nodo *aux = retirarFila(bfs);
            
                        printf("%c (n:%d) [", aux->ehfolha ? 'F' : 'I', aux->n);
            
                        int32_t i = 0;
                        while (i < aux->n - 1) {
                                printf("%d ", aux->chaves[i]);
                                i++;
                        }

                        /* o último nodo é imprimido para fora para não ter espaço antes do colchete */
                        printf("%d]", aux->chaves[i]);

                        /* inserindo nodos filhos do atual, se houver */
                        if (!aux->ehfolha) {
                                for (int32_t i = 0; i <= aux->n; i++) {
                                        if (aux->filhos[i] != NULL) {
                                        inserirFila(bfs, aux->filhos[i]);
                                        }
                                }   
                        }

                        /* desde que não seja o último nodo, colocar espaçamento entre nodos */
                        if (k < qtdNodos - 1) {
                        printf("   ");
                        }
                }

                printf("\n"); /* linha entre níveis */
                nivel++;
        }

        destruirFila(bfs);
}

void imprimirArvoreB(struct arvoreB* arvore) 
{
        if (!arvore) {
                return;
        }
    
        imprimirNodoLargura(arvore->raiz);
}

void imprimirNodoOrdem(struct nodo *no) 
{
        if (!no) {
                return;
        }

        int32_t i = 0;
        while (i < no->n) {
                if (!no->ehfolha) {
                        /* chama recursivo para os filhos antes de imprimir a chave atual */
                        imprimirNodoOrdem(no->filhos[i]);
                }
                printf(" %d", no->chaves[i]);
                        i++;
        }

        /* como no loop imprimimos somente filho à esquerda da chave, precisamos imprimir o último à direita separadamente */
        if (!no->ehfolha) {
                imprimirNodoOrdem(no->filhos[i]);
        }
}


void imprimirEmOrdem(struct arvoreB* arvore) 
{
        if (!arvore) {
                return;
        }

        printf("Em ordem:");

        imprimirNodoOrdem(arvore->raiz);
}

struct nodo *buscarNodoB(struct nodo *no, int32_t chave, int32_t *idxEncontrado) 
{
        int32_t i = 0;

        /* loop que vai até onde a chave atual é igual ou maior que a chave desejada */
        while (i < no->n && chave > no->chaves[i]) {
                i++;
        }

        /* verifica se o índice em que o loop parou está dentro da quantidade de chaves e se achamos a chave desejada */
        /* em sucesso, retornamos o nodo onde a chave está e o índice da chave */
        if (i < no->n && chave == no->chaves[i]) {
                *idxEncontrado = i;
                return no; 
        }

        /* se a chave não foi encontrada e não há filhos onde procurar, retornamos NULL */
        if (no->ehfolha) {
                return NULL;
        }

        return buscarNodoB(no->filhos[i], chave, idxEncontrado);
}

struct nodo *buscarArvoreB(struct arvoreB *arvore, int32_t chave, int32_t *idxEncontrado) 
{
        if (!arvore || !arvore->raiz || !idxEncontrado) {
                return NULL;
        }

        return buscarNodoB(arvore->raiz, chave, idxEncontrado);
}

void mergeNodoArvoreB(struct nodo *esq, struct nodo *dir, int32_t chave, int32_t t)
{
        if (!esq || !dir)
			return;

        /* como mesclamos dois nodos de n igual a (t - 1) + a chave a ser removida, agora temos 2*(t-1) + 1  = 2t - 1 chaves */

        esq->n = 2*t - 1;
        esq->chaves[t - 1] = chave;

        for (int32_t i = 0; i < t - 1; i++) {
                esq->chaves[i+t] = dir->chaves[i];
        }

        if (!esq->ehfolha) {
                for (int32_t i = 0; i < t; i++) {
                        esq->filhos[t + i] = dir->filhos[i];
                }
        }
}

struct nodo *buscarPredecessor(struct nodo *no) 
{
        struct nodo *aux = no;

        /* enquanto não for folha, vai para o filho mais à direita (obs: o no passado é o filho à esquerda) */
        while (!aux->ehfolha) {
                aux = aux->filhos[aux->n];
        }
        return aux;
}

struct nodo *buscarSucessor(struct nodo *no) 
{ 
	struct nodo *aux = no;

	while (!aux->ehfolha) {
		aux = aux->filhos[0];
	}

	return aux;
}

bool removerChaveArvoreB(struct arvoreB *arvore, int32_t chave) 
{
        if (!arvore) {
                return false;
        }

        return removerChaveNodo(arvore, arvore->raiz, chave);
}

bool removerChaveNodo(struct arvoreB *arvore, struct nodo *no, int32_t chave) 
{
        if (!no) {
                return false;
        }

        int32_t id = 0;
        while (id < no->n && chave > no->chaves[id]) {
                id++;
        }

        if (id < no->n && chave == no->chaves[id]) {
                if (no->ehfolha) {
                        /* empurrando os elementos à frente do id pra esquerda, se houver */
                        for (int32_t a = id; a < no->n - 1; a++) {
                                no->chaves[a] = no->chaves[a + 1];
                        }
                        no->n--;

                        return true;   
                }

                /* a chave está em um nó interno. aqui verificamos se o filho à esquerda tem ao menos t chaves */
                if (no->filhos[id]->n >= arvore->t_arvore) {                
                 	struct nodo *predecessor = buscarPredecessor(no->filhos[id]);
                        /* o predecessor tem que ser a última chave do nodo mais à direita */
			no->chaves[id] = predecessor->chaves[predecessor->n - 1];       

                        /* já substituímos a chave pelo predecessor, então removemos o predecessor de baixo q restou */
			return removerChaveNodo(arvore, predecessor, predecessor->chaves[predecessor->n - 1]);       
                }

                /* o lado esquerdo n tem chaves suficientes. verificamos se o lado direito tem ou não. */
		if (no->filhos[id + 1]->n >= arvore->t_arvore) {
			struct nodo *sucessor = buscarSucessor(no->filhos[id + 1]);
			no->chaves[id] = sucessor->chaves[0];

			return removerChaveNodo(arvore, sucessor, sucessor->chaves[0]);
		}


                /* como ambos os filhos têm t - 1 chaves, fazemos um merge para uni-los com a própria chave a ser removida */
                mergeNodoArvoreB(no->filhos[id], no->filhos[id + 1], chave, arvore->t_arvore);
		
                /* empurramos as chaves à direita da que deve ser removida para trás */
                for (int32_t i = id; i < no->n - 1; i++) {
                        no->chaves[i] = no->chaves[i + 1];
                }

                /* para remover o nodo que já foi mesclado, substituímos pelos nodos da frente (se tiver) */
                for (int32_t i = id + 1; i < no->n; i++) {
                        no->filhos[i] = no->filhos[i + 1];
                }

		no->filhos[no->n] = NULL; 
		no->n--;
		
		/* guardamos o último nodo (vai ser removido) */
                struct nodo *aux = no->filhos[no->n];
		
                free(aux->filhos);
                free(aux->chaves);
                free(aux);

                /* se o nodo de onde a chave foi removida ficou vazio, quer dizer que ele é a nova raiz */
                if (no->n == 0) {
                        arvore->raiz = no->filhos[0];
                        free(no->chaves);
                        free(no);
                        return true;
                }

		/* agora a chave a ser removida está no filho, então chamamos a remoção para baixo */
		return removerChaveNodo(arvore, no->filhos[id], chave);
        }

        if (no->ehfolha) {
                return false;
        }

        /* verificamos se o próximo nodo tem só t-1 chaves antes de descer */
        if (no->filhos[id]->n == arvore->t_arvore - 1) {
                /* assumimos que o nodo com mais chaves é o irmão direito de no->filhos[id] */
                struct nodo *maior;
                int32_t idmaior = id;

                /* se estivermos no meio dos filhos, esse filho tem irmão esquerdo e direito */
                if (id > 0 && id < no->n) {
                        /* vê qual irmao tem mais chaves */
                        if (no->filhos[id - 1]->n > no->filhos[id + 1]->n) {
                                maior = no->filhos[id - 1];
                                idmaior--; /* índice do filho à esquerda de id */
                        }
                        else {
                                maior = no->filhos[id + 1];
                                idmaior++; /* índice do filho à direita de id */
                        }
                }
		
                /* se estivermos no primeiro filho, o único irmão imediato é o direito */
                if (id == 0) {
                        maior = no->filhos[id + 1];
                        idmaior++;
                }

                /* se estivermos no último filho, este só tem irmão esquerdo */
                if (id == no->n) {
                        maior = no->filhos[id - 1];
                        idmaior--;
                }
                
                /* verificando se o irmão com mais chaves tem pelo menos t chaves */
                if (maior->n >= arvore->t_arvore) {

			/* verificando se o idmaior é o irmão direito */
                        if (idmaior == id + 1) {
                                no->filhos[id]->chaves[no->filhos[id]->n] = no->chaves[id];
                                /* passamos sua primeira chave para o seu pai */
				no->chaves[id] = maior->chaves[0];

                                /* remove a chave do irmão direito q passamos (a primeira)*/
                                for (int32_t i = 0; i < maior->n - 1; i++) {
                                        maior->chaves[i] = maior->chaves[i + 1];
                                }

                                /* passando filhos para a esquerda (se houver) */
                                if (!maior->ehfolha) {
                                        no->filhos[id]->filhos[no->filhos[id]->n + 1] = maior->filhos[0];

                                        for (int32_t i = 0; i < maior->n; i++) {
                                                maior->filhos[i] = maior->filhos[i + 1];
                                        }

                                        maior->filhos[maior->n] = NULL;
                                }

                        } else {
                                /* abre espaço no começo */
                                for (int32_t i = no->filhos[id]->n - 1; i >= 0; i--) {
                                        no->filhos[id]->chaves[i + 1] = no->filhos[id]->chaves[i];
                                }

                                no->filhos[id]->chaves[0] = no->chaves[id-1];
                                no->chaves[id - 1] = maior->chaves[maior->n - 1];

                        }
                        no->filhos[id]->n++;
                        maior->n--;
                } else {
                        struct nodo *aux;
                        /* se tiver só t-1 chaves, por garantia, mesclamos as chaves dos filhos + chave do pai */
                        if (idmaior == id + 1) {
                                mergeNodoArvoreB(no->filhos[id], maior, no->chaves[id], arvore->t_arvore);

                                aux = maior;

                                for (int32_t i = id + 1; i < no->n; i++) {
                                        no->filhos[i] = no->filhos[i + 1];
                                }


                        } else {
                                mergeNodoArvoreB(maior, no->filhos[id], no->chaves[id-1], arvore->t_arvore);

                                aux = no->filhos[id];

                                for (int32_t i = id; i < no->n; i++) {
                                        no->filhos[i] = no->filhos[i + 1];
                                }
                                id--;
                        }

                        no->filhos[no->n] = NULL;
                        /* podemos liberar o maior */
                        free(aux->filhos);
                        free(aux->chaves);
                        free(aux);
                        
                        /* excluindo a chave do pai */
                        for (int32_t i = id; i < no->n - 1; i++) {
                                no->chaves[i] = no->chaves[i + 1];
			}
			
                        no->n--;
                        no->chaves[no->chaves->n - 1] = 0;
                        
                        if (no->n < 1) {
                                struct nodo* novaraiz = no->filhos[0];

                                free(no->chaves);
                                free(no->filhos);
                                free(no);
                                arvore->raiz = novaraiz;
                                return removerChaveNodo(arvore, novaraiz, chave);
                        }
                }
        }
        
        return removerChaveNodo(arvore, no->filhos[id], chave);
}

void liberarNodo(struct nodo *no) 
{
        if (!no) {
                return;
        }

        /* libera um por um dos filhos antes, se houver */
        if (!no->ehfolha) {
                for (int32_t i = 0; i <= no->n; i++) {
                        liberarNodo(no->filhos[i]);
                }
        }

        free(no->filhos);
        free(no->chaves);
        free(no);
}

void deletarArvore(struct arvoreB* arvore) 
{
        if (!arvore) {
                return;
        }

        liberarNodo(arvore->raiz);
        /* recebe NULL para o caso de a raiz ser procurada ou chamada externamente */
        arvore->raiz = NULL;

        free(arvore);
}





