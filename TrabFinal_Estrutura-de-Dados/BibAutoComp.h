#ifndef BIBAUTOCOMP_H_INCLUDED
#define BIBAUTOCOMP_H_INCLUDED
#include <stdio.h>
#define TAMSTRING 100
#define MENOR 155
#define MAIOR 156
#define IGUAL 157
#define TRUE 158

typedef char TipoInfo;
struct TNodoA{
    TipoInfo info[TAMSTRING];
    char primLetra;
    int FB;
    double peso;
    struct TNodoA *esq;
    struct TNodoA *dir;
};  typedef struct TNodoA pNodoA;

char primeiroChar(char *palavra);
// pega o primeiro caractere da palavra(apos o peso) da string
double pesoString(char* stringArq);
// pega o peso salvo na string e converte para double
int comparaString (char *a,pNodoA *arvWiki, int *flag);
// compara uma string caractere por caractere para ver qual a palavra sugerida
void percorreArvore(char *palavraCons,pNodoA *arvWiki,int *flag,FILE *arqSaida);
void consultaArq (FILE *arqCons,FILE *arqSaida,pNodoA *arvWiki);
pNodoA *preencheAVL (pNodoA *a,FILE *arq);
// preenche a arvore AVL com os dados do arquivo especificado
pNodoA* cria_arvore(void);
// cria uma árvore vazia
pNodoA* destroi(pNodoA *a);
// destroi a arvore
void preFixado(pNodoA *a);
// imprime os nodos de uma arvore no modo prefixado a esquerda
void preFixado_igual(pNodoA *a, int cont);
// faz o mesmo que "preFixado" mas coloca '=' para definir o nivel do nodo
void central(pNodoA *a);
// imprime os nodos de uma arvore no modo central a esquerda
void centralDir(pNodoA *a);
void posFixado(pNodoA *a);
// imprime os nodos de uma arvore no modo posfixado a esquerda
pNodoA* rotacao_direita(pNodoA* pt);
// rotação direita para nodo com fator fora do intervalo [-1,1] (- -)
pNodoA* rotacao_esquerda(pNodoA *pt);
// rotação esquerda para nodo com fator fora do intervalo [-1,1] (+ +)
pNodoA* rotacao_dupla_direita (pNodoA* pt);
// dupla rotação direita para nodo com fator fora do intervalo [-1,1] (+ -)
pNodoA* rotacao_dupla_esquerda (pNodoA *pt);
// dupla rotação esquerda para nodo com fator fora do intervalo [-1,1] (- +)
pNodoA* InsereAVLstring (pNodoA *a, TipoInfo *x, int *ok);
// insere nodos em uma arvore do tipo AVL
pNodoA* Caso1 (pNodoA *a , int *ok);
pNodoA* Caso2 (pNodoA *a , int *ok);

#endif // BIBAUTOCOMP_H_INCLUDED
