#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "BibAutoComp.h"

int main()
{
    clock_t inicio = clock();
    FILE *arqWiki,*arqCons,*arqSaida;
    pNodoA *arvoreWiki;
    char palavra[TAMSTRING];
    arvoreWiki = cria_arvore();
    arqWiki = fopen("wiktionary.txt", "r");
    if (arqWiki == NULL) //testa se o arquivo foi aberto corretamente
        printf("Erro na abertura do arquivo!\n");
    arqCons = fopen("consultas.txt", "r");
    if (arqCons == NULL) //testa se o arquivo foi aberto corretamente
        printf("Erro na abertura do arquivo!\n");
    arqSaida = fopen("saida.txt", "w");
    if (arqSaida == NULL) //testa se o arquivo foi aberto corretamente
        printf("Erro na abertura do arquivo!\n");

    fgets(palavra,sizeof(palavra),arqWiki);         //primeira linha do txt = numero de palavras

    arvoreWiki = preencheAVL(arvoreWiki,arqWiki);
    consultaArq(arqCons,arqSaida,arvoreWiki);
    printf("Arquivo de saida gerado com sucesso!\n");
    fclose(arqWiki);
    fclose(arqCons);
    clock_t finall = clock();
    double tempo = (double)(finall-inicio)/CLOCKS_PER_SEC;
    fprintf(arqSaida,"\nTempo: %.3lfs",tempo);
    fclose(arqSaida);
    return 0;
}
