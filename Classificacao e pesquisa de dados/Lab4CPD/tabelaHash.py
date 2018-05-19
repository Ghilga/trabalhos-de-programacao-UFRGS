# -*- coding: utf-8 -*-
"""
Created on Sat May 19 20:32:10 2018

@author: Ghilga
"""
#a funcao para transformar strings em hash foi feita da seguinte maneira:
#obtem-se o numero do caractere (de acordo com a tabela ASCII)
#concatena-se os numeros em formato de string (um do lado do outro) e inverte para inteiro
#e por fim obtem-se o resto da divisao do numero inteiro por 2^32 (32 bits)
def strToHash (string):
    hashstr = ""            #Inicializa a variavel para armazenar o hash
    for i in string:        #transforma cada letra da string em inteiro e adiciona na string do hash(uma do lado da outra)
        hashstr = hashstr + str(ord(i))
    
    hashstr = int(hashstr)  #transforma a string em inteiro
    hashstr = hashstr % (2**32)     #2**32 para transformar em um inteiro de 32 bits
    return hashstr

#funcao para inserir os hashes na tabela
#algoritmo de colisao utilizado e o de duplo hash
def insTabela (tabela,hashlist,col):
    for i in hashlist:
        j = 0
        condicao = True
        while(condicao):
            pos = ((i%53) + j*(7-(i%7)))%53     #funcao double hash
            if(tabela[pos] is not 0):           #se o valor da posicao nao for 0 nao insere
                col += 1                        #incrementa o numero de colisoes
                j += 1
                    
            else:                   #se for 0 insere
                tabela[pos] = i
                condicao = False    #condicao de parada
                
    return col


arq = open("names.txt","r")
dicionario = {}             #inicializa a variavel de dicionario para converter as hashes
for i in arq:
    i = i.strip('\n')       #remove os \n da string
    hashString = strToHash(i)   #cria o hash
    dicionario[i] = hashString  #salva a string e sua hash em um dicionario para conversao
    
listaHashes = []            #inicializa uma lista para os hashes
listaHashes = list(dicionario.values())   #salva todas as hashes nessa lista
tabHash = [0 for i in range(53)]   #inicializa uma tabela para os hashes (53 pois e um numero primo)
colisoes = 0
colisoes = insTabela (tabHash,listaHashes,colisoes)
print("Numero de colisoes: ",colisoes)
print("Taxa de ocupacao da tabela: 50 itens preenchidos,",len(tabHash)-50,"vazios")