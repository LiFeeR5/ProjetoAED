#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

//Le a primeira linha de cada exercicio guardando os 5 valores no vetor cabecalho
//[C]olunas, [L]inhas, [v]ariavel, [l]inha, [c]oluna
int LerCabecalho(FILE* fp, int* cabecalho)
{
	return fscanf(fp, "%d %d %d", &cabecalho[0], &cabecalho[1], &cabecalho[2]);
}

//Verifica se a variante é 1 ou 2, retornando 1
//Caso contrário da print ao cabecalho e retorna -1
int CheckVariante(int* cabecalho, FILE* fp_out)
{
	if (cabecalho[2] < 0 && cabecalho[2] != -1 && cabecalho[2] != -3)
	{
		fprintf(fp_out, "%d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2]);
		return -1;
	}
	else return 1;
}