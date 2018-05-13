#ifndef MENU
#define MENU
#include <stdio.h>
#include <conio.h>
#include <conio2.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#define XMARJOG 25
#define XMARADV 3
#define TAMANHO 15
#define TAMSUB 1
#define TAMCRUZ 2
#define TAMDEST 4
#define TAMPORTAV 5
#define X 100
#define Y 6

void menuOpcoes();
void resetTabuleiro(char mar[TAMANHO][TAMANHO], char mar2[TAMANHO][TAMANHO], char mar3[TAMANHO][TAMANHO]);
void tabuleiro(int linha[TAMANHO], char coluna[TAMANHO], char mar[TAMANHO][TAMANHO], int altura);
void posNavios(char mar[TAMANHO][TAMANHO],char mar2[TAMANHO][TAMANHO], int linhaTab[TAMANHO], char colunaTab[TAMANHO]);
void posNaviosAdv(char mar[TAMANHO][TAMANHO]);
void menu();
void imprimeCentro();
void colocaBarco(char mar[TAMANHO][TAMANHO], int linha, char coluna, char direcao, int tamBarco, int *tipoBarco);
void quantBarcos(int sub, int cruz, int dest, int port);
char leOpcao();

void menu() {       // Funcao para chamar o menu principal
    char op;
    char filename[100];
    int coordNum[TAMANHO] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    char coordChar[TAMANHO] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    char marJog[TAMANHO][TAMANHO], marAdv[TAMANHO][TAMANHO], marInvisivel[TAMANHO][TAMANHO];

    system("mode 100,50");
    menuOpcoes();
    op = getch();

    switch(op) {
        case 'i':
        case 'I': printf("Iniciando um novo jogo!!\n");
            delay(1000);
            resetTabuleiro(marJog, marAdv, marInvisivel);
            posNaviosAdv(marAdv);
            delay(1000);
            clrscr();
            tabuleiro(coordNum, coordChar, marAdv,XMARADV);
            printf("\n\n");
            tabuleiro(coordNum, coordChar, marJog,XMARJOG);
            posNavios(marJog,marAdv,coordNum,coordChar);
            break;
        case 'c':
        case 'C': printf("Digite o nome do arquivo com o jogo a carregar: ");
            scanf("%s",filename);
            printf("Carregando o jogo salvo no arquivo %s!\n",filename);
            break;
        case 'r':
        case 'R': printf("Regras do Jogo Batalha Naval..\n");
            break;
        case 'p':
        case 'P': printf("Buscando os recordes registrados...\n");
            break;
        case 's':
        case 'S': printf("Ateh mais!!\n");
            break;
        default: printf("Opcao invalida!!\n");
    }
}

void imprimeCentro(char str[30],int linha){ // Calcula o tamanho da string e imprime-a na centralizada na tela de acordo com seu tamanho
    gotoxy((X-strlen(str))/2,linha);
    puts(str);
}

void menuOpcoes(){          // Imprime o menu de opcoes
    textcolor (10);
    imprimeCentro("*****************",Y);
    imprimeCentro("* B A T A L H A *",Y+1);
    imprimeCentro("*   N A V A L   *",Y+2);
    imprimeCentro("*****************",Y+3);
    imprimeCentro("[I] Iniciar um novo jogo",Y+8);
    imprimeCentro("[C] Carregar um jogo",Y+10);
    imprimeCentro("[R] Regras do jogo",Y+12);
    imprimeCentro("[P] Melhores pontuacoes (recordes)",Y+14);
    imprimeCentro("[S] Sair",Y+16);
    textcolor (15);
}

void resetTabuleiro(char mar[TAMANHO][TAMANHO], char mar2[TAMANHO][TAMANHO], char mar3[TAMANHO][TAMANHO]){    // Coloca '~' (mar) em todo o tabuleiro
    int i,j;
    for(i=0; i<TAMANHO; i++){
        for(j=0; j<TAMANHO; j++){
            mar[i][j] = '~';
            mar2[i][j] = '~';
            mar3[i][i] = '~';
        }
    }
}

