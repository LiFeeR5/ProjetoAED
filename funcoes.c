#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

////////////////////////////////////////////////////////////////////////////////CHATTTTT TTEMOS DE DESCOMENDAR
//Recebe o nome do ficheiro de entrada e devolve o nome do ficheiro de saida
char* FileOutName(char* inputFileName) {
	//const char* token = ".";
	const char* positionOfToken = strrchr(inputFileName, '.');

	if (positionOfToken == NULL) {
		// O ponto não foi encontrado no nome do arquivo de entrada.
		return NULL; // Ou realize outra ação apropriada.
	}

	// Tamanho da parte do nome do arquivo antes do ponto.
	size_t prefixLength = positionOfToken - inputFileName;

	// Tamanho total da nova string (incluindo ".tileblasts" e o caractere nulo).
	size_t newLength = prefixLength + strlen(".tileblasts") + 1;

	char* fileOutName = (char*)malloc(newLength);

	if (fileOutName == NULL) {
		fprintf(stderr, "Falha na alocação de memória.\n");
		exit(1); // Ou tome outra ação apropriada em caso de falha na alocação.
	}

	// Copia a parte do nome do arquivo antes do ponto.
	strncpy(fileOutName, inputFileName, prefixLength);

	// Acrescenta a extensão desejada na nova string.
	strcpy(fileOutName + prefixLength, ".tileblasts");

	return fileOutName;
}

//Retira os azuleijos da coordenada dada no cabecalho e adjacentes à coordanada, contando-os e construindo a mancha 
//Retornando o numero total de azuleijos adjacentes
int Mancha(int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente)
{
	int valornumero = matriz[l][c]; //Guardar o valor das coordenadas
	matriz[l][c] = -1; //Colocar o valor das coordenadas recebidas a -1
	azuleijoadjacente++;

	//Verificar se está dentro da matriz 
	if (l + 1 <= (cabecalho[0] - 1))
	{
		//verifica se em cima da coordenada o valor é diferente de -1 e se é igual ao valor da coordenada recebida
		if (matriz[l + 1][c] != -1 && valornumero == matriz[l + 1][c])
		{
			azuleijoadjacente = Mancha(cabecalho, matriz, l + 1, c, azuleijoadjacente);
		}
	}

	//Verificar se está dentro da matriz 
	if (c + 1 <= (cabecalho[1] - 1))
	{
		//verifica se à direita da coordenada o valor é diferente de -1 e se é igual ao valor da coordenada recebida
		if (matriz[l][c + 1] != -1 && valornumero == matriz[l][c + 1])
		{
			azuleijoadjacente = Mancha(cabecalho, matriz, l, c + 1, azuleijoadjacente);
		}
	}

	//Verificar se está dentro da matriz 
	if (l - 1 >= 0)
	{
		//verifica se em baixo da coordenada o valor é diferente de -1 e se é igual ao valor da coordenada recebida
		if (matriz[l - 1][c] != -1 && valornumero == matriz[l - 1][c])
		{
			azuleijoadjacente = Mancha(cabecalho, matriz, l - 1, c, azuleijoadjacente);
		}
	}

	//Verificar se está dentro da matriz
	if (c - 1 >= 0)
	{
		//verifica se à esquerda da coordenada o valor é diferente de -1 e se é igual ao valor da coordenada recebida
		if (matriz[l][c - 1] != -1 && valornumero == matriz[l][c - 1])
		{
			azuleijoadjacente = Mancha(cabecalho, matriz, l, c - 1, azuleijoadjacente);
		}
	}
	return azuleijoadjacente;
}

//Le a matriz, trocando a posição dos "-1" com os outros numeros acima deles
//Caso haja alguma coluna apenas com "-1" todas as colunas à sua esquerda dao slide para a direita 
void Gravidade(int* cabecalho, int** matriz, int azuleijoadjacente)
{
	//Se o numero de azulejos na mancha for só um não entra dentro do ciclo
	if (azuleijoadjacente != 1)
	{
		//Alocacao dinamica de memoria do vetor tamanhoqueda
		int* tamanhoqueda = (int*)malloc(cabecalho[1] * sizeof(int));

		//Inicializaçao do vetor tamanhoqueda
		for (int i = 0; i < (cabecalho[1]); i++)
		{
			tamanhoqueda[i] = 0;
		}

		//Percorre as linhas de baixo para cima, ao longo das colunas 
		for (int col = 0; col < (cabecalho[1]); col++)
		{
			for (int li = 0; li < (cabecalho[0]); li++)
			{
				if (matriz[li][col] == -1) tamanhoqueda[col]++;

				//Se o numero for difetente de -1 ele vai descer tantas posições quantos numeros "-1" existirem na coluna
				else if (matriz[li][col] != -1 && tamanhoqueda[col] != 0)
				{
					int aux = matriz[li][col];
					matriz[li][col] = matriz[li - tamanhoqueda[col]][col];
					matriz[li - tamanhoqueda[col]][col] = aux;
				}
			}

			//Caso a coluna tenha apenas "-1", todas as colunas à sua esquerda dao slide para a direita
			if (tamanhoqueda[col] == (cabecalho[0]))
			{
				int Colvazias = 0;
				Colvazias++;

				for (int j = (col - 1); j >= 0; j--)
				{
					for (int k = 0; k <= (cabecalho[0] - 1); k++)
					{
						matriz[k][j + 1] = matriz[k][j];
					}
				}

				for (int j = 0; j < (Colvazias); j++)
				{
					for (int k = 0; k <= (cabecalho[0] - 1); k++)
					{
						matriz[k][j] = -1;
					}
				}
			}

		}

		//Libertar a memória do vetor tamanhoqueda
		free(tamanhoqueda);
	}


}