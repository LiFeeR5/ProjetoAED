#ifndef funcoes_H_INCLUDED
#define funcoes_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Recebe o nome do ficheiro de entrada e devolve o nome do ficheiro de saida
char* FileOutName(char* argv[]);

//Le a primeira linha de cada exercicio guardando os 5 valores no vetor cabecalho
int LerCabecalho(FILE* fp, int* cabecalho);

//Controi e retorna o vetor matriz, colocando os valores do ficheiro de entrada
int **ConstuirMatriz(FILE* fp, int** matriz, int* cabecalho);

//Verifica se a variante é 1 ou 2, retornando 1
//Caso contrário da print ao cabecalho e retorna -1
int CheckVariante(int* cabecalho, FILE* fp_out);

//Retira os azuleijos da coordenada dada no cabecalho e adjacentes à coordanada, contando-os e construindo a mancha 
//Retornando o numero total de azuleijos adjacentes
int Mancha(int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente);

//Calcula a pontuaçao dos azuleijos retirados e retorna os pontos
int Pontuacao(int azuleijoadjacente);

//Le a matriz, trocando a posição dos "-1" com os outros numeros acima deles
//Caso haja alguma coluna apenas com "-1" todas as colunas à sua esquerda dao slide para a direita 
void Gravidade(int* cabecalho, int** matriz, int azuleijoadjacente);
#endif