#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

//Controi e retorna o vetor matriz, colocando os valores do ficheiro de entrada
int **ConstuirMatriz(FILE* fp, int** matriz, int* cabecalho)
{
		//Colocar os numeros na matriz
		for (int j = cabecalho[0] - 1; j >= 0; j--)
		{
			for (int k = 0; k < cabecalho[1]; k++)
			{
				//Se a leitura falhar, da erro e sai do programa
                if(fscanf(fp, "%d", &matriz[j][k]) == -1)
                	exit(EXIT_FAILURE);
			}
		}

	return matriz;
}

//Verifica se a coordenada dada no cabecalho se encontra na matriz e retorna 1
//Caso contrário da print do cabecalho e retorna -1
int VerificacaoCoordenadas(int* cabecalho, int** matriz, FILE* fp_out)
{
	if ((1 > cabecalho[3] || cabecalho[3] > cabecalho[0]) || (1 > cabecalho[4] || cabecalho[4] > cabecalho[1]))
	{
		fprintf(fp_out, "%d %d %d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2], cabecalho[3], cabecalho[4]);
		return -1;
	}
	else return 1;
}

//Calcula a pontuaçao dos azuleijos retirados e retorna os pontos 
int Pontuacao(int azuleijoadjacente)
{
	int P = azuleijoadjacente * (azuleijoadjacente - 1);
	return P;
}