void tabuleiro(int linhaTab[TAMANHO], char colunaTab[TAMANHO], char mar[TAMANHO][TAMANHO], int altura){       // Funcao para exibir o tabuleiro
    int i,j;
    gotoxy(35,altura);
    for(i=0; i<TAMANHO; i++)
        printf("%2c",colunaTab[i]);
    gotoxy(33,altura+2);
    for(i=0; i<TAMANHO+1; i++)
        printf("%2c",'#');
    gotoxy(35,altura+18);
    for(i=0; i<TAMANHO+1; i++)
        printf("%2c",'#');
    for(i=0; i<TAMANHO+1; i++){
        gotoxy(33,altura+3+i);
        printf("%2c",'#');
        gotoxy(65,altura+2+i);
        printf("%2c",'#');
    }
    for(i=0; i<TAMANHO; i++){
        gotoxy(31,altura+3+i);
        printf("%2d",linhaTab[i]);
    }
    for(i=0; i<TAMANHO; i++){
        gotoxy(35,altura+3+i);
        for(j=0; j<TAMANHO; j++){
            if(mar[i][j] != '~'){
                textcolor(YELLOW);
                printf("%2c",mar[i][j]);
                textcolor(WHITE);
            }
            else{
                textcolor(LIGHTBLUE);
                printf("%2c",mar[i][j]);
                textcolor(WHITE);
            }
        }
    }

    /*int i,j;                              //i = linha, j = coluna
    for(i=0; i<TAMANHO+1; i++){
        if(i==0 || i==15){                // i=0 e i=17 topo e base do tabuleiro, respectivamente
            for(j=0; j<TAMANHO+1; j++){
                if(j == 0)
                    printf("%2c",'*');
                if(j == 15)
                    printf("  *\n");
                else
                    printf(" %2c",colunaTab[j]);
            }
        }
        if(i>=0 && i<15){
            for(j=0; j<TAMANHO+1; j++){
                if(j == 0)
                    printf("%2d",linhaTab[i]);
                if(j == 15)
                    printf(" %2d\n",linhaTab[i]);
                else{
                    if(mar[i][j] != '~'){
                        textcolor(YELLOW);
                        printf(" %2c",mar[i][j]);
                        textcolor(WHITE);
                    }
                    else{
                        textcolor(LIGHTBLUE);
                        printf(" %2c",mar[i][j]);
                        textcolor(WHITE);
                    }
tabuleiro(linhaTab,colunaTab,mar2,4);
                }
            }
        }
    }
    */
}

