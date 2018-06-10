#ifndef ARVOREBIN_H_INCLUDED
#define ARVOREBIN_H_INCLUDED
#include <stdio.h>
#include <math.h>
#include <string.h>
typedef char TipoInfo;
struct TNodoA{
    TipoInfo info[100];
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
};  typedef struct TNodoA pNodoA;

pNodoA* cria_arvore(void);
// cria uma árvore vazia
pNodoA* InsereArvore(pNodoA *a, TipoInfo ch);
// insere nodo na ABP (caminhamento central a esquerda)
pNodoA* achaPai(pNodoA *a, TipoInfo *info);
// acha o pai do nodo informado
pNodoA* destroi(pNodoA *a);
// destroi a arvore
void preFixado(pNodoA *a);
// imprime os nodos de uma arvore no modo prefixado a esquerda
void preFixadoString(pNodoA *a);
void preFixado_igual(pNodoA *a, int cont);
// faz o mesmo que "preFixado" mas coloca '=' para definir o nivel do nodo
void central(pNodoA *a);
// imprime os nodos de uma arvore no modo central a esquerda
void posFixado(pNodoA *a);
void posFixadoString(pNodoA *a);
// imprime os nodos de uma arvore no modo posfixado a esquerda
int contaNodos(pNodoA* a,int quantNodos);
// conta o numero total de nodos de uma arvore
pNodoA* rotacao_direita(pNodoA* pt);
// rotação direita para nodo com fator fora do intervalo [-1,1] (- -)
pNodoA* rotacao_esquerda(pNodoA *pt);
// rotação esquerda para nodo com fator fora do intervalo [-1,1] (+ +)
pNodoA* rotacao_dupla_direita (pNodoA* pt);
// dupla rotação direita para nodo com fator fora do intervalo [-1,1] (+ -)
pNodoA* rotacao_dupla_esquerda (pNodoA *pt);
// dupla rotação esquerda para nodo com fator fora do intervalo [-1,1] (- +)
pNodoA* InsereAVL (pNodoA *a, TipoInfo x, int *ok);
pNodoA* InsereAVLstring (pNodoA *a, TipoInfo *x, int *ok);
// insere nodos em uma arvore do tipo AVL
pNodoA* Caso1 (pNodoA *a , int *ok);
pNodoA* Caso2 (pNodoA *a , int *ok);
int Altura (pNodoA *a);
// calcula a altura a partir de um nodo ate a folha
int fatorNodo (pNodoA *a, TipoInfo nodo);
// calcula o fator do nodo
int maiorFator (pNodoA *a,int maior);
//calcula o maior fator da arvore
pNodoA *intersecta(pNodoA *a,pNodoA *b,pNodoA *c);

#endif // ARVOREBIN_H_INCLUDED
