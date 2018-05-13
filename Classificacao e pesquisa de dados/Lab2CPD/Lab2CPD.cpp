#include <cstdio>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

#define TAM 10
int trocas=0, trocasRandom=0, chamadas=0, chamadasRandom=0;     //variavel global para contar as trocas no sort, e para contar as chamadas recursivas
int esq,dir,maior;          //variaveis do heapsort
void writeFile(ofstream &saida, ofstream &stats, int vetor[], size_t tamVet,  int caso, int trocas, int chamadas, long double tempo){
    stats << caso+1 << " Caso:\n";                                  //escreve as informações relevantes no arquivo de saída
    stats << "Trocas = " << trocas << '\n';                      //
    stats << "Chamadas recursivas = " << chamadas << '\n';       //
    stats << "Tempo de execução = " << tempo << "ms\n\n";   //

    saida << tamVet << ' ';
    for (int k=0; k<tamVet-1; k++)      saida << vetor[k] << ' ';         //salva o elemento do array no arquivo de saída
    saida << vetor[tamVet-1] << '\n';
}

int particiona(int c[], int i, int f){    // k = posição ocupada ao final pela chave particionadora (cp)
    int cp;     // chave particionadora
    bool esq;   // esquerda
    cp = c[i];
    esq = true;
    while(i<f){
        if(esq){                //compara os valores à esquerda
            if(cp >= c[f]){     //se a chave é maior que o valor apontado pelo ponteiro f(im)
                c[i] = c[f];
                i++;
                trocas++;
                esq = false;    //termina a comparação à esquerda
            }
            else f--;
        }
        else{                   //compara os valores à direita
            if(cp < c[i]){      //se a chave é menor que o valor apontado pelo ponteiro i(nicio)
                c[f] = c[i];
                trocas++;
                f--;
                esq = true;
            }
            else i++;
        }
    }
    c[i] = cp;
    return i; //'i' é a posição final ocupada pela chave particionadora
}

void quicksort (int vetor[], int i, int f) {
    chamadas++;
    int p; // índice do pivô
    if (f > i) {
        p = particiona (vetor, i, f);
        quicksort (vetor, i, p-1);
        quicksort (vetor, p+1, f);
    }
}

int particaoRandomizada(int c[], int i, int f) {
    long int r;
    int varAux;
    srand(time(NULL));      // cria uma seed para que os numeros randomicos nao sejam sempre iguais a cada execução
    r = rand()%(f+1-i) +i;
    varAux = c[i];          //troca c[i] e c[r]
    c[i] = c[r];
    c[r] = varAux;
    trocasRandom++;
    return particiona(c, i, f);
}

void quicksortRandomizado(int c[], int i, int f){
    chamadasRandom++;
    int k;
    if(f > i){
        k = particaoRandomizada(c,i,f);
        quicksortRandomizado(c, i, k-1);
        quicksortRandomizado(c, k+1, f);
    }
}