void posNavios(char mar[TAMANHO][TAMANHO], char mar2[TAMANHO][TAMANHO],int linhaTab[TAMANHO], char colunaTab[TAMANHO]){       // Funcao escolher os barcos para posicionar
    int linha, opcaoNavio, submarino = 5, cruzador = 4, destroyer = 2, portAviao = 1;
    bool printMenu = true;
    char col,direcao;
    do{
        if(printMenu){
        gotoxy(1,42);
        printf("Escolha o navio: \n");
        printf("1 - Submarino\n");
        printf("2 - Cruzador\n");
        printf("3 - Destroyer\n");
        printf("4 - Porta avioes\n");
        }
        printMenu = true;
        do{
            opcaoNavio = getch();
        }while(opcaoNavio<'1' || opcaoNavio>'4');

        switch(opcaoNavio){
            case '1':
                    if(submarino == 0){
                        printf("Nao ha mais submarinos\n");
                        printMenu = false;
                        break;
                    }
                    printf("\nDigite as coordenadas (Coluna, Linha, Direcao [H - Horizontal, V - Vertical]\n");
                    do{
                        scanf(" %c%d,%c",&col, &linha, &direcao);
                        col = toupper(col);
                        direcao = toupper(direcao);
                    }while(linha<1 || linha>15 || col<'A' || col>'O' || (direcao!='H' && direcao!='V'));
                    clrscr();
                    colocaBarco(mar, linha, col, direcao, TAMSUB, &submarino);
                    tabuleiro(linhaTab,colunaTab,mar2,XMARADV);
                    tabuleiro(linhaTab,colunaTab,mar,XMARJOG);
                    quantBarcos(submarino,cruzador,destroyer,portAviao);
                    break;
            case '2':
                    if(cruzador == 0){
                        printf("Nao ha mais cruzadores\n");
                        break;
                    }
                    printf("\nDigite as coordenadas (Coluna, Linha, Direcao [H - Horizontal, V - Vertical]\n");
                    do{
                        scanf(" %c%d,%c",&col, &linha, &direcao);
                        col = toupper(col);
                        direcao = toupper(direcao);
                    }while(linha<1 || linha>15 || col<'A' || col>'O' || (direcao!='H' && direcao!='V'));
                    clrscr();
                    colocaBarco(mar, linha, col, direcao, TAMCRUZ, &cruzador);
                    tabuleiro(linhaTab,colunaTab,mar2,XMARADV);
                    tabuleiro(linhaTab,colunaTab,mar,XMARJOG);
                    quantBarcos(submarino,cruzador,destroyer,portAviao);
                    break;
            case '3':
                    if(destroyer == 0){
                        printf("Nao ha mais destroyers\n");
                        break;
                    }
                    printf("\nDigite as coordenadas (Coluna, Linha, Direcao [H - Horizontal, V - Vertical]\n");
                    do{
                        scanf(" %c%d,%c",&col, &linha, &direcao);
                        col = toupper(col);
                        direcao = toupper(direcao);
                    }while(linha<1 || linha>15 || col<'A' || col>'O' || (direcao!='H' && direcao!='V'));
                    clrscr();
                    colocaBarco(mar, linha, col, direcao, TAMDEST, &destroyer);
                    tabuleiro(linhaTab,colunaTab,mar2,XMARADV);
                    tabuleiro(linhaTab,colunaTab,mar,XMARJOG);
                    quantBarcos(submarino,cruzador,destroyer,portAviao);
                    break;
            case '4':
                    if(portAviao == 0){
                        printf("Nao ha mais Porta-Avioes\n");
                        break;
                    }
                    printf("\nDigite as coordenadas (Coluna, Linha, Direcao [H - Horizontal, V - Vertical]\n");
                    do{
                        scanf(" %c%d,%c",&col, &linha, &direcao);
                        col = toupper(col);
                        direcao = toupper(direcao);
                    }while(linha<1 || linha>15 || col<'A' || col>'O' || (direcao!='H' && direcao!='V'));
                    clrscr();
                    colocaBarco(mar, linha, col, direcao, TAMPORTAV, &portAviao);
                    tabuleiro(linhaTab,colunaTab,mar2,XMARADV);
                    tabuleiro(linhaTab,colunaTab,mar,XMARJOG);
                    quantBarcos(submarino,cruzador,destroyer,portAviao);
                    break;
            default: break;
        }
    }while(submarino+cruzador+destroyer+portAviao !=0);
    gotoxy(1,42);
    printf("Todos os barcos posicionados!!\n");
}

void posNaviosAdv(char mar[TAMANHO][TAMANHO]){
    int linha, opcaoNavio, submarino = 5, cruzador = 4, destroyer = 2, portAviao = 1;
    char col,direcao;
    do{
        srand(time(NULL));
        opcaoNavio = (rand()%4)+1;
        switch(opcaoNavio){
                case 1:
                        if(submarino == 0)
                            break;
                        linha = (rand()%15)+1;
                        col = (rand()%15)+65;
                        if((rand()%2) == 1)
                            direcao = 'V';
                        else
                            direcao = 'H';
                        clrscr();
                        colocaBarco(mar, linha, col, direcao, TAMSUB, &submarino);
                        break;

                case 2:
                        if(cruzador == 0)
                            break;
                        linha = (rand()%15)+1;
                        col = (rand()%15)+65;
                        if((rand()%2) == 1)
                            direcao = 'V';
                        else
                            direcao = 'H';
                        clrscr();
                        colocaBarco(mar, linha, col, direcao, TAMCRUZ, &cruzador);
                        break;

                case 3:
                        if(destroyer == 0)
                            break;
                        linha = (rand()%15)+1;
                        col = (rand()%15)+65;
                        if((rand()%2) == 1)
                            direcao = 'V';
                        else
                            direcao = 'H';
                        clrscr();
                        colocaBarco(mar, linha, col, direcao, TAMDEST, &destroyer);
                        break;

                case 4:
                        if(portAviao == 0)
                            break;
                        linha = (rand()%15)+1;
                        col = (rand()%15)+65;
                        if((rand()%2) == 1)
                            direcao = 'V';
                        else
                            direcao = 'H';
                        clrscr();
                        colocaBarco(mar, linha, col, direcao, TAMPORTAV, &portAviao);
                        break;
                default:
                        break;
        }
    }while(submarino+cruzador+destroyer+portAviao !=0);
    printf("TODOS OS BARCOS POSICIONADOS");
}

