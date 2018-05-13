#include "BibAutoComp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char primeiroChar(char *palavra){
    char aux1[TAMSTRING],aux2[TAMSTRING];
    sscanf(palavra,"%s %s",&aux2,&aux1);
    return tolower(aux1[0]);
}
double pesoString(char* stringArq){
    char aux[TAMSTRING];
    sscanf(stringArq," %s",&aux);
    return atof(aux);
}

int comparaString(char *palavraCons,pNodoA *arvWiki,int *flag){
    int i=0,j = strlen(palavraCons);
    char aux[TAMSTRING],aux2[TAMSTRING];
    sscanf(arvWiki->info,"%s %s ",&aux,&aux2);
    while(tolower(palavraCons[i]) == tolower(aux2[i])){
        i++;
        j--;
        if(j == 1){
            *flag = TRUE;
            return IGUAL;
        }
    }
    return NULL;
}

void percorreArvore(char *palavraCons,pNodoA *arvWiki,int *flag, FILE *arqSaida){
    if(arvWiki!=NULL){
        if(tolower(palavraCons[0]) == arvWiki->primLetra){
            percorreArvore(palavraCons,arvWiki->dir,flag,arqSaida);

            if (comparaString(palavraCons,arvWiki,flag) == IGUAL){
                fprintf(arqSaida,"%s",arvWiki->info);
            }

            percorreArvore(palavraCons,arvWiki->esq,flag,arqSaida);
        }
        if(tolower(palavraCons[0]) < arvWiki->primLetra)
            percorreArvore(palavraCons,arvWiki->esq,flag,arqSaida);
        else if(tolower(palavraCons[0]) > arvWiki->primLetra)
            percorreArvore(palavraCons,arvWiki->dir,flag,arqSaida);
    }
}

void consultaArq (FILE *arqCons,FILE *arqSaida,pNodoA *arvWiki){
    char consulta[TAMSTRING];
    int flag;
    while(!feof(arqCons)){
        flag = 0;
        fgets(consulta,sizeof(consulta),arqCons);
        fprintf(arqSaida,"%s",consulta);
        percorreArvore(consulta,arvWiki,&flag,arqSaida);
        if (flag == 0)
            fprintf(arqSaida,"\tnenhum resultado encontrado\n");
        }
}
pNodoA *preencheAVL (pNodoA *a,FILE *arq){
    char palavra[TAMSTRING];
    int ok;
    while(!feof(arq)){
        fgets(palavra,sizeof(palavra),arq);
        a = InsereAVLstring(a,palavra,&ok);
        }
    return a;
    }
pNodoA* cria_arvore(void){
    return NULL;
}
pNodoA* destroi(pNodoA *a){
    if (a!= NULL){
        destroi(a->esq);
        destroi(a->dir);
        printf("destruindo %s\n",a->info);
        free(a);
        return NULL;
    }
}
void preFixado(pNodoA *a){
    if (a!= NULL){
    puts(a->info);
    preFixado(a->esq);
    preFixado(a->dir);
    }
}
void preFixado_igual(pNodoA *a, int cont){
    if (a!= NULL){
        int i=0;
        for(i;i<cont;i++)
            printf("%c",'=');
        puts(a->info);
        cont++;
        preFixado_igual(a->esq,cont);
        preFixado_igual(a->dir,cont);
    }
}
void central(pNodoA *a){
    if (a!= NULL){
    central(a->esq);
    puts(a->info);
    central(a->dir);
    }
}
void centralDir(pNodoA *a){
    if (a!= NULL){
    central(a->dir);
    puts(a->info);
    central(a->esq);
    }
}
void posFixado(pNodoA *a){
    if (a!= NULL){
    posFixado(a->dir);
    posFixado(a->esq);
    puts(a->info);
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
    char primeiraLetraX;
    primeiraLetraX = primeiroChar(x);

    if (a == NULL) {
        TipoInfo aux[TAMSTRING];
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->peso = pesoString(x);
        strcpy(a->info,x);
        strcpy(aux,a->info);
        a->primLetra = primeiroChar(aux);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (primeiraLetraX < a->primLetra) {
        a->esq = InsereAVLstring(a->esq,x,ok);
        if (*ok) {
            switch (a->FB) {
                case -1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = 1; break;
                case 1: a=Caso1(a,ok); break;
                }
            }
        }
    else if (primeiraLetraX > a->primLetra) {
        a->dir = InsereAVLstring(a->dir,x,ok);
        if (*ok) {
            switch (a->FB) {
                case 1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = -1; break;
                case -1: a = Caso2(a,ok); break;
                }
            }
        }
    else if (primeiraLetraX == a->primLetra){
        if(pesoString(x) < a->peso){
            a->esq = InsereAVLstring(a->esq,x,ok);
            if (*ok) {
            switch (a->FB) {
                case -1: a->FB = 0; *ok = 0; break;
                case 0: a->FB = 1; break;
                case 1: a=Caso1(a,ok); break;
                }
            }
        }
        else{
            a->dir = InsereAVLstring(a->dir,x,ok);
            if (*ok) {
                switch (a->FB) {
                    case 1: a->FB = 0; *ok = 0; break;
                    case 0: a->FB = -1; break;
                    case -1: a = Caso2(a,ok); break;
                    }
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
