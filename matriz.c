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

//Calcula a pontuaçao dos azuleijos retirados e retorna os pontos 
int Pontuacao(int azuleijoadjacente)
{
	int P = azuleijoadjacente * (azuleijoadjacente - 1);
	return P;
}