void quantBarcos(int sub, int cruz, int dest, int port){
    textcolor(LIGHTCYAN);
    gotoxy(70,XMARJOG);
    printf("Submarinos: %d",sub);
    gotoxy(70,XMARJOG+1);
    printf("Cruzadores: %d",cruz);
    gotoxy(70,XMARJOG+2);
    printf("Destroyers: %d",dest);
    gotoxy(70,XMARJOG+3);
    printf("Porta-avioes: %d",port);
    textcolor(WHITE);
}

void colocaBarco(char mar[TAMANHO][TAMANHO], int linha, char coluna, char direcao, int tamBarco, int *tipoBarco){       // Funcao para posicionar os barcos, com testes de consistencia

    int i, checaBarco=0,col;
    col = coluna-'A';
    linha--;
    switch(tamBarco){
        case TAMSUB:
            if(mar[linha][col] == '~'){
                mar[linha][col] = 'S';
                (*tipoBarco)--;
            }
            else printf("Nao e possivel posicionar o barco nesta posicao!\n");

            break;
        case TAMCRUZ:
            if(direcao == 'H'){
                for(i=col; i<(col+TAMCRUZ) && i<TAMANHO; i++){
                    if(mar[linha][i] == '~')
                        checaBarco++;

                    else{
                        printf("Nao e possivel posicionar o barco nesta posicao!\n");
                        break;
                    }
                }
                if(checaBarco == TAMCRUZ){
                    for(i=col; i<(col+TAMCRUZ) && i<TAMANHO; i++)
                        mar[linha][i] = 'C';
                    (*tipoBarco)--;
                    checaBarco=0;
                }
                break;
            }
            else if(direcao == 'V'){
                for(i=linha; i<linha+TAMCRUZ && i<TAMANHO; i++){
                    if(mar[i][col] == '~')
                        checaBarco++;

                    else{
                        printf("Nao e possivel posicionar o barco nesta posicao!\n");
                        break;
                    }
                }
                if(checaBarco == TAMCRUZ){
                    for(i=linha; i<linha+TAMCRUZ && i<TAMANHO; i++){
                        mar[i][col] = 'C';
                    }
                    (*tipoBarco)--;
                    checaBarco=0;
                }
                break;
            }
        case TAMDEST:
            if(direcao == 'H'){
                for(i=col; i<col+TAMDEST && i<TAMANHO; i++){
                    if(mar[linha][i] == '~')
                        checaBarco++;
                    else{
                        printf("Nao e possivel posicionar o barco nesta posicao!\n");
                        break;
                    }
                }
                if(checaBarco == TAMDEST){
                    for(i=col; i<col+TAMDEST && i<TAMANHO; i++)
                        mar[linha][i] = 'D';
                    (*tipoBarco)--;
                    checaBarco=0;
                }
                break;
            }
            if(direcao == 'V'){
                for(i=linha; i<linha+TAMDEST && i<TAMANHO; i++){
                    if(mar[i][col] == '~')
                        checaBarco++;
                    else{
                        printf("Nao e possivel posicionar o barco nesta posicao!\n");
                        break;
                    }
                }
                if(checaBarco == TAMDEST){
                    for(i=linha; i<linha+TAMDEST && i<TAMANHO; i++)
                        mar[i][col] = 'D';
                    (*tipoBarco)--;
                    checaBarco=0;
                }
                break;
            }
        case TAMPORTAV:
            if(direcao == 'H'){
                for(i=col; i<col+TAMPORTAV && i<TAMANHO; i++){
                    if(mar[linha][i] == '~')
                        checaBarco++;
                    else{
                        printf("Nao e possivel posicionar o barco nesta posicao!\n");
                        break;
                    }
                }
                if(checaBarco == TAMPORTAV){
                    for(i=col; i<col+TAMPORTAV && i<TAMANHO; i++)
                        mar[linha][i] = 'P';
                    (*tipoBarco)--;
                    checaBarco=0;
                }
                break;
            }
            if(direcao == 'V'){
                for(i=linha; i<linha+TAMPORTAV && i<TAMANHO; i++){
                    if(mar[i][col] == '~')
                        checaBarco++;
                    else{
                        printf("Nao e possivel posicionar o barco nesta posicao!\n");
                        break;
                    }
                }
                if(checaBarco == TAMPORTAV){
                    for(i=linha; i<linha+TAMPORTAV && i<TAMANHO; i++)
                        mar[i][col] = 'P';
                    (*tipoBarco)--;
                    checaBarco=0;
                }
                break;
            }
        default: break;
    }
}

#endif
