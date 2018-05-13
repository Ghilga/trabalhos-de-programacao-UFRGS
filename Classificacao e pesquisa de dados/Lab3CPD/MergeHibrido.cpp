#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

//O numero de elementos escolhidos para serem ordenados com insertion sort no merge hibrido foi 40


using namespace std;
int passada=0;
void print_array(vector<int> &C, int tam) {
    printf("[");
    for (int i=0; i<tam-1; i++) {
        printf("%d, ", C[i]);
    }
    printf("%d]\n", C[tam-1]);
}

int binary_search (vector<int> &a, int low, int high, int key) {
        int mid;
        if (low == high)
                return low;
        mid = low + ((high-low)/2);
        if (key > a[mid])
                return binary_search(a, mid+1, high, key);
        else if (key < a [mid])
                return binary_search(a, low, mid, key);
        return mid;
}

void binary_insertion_sort(vector<int> &C, int ini, int fim) {
        int i, j, chave;
        int ins;
        for (j=ini+1; j<=fim; j++) {
                ins = binary_search(C, ini, j, C[j]);
                chave = C[j];
                for (int k=j-1; k>=ins; k--) {
                        C[k+1] = C[k];
                }
                C[ins]=chave;
        }
}

void insertion_sort(int C[], int tam) {
        int i, j, chave;
        for (j=1; j<tam; j++) {
                chave = C[j];
                i = j-1;
                while ((i>=0) && C[i]>chave) {
                        C[i+1] = C[i];
                        i--;
                }
                C[i+1]=chave;
        }
}

// Merge Sort
void merg(vector<int> &vet, vector<int> &vetAux, int i, int f, int m, size_t tamVet){ //i: inicio, f: final, m: meio
    int mid = m+1, ini = i;
    for (int k = ini; k <= f; k++){
        vetAux[k] = vet[k];
    }
    for (int k = ini; k <= f; k++){
        if (ini > m)
            vet[k] = vetAux[mid++];
        else if (mid > f)
            vet[k] = vetAux[ini++];
        else if (vetAux[mid] < vetAux[ini])
            vet[k] = vetAux[mid++];
        else
            vet[k] = vetAux[ini++];
    }
}
void mergeSort(vector<int> &vet,vector<int> &vetAux, int i, int f, size_t tamVet){  //i: inicio, f: final
    if(i < f){
        int m = (i+f)/2;
        mergeSort(vet,vetAux,i,m,tamVet);
        mergeSort(vet,vetAux,m+1,f,tamVet);
        merg(vet,vetAux,i,f,m,tamVet);
    }
}
void hybridMergeSort(vector<int> &vet,vector<int> &vetAux, int i, int f, size_t tamVet){  //i: inicio, f: final
    if(i < f){
        int m = (i+f)/2;
        if(m > 20 && m < tamVet-21){
            hybridMergeSort(vet,vetAux,i,m,tamVet);
            hybridMergeSort(vet,vetAux,m+1,f,tamVet);
            merg(vet,vetAux,i,f,m,tamVet);
        }
        else{
            binary_insertion_sort(vet,i,f);
        }
    }
}

int is_sorted(vector<int> &C, int tam) {
  for (int i=1; i<tam; i++) {
    if ( C[i-1] > C[i])
      return 0;
  }
  return 1;
}


int main(){
    ofstream FileOut; FileOut.open("out.csv");
    clock_t start, end;                //variaveis para o benchmark
    double time[3][20];
    for (int k=1; k<=20; k++){
        size_t tam = k*50;                  //variavel para o tamanho dos arrays
        vector<int> vetHybrid(tam), vetAux(tam), vetMerge(tam), vetInsert(tam);
        for (int i=0; i<tam; i++){              //cria um array aleatorio para ser usado igualmente em todos os sorts
            vetHybrid[i] = rand()%tam+1;
            vetMerge[i] = vetHybrid[i];
            vetInsert[i] = vetHybrid[i];
        }
        cout << "Tamanho do Array: " << tam << '\n';
        start = clock();               //benchmark de tempo de execucao
        binary_insertion_sort(vetInsert,0,tam-1);               //executa o binary insertion
        end = clock();
        time[0][k-1] = (end - start)/(double)CLOCKS_PER_SEC;             //salva os tempos em uma matriz


        start = clock();                //benchmark de tempo de execucao
        mergeSort(vetMerge,vetAux,0,tam-1,tam);                 //executa o merge normal
        end = clock();
        time[1][k-1] = (end - start)/(double)CLOCKS_PER_SEC;            //salva os tempos em uma matriz

        start = clock();                //benchmark de tempo de execucao
        hybridMergeSort(vetHybrid,vetAux,0,tam-1,tam);          //executa o merge hibrido (com binary insertion)
        end = clock();
        time[2][k-1] = (end - start)/(double)CLOCKS_PER_SEC;            //salva os tempos em uma matriz

        if(is_sorted(vetInsert,tam))              //verifica se os arrays estao ordenados
            cout << "Ordenado\n";
        else
            cout << "Nao ordenado\n";

        }
    FileOut << "Algoritmo,N,time\n";                        //insere os dados para plotar o grafico no arquivo de saida (out.csv)
    for (int j=0; j<3; j++){

        for (int l=0; l<20; l++){
            switch(j){
                case 0: FileOut << "Insertion,";
                    break;
                case 1: FileOut << "Merge,";
                    break;
                case 2: FileOut << "MergeHibrido,";
            }
            FileOut << 50*(l+1) << ',';
            FileOut << time[j][l] << '\n';
        }
    }

    return 0;
}

