import re
import unidecode

def radixmsd (string, n):           #n sendo a posicao da letra a ser comparada
    if(len(string) <= 1):           #se o tamanho e menor ou igual que 1 a string ja esta ordenada
        return string
    
    ordenados = []           #string para guardar as palavras ordenadas
    letras = [[] for i in range(27)]        #matriz com cada letra do alfabeto

    for i in string:
        if (n >= len(i)):
            ordenados.append(i)
        else:
            letras[ord(i[n]) - ord('a')].append(i)

    letras = [radixmsd(l,n+1) for l in letras]
    return ordenados + [l for lista in letras for l in lista]

#Texto frankenstein:
arq = open("frankenstein.txt","r")              #abre o arquivo em modo de leitura
string = arq.read()                             #le o arquivo inteiro em uma string
string = string.lower()                         #deixa todas as letras em minusculo
string = re.sub('\d+','',string)                #tira todos os numeros da string
string = unidecode.unidecode(string)            #tira todos os acentos da string
string = string.replace('_','')                 #substitui os underlines por vazio (pois o comando a seguir nao o faz)
strAux = re.split('\W+',string)                 #retira todos os caracteres que nao sao do padrao Unicode (pontuacoes no gera)(regular expression), e transforma em uma lista de palavras
strAux = list(filter(None, strAux))             #filtra os elementos vazios da lista de strings
string = radixmsd(strAux,0)                     #executa o radix sort MSD
arq.close()                                     #fecha o arquivo
arq = open("frankenstein_ordenado.txt","w")     #abre o arquivo de saida em modo de escrita
for i in range(len(string)):                    #escreve cada palavra no arquivo (20 palavras por linha)
    if i%20 == 0:
        arq.write('\n')

    arq.write(string[i])
    arq.write(',')

arq.close()                                     #fecha o arquivo de saida

#Texto war_and_peace:
arq = open("war_and_peace.txt","r")              #abre o arquivo em modo de leitura
string = arq.read()                             #le o arquivo inteiro em uma string
string = string.lower()                         #deixa todas as letras em minusculo
string = re.sub('\d+','',string)                #tira todos os numeros da string
string = unidecode.unidecode(string)            #tira todos os acentos da string
string = string.replace('_','')                 #substitui os underlines por vazio (pois o comando a seguir nao o faz)
strAux = re.split('\W+',string)                 #retira todos os caracteres que nao sao do padrao Unicode (pontuacoes no gera)(regular expression), e transforma em uma lista de palavras
strAux = list(filter(None, strAux))             #filtra os elementos vazios da lista de strings
string = radixmsd(strAux,0)                     #executa o radix sort MSD
arq.close()                                     #fecha o arquivo
arq = open("war_and_peace_ordenado.txt","w")     #abre o arquivo de saida em modo de escrita
for i in range(len(string)):                    #escreve cada palavra no arquivo (20 palavras por linha)
    if i%20 == 0:
        arq.write('\n')

    arq.write(string[i])
    arq.write(',')

arq.close()                                     #fecha o arquivo de saida