void heapify(int vetor[], int pos, int tamVet){
    chamadas++;
    esq = 2*pos +1;
    dir = 2*pos +2;
    maior = pos;
    if(esq < tamVet && vetor[esq] > vetor[maior])
        maior = esq;

    if(dir < tamVet && vetor[dir] > vetor[maior])
        maior = dir;

    if(maior != pos){
        swap(vetor[pos],vetor[maior]);
        trocas++;
        heapify(vetor,maior,tamVet);
    }
}
void buildHeap(int vetor[], int tamVet){
    for (int j = tamVet/2 -1; j>=0; j--)
        heapify(vetor,j,tamVet);
}
void heapSort(int vetor[], int tamVet){
    buildHeap(vetor, tamVet);
    for (int j = tamVet-1; j>=0; j--){
        swap(vetor[0],vetor[j]);
        trocas++;
        heapify(vetor,0,j);
    }
}
int main(){
    clock_t start, end;
    long double timeNormal, timeRandom, timeHeap;
    string linha;
    ifstream arqEntrada ("entrada.txt");
    ofstream arqSaida, arqSaidaAleatorio, arqStats, arqStatsAleatorio, arqSaidaHeap, arqStatsHeap;
    arqSaida.open("saida-primeiro.txt");            //cria arquivo de saida
    arqSaidaAleatorio.open("saida-aleatorio.txt");
    arqStats.open("stats-primeiro.txt");
    arqStatsAleatorio.open("stats-aleatorio.txt");
    arqSaidaHeap.open("saida-heap.txt");
    arqStatsHeap.open("stats-heap.txt");
    size_t numElementos, numTestes;
    getline(arqEntrada,linha);      //pega o numero de arrays que arquivo tem
    numTestes = stoi(linha);
    arqSaida << numTestes << '\n';
    arqSaidaAleatorio << numTestes << '\n';
    arqSaidaHeap << numTestes << '\n';
    bool abriuArquivos = arqEntrada.is_open() && arqSaida.is_open() && arqSaidaAleatorio.is_open() && arqStats.is_open() && arqStatsAleatorio.is_open() && arqSaidaHeap.is_open() && arqStatsHeap.is_open();

    if(abriuArquivos){
        for(int i=0; i<numTestes; i++){
            getline(arqEntrada,linha, ' ');           //le a primeira linha do arquivo que diz o numero de casos de testes
            numElementos = stoi(linha);               //salva o numero de elementos do array
            int vetor[numElementos];         //cria um array com o numero de elementos obtido anteriormente
            if(arqSaida.is_open()){
                for (int j=0; j<numElementos-1; j++){     //faz um loop para ir pegando numero por numero(com o separador ' ') para salvar no array
                    getline(arqEntrada, linha, ' ');
                    vetor[j] = stoi(linha);
                    }
                getline(arqEntrada, linha);               //pega o ultimo elemento separadamente, pois, depois dele, há um \n indicando o final da linha
                vetor[numElementos-1] = stoi(linha);

                int copiaVetor[numElementos];
                for (int k=0; k<numElementos; k++)  copiaVetor[k] = vetor[k];   //copia o vetor original para outro, para executar outro sort
                trocas=0;       //zera o numero de trocas
                chamadas=0;     //zera o numero de chamadas
                start = clock();
                quicksort(copiaVetor,0,numElementos-1);                          //executa os quicksorts
                end = clock();
                timeNormal = 1000.0 * (end-start) / CLOCKS_PER_SEC;

                writeFile(arqSaida,arqStats,copiaVetor,numElementos,i,trocas,chamadas-1,timeNormal);//salva as informacoes no arquivo de saida

                for (int k=0; k<numElementos; k++)  copiaVetor[k] = vetor[k];   //copia o vetor original para outro, para executar outro sort
                trocas=0;       //zera o numero de trocas
                trocasRandom=0; //
                chamadasRandom=0;     //zera o numero de chamadas
                start = clock();
                quicksortRandomizado(copiaVetor, 0, numElementos-1);
                end = clock();
                timeRandom = 1000.0 * (end-start) / CLOCKS_PER_SEC;
                trocasRandom += trocas;
                writeFile(arqSaidaAleatorio,arqStatsAleatorio,copiaVetor,numElementos,i,trocasRandom,chamadasRandom-1,timeRandom);//salva as informacoes no arquivo de saida

                for (int k=0; k<numElementos; k++)  copiaVetor[k] = vetor[k];   //copia o vetor original para outro, para executar outro sort
                trocas=0;
                chamadas=0;
                start = clock();
                heapSort(copiaVetor,numElementos);
                end = clock();
                timeHeap = 1000.0 * (end-start) / CLOCKS_PER_SEC;
                writeFile(arqSaidaHeap,arqStatsHeap,copiaVetor,numElementos,i,trocas,chamadas-1,timeHeap);//salva as informacoes no arquivo de saida
            }
        }
        arqEntrada.close();
        arqSaida.close();
        arqSaidaAleatorio.close();
    }

    else cout << "Erro ao abrir o arquivo\n";
    return 0;
}
