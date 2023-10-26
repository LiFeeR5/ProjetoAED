#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

struct _Comboio
{
    int **matriz;
    int score;
    int **manchacoord;
    int totalmanchas;
    int cnt;
};

typedef struct _Comboio Comboio;

Comboio* initComboio(int* cabecalho);

Comboio* copyComboio(Comboio* original, int* cabecalho);

//getNewBoardMove  
void novaMatriz(Comboio* boardAtual, Comboio* newBoard, int *cabecalho, int* totalScore);

void FindAllManchas(Comboio* board, int* cabecalho, int** matrizTemporaria);

//makeBoardMove  //Tira a mancha e cria a nova board
Comboio* currentBoard (Comboio* board, int* cabecalho, int* totalScore, int** matrizTemporaria);

Comboio* FirstBoard(int* cabecalho, int** matriz, int** matrizTemporaria);

void deleteBoard(Comboio *board, int* cabecalho);

int compararDecrescente(const void *a, const void *b);

int ThereIsHope(Comboio* boardAtual, int* cabecalho, int* totalScore, int* array_qsort);

void NextMancha(Comboio* boardAtual);

Comboio* DFS2(Stack *stack, int* cabecalho, int** matriz, int* totalScore, int** matrizTemporaria, int* qsort_array);

void DFS3(Stack *stack, int* cabecalho, int** matriz, int** matrizTemporaria, int** saveBestRamo, int* qsort_array, int* PontosAtuais);
#endif