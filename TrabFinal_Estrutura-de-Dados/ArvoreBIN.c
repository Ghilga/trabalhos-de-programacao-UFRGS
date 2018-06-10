#include "ArvoreBIN.h"
#include "BibAutoComp.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
pNodoA* cria_arvore(void){
    return NULL;
}

pNodoA* achaPai(pNodoA *a, TipoInfo *info){
    pNodoA *found = NULL;
    if (a != NULL){
        if (a->info == info)
            return a;
        else{
            found = achaPai(a->esq,info);
            if (!found)
            return achaPai(a->dir,info);
            else return found;
        }
    }
    else
        return NULL;
}

pNodoA* destroi(pNodoA *a){
    if (a!= NULL){
        destroi(a->esq);
        destroi(a->dir);
        printf("destruindo %c\n",a->info);
        free(a);
        return NULL;
    }
}

void preFixado(pNodoA *a){
    if (a!= NULL){
    printf("%d\n",a->info);
    preFixado(a->esq);
    preFixado(a->dir);
    }
}
void preFixadoString(pNodoA *a){
    if (a!= NULL){
    puts(a->info);
    preFixadoString(a->esq);
    preFixadoString(a->dir);
    }
}
void central(pNodoA *a){
    if (a!= NULL){
    central(a->esq);
    printf("%s\n",a->info);
    central(a->dir);
    }
}

void posFixado(pNodoA *a){
    if (a!= NULL){
    posFixado(a->esq);
    posFixado(a->dir);
    printf("%d\n",a->info);
    }
}
void posFixadoString(pNodoA *a){
    if (a!= NULL){
    posFixadoString(a->dir);
    posFixadoString(a->esq);
    puts(a->info);
    }
}


int contaNodos(pNodoA* a, int quantNodos){
    if(a != NULL){
        quantNodos++;
        quantNodos = contaNodos(a->esq,quantNodos);
        quantNodos = contaNodos(a->dir,quantNodos);
    }
    return quantNodos;
}

void preFixado_igual(pNodoA *a, int cont){
    if (a!= NULL){
    int i=0;
    for(i;i<cont;i++)
        printf("%c",'=');
    printf("%d\n",a->info);
    cont++;
    preFixado_igual(a->esq,cont);
    preFixado_igual(a->dir,cont);
    }
}

pNodoA* rotacao_direita(pNodoA* pt){
    pNodoA *ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
return pt;
}

pNodoA* rotacao_esquerda(pNodoA *pt){
    pNodoA *ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
return pt;
}

pNodoA* rotacao_dupla_direita (pNodoA* pt){
    pNodoA *ptu, *ptv;
    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)
        pt->FB = -1;
    else
        pt->FB = 0;
    if (ptv->FB == -1)
        ptu->FB = 1;
    else
        ptu->FB = 0;
    pt = ptv;
return pt;
}

pNodoA* rotacao_dupla_esquerda (pNodoA *pt){
    pNodoA *ptu, *ptv;
    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1)
        pt->FB = 1;
    else
        pt->FB = 0;
    if (ptv->FB == 1)
        ptu->FB = -1;
    else
        ptu->FB = 0;
    pt = ptv;
return pt;
}

pNodoA* InsereAVLstring (pNodoA *a, TipoInfo *x, int *ok){
/* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL) {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->info,x);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }

    else if (comparaString(x,a->info) == MENOR) {
        a->esq = InsereAVLstring(a->esq,x,ok);
        if (*ok) {
            switch (a->FB) {
                case -1: a->FB = 0; *ok = 0;
                    break;
                case 0: a->FB = 1;
                    break;
                case 1: a=Caso1(a,ok);
                    break;
                }
            }
        }
        else {
            a->dir = InsereAVLstring(a->dir,x,ok);
            if (*ok) {
                switch (a->FB) {
                    case 1: a->FB = 0; *ok = 0;
                        break;
                    case 0: a->FB = -1;
                        break;
                    case -1: a = Caso2(a,ok);
                        break;
                }
            }
        }
    return a;
}


pNodoA* Caso1 (pNodoA *a , int *ok){
    pNodoA *ptu;
    ptu = a->esq;
    if (ptu->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* Caso2 (pNodoA *a , int *ok){
    pNodoA *ptu;
    ptu = a->dir;
    if (ptu->FB == -1)
        a=rotacao_esquerda(a);
    else
        a=rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA* consultaABP2(pNodoA *a, TipoInfo chave) {
    if (a==NULL)
        return NULL;
    else
        if (a->info == chave)
            return a;
        else
            if (a->info > chave)
                return consultaABP2(a->esq,chave);
            else
                return consultaABP2(a->dir,chave);
}

int Altura (pNodoA *a){
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else{
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

int fatorNodo (pNodoA *a, TipoInfo nodo){
    int fator, ladoEsq, ladoDir;
    a = consultaABP2(a, nodo);
    ladoEsq = Altura(a->esq);
    ladoDir = Altura(a->dir);
    fator = abs(ladoEsq-ladoDir);
    return fator;
}

int maiorFator (pNodoA *a,int maior){
    int fator;
    if (a==NULL)
        return maior;
    else{
        fator = abs(fatorNodo(a,a->info));
        if (fator > maior)
            maior = fator;
        return maiorFator(a->esq,maior);
        return maiorFator(a->dir,maior);
    }
}
