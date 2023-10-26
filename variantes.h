#ifndef VARIANTES_H
#define VARIANTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Comboio Comboio;

int RemoverManchas(int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente, int numjogadas, int** play, int *pontos);

void Variante1(FILE* fp_out, int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente, int *pontos);

void FreeV2(int** matrizTemporaria, int* qsort_array, int* cabecalho);

void Variante2(Comboio* solucao, FILE* fp_out, int* cabecalho, int** matriz);

void FreeV3(int** matrizTemporaria, int** saveBestRamo, int* qsort_array, int* cabecalho);

void Variante3(FILE* fp_out, int* cabecalho, int** matriz);
#endif