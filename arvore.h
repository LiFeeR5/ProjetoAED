#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct _Comboio Comboio;

Comboio* initComboio(int* cabecalho);

Comboio* FirstBoard(int* cabecalho, int** matriz);


Comboio* copyComboio(Comboio* original, int* cabecalho);

//makeBoardMove  //Tira a mancha e cria a nova board
Comboio* currentBoard (Comboio* board, int* cabecalho, int** matriz, int totalScore);

//getNewBoardMove  
void novaMatriz(Comboio* boardAtual, int *cabecalho, int **matriz, int totalScore);

void deleteBoard(Comboio *board, int L);

int ProcuraMancha(int* cabecalho, int** matriz, int l, int c);

//Ver a matriz toda, começamos a ver em l=0 e c=0, se nao encontrarmos uma mancha passamos a frente, até chegar ao fim returnando 0, se encontrarmos returnamos 1
int VerificarMatriz(Comboio* board, int* cabecalho, int** matriz, int l, int c);

int CountNum(Comboio* boardAtual, int* cabecalho);

int ThereIsHope(Comboio* boardAtual, int* cabecalho, int totalScore);


Comboio* DFS(int* cabecalho, int** matriz);

void Variante2(Comboio* solucao, FILE* fp_out, Stack* stack,int* cabecalho, int** matriz);

#endif