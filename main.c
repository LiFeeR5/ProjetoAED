#define _CRT_SECURE_NO_WARNINGS

//Linha 88, podemos por l e c em vez de cabecalho[3] - 1 e cabecalho[4] - 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "arvore.h"
#include "stack.h"
#include "variantes.h"

int main(int argc, char* argv[])
{
	FILE* fp;
	FILE* fp_out;
	Comboio* solucao = NULL;

	char* fileoutname;
	int i;
	int* cabecalho;
	int** matriz;
	int azuleijoadjacente = 0;


	//Caso haja menos que dois argumentos, sai do programa
	if (argc < 2) exit(0);
	
	//Se o ficheiro de entrada não tiver a extensão correta, sai do programa
	if (strstr(argv[1], ".tilewalls") == NULL)
		exit(EXIT_FAILURE);

	//Abrir o ficheiro em modo leitura
	fp = (FILE*)fopen(argv[1], "r");
	
	//Caso o Ficheiro nao seja encontrado
	if (fp == NULL)
		exit(EXIT_FAILURE);

	//O nome do ficheiro de saída
	fileoutname = FileOutName(argv);

	//Abrir o ficheiro de saída em modo de escrita
	fp_out = (FILE*)fopen(fileoutname, "w");

	//Caso o Ficheiro nao seja encontrado
	if(fp_out == NULL)
		exit(EXIT_FAILURE);

	// O ciclo continua até chegar ao fim do ficheiro
	while (!feof(fp))
	{
		//Fazer alocação de memoria dinamica ao vetor que irá guardar o cabeçalho
		cabecalho = (int*)malloc(3 * sizeof(int));

		//Coloca o [C]olunas, [L]inhas, [v]ariavel, [l]inha, [c]oluna num vetor
		//Se a leitura do cabeçalho não foi concretizada com sucesso, dá print do cabeçalho, liberta a memoria do vetor e saí do ciclo
		if(LerCabecalho(fp, cabecalho) == -1) 
		{
			free(cabecalho);
			break;
		}

		//Alocar as linhas da matriz
		matriz = (int**)malloc(cabecalho[0] * sizeof(int*));

		//Alocar as colunas da matriz
		for (int i = 0; i < cabecalho[0]; i++)
		{
			matriz[i] = (int*)malloc((cabecalho[1]) * sizeof(int));
		}
		
		//Constroi a matriz
		matriz = ConstuirMatriz(fp, matriz, cabecalho);

		//Verifica se a variante é 1 ou 2 ou 3
		if (CheckVariante(cabecalho, fp_out) != -1)
		{
			if(cabecalho[2] == -1)
			{
				int pontos = 0;	
				//coordenada incial l=0 c=0
				Variante1(fp_out, cabecalho, matriz, 0, 0, azuleijoadjacente, &pontos);
			}

			else if(cabecalho[2] >= 0)
			{
				Variante2(solucao, fp_out, cabecalho, matriz);
			}

			else if(cabecalho[2] == -3)
			{
				Variante3(fp_out, cabecalho, matriz);
			}
			
			else
				fprintf(fp_out,"%d %d %d", cabecalho[0], cabecalho[1], cabecalho[2]);
			
		}
		//Separar os vários exercicios
		fprintf(fp_out, "\n");

		// Libertar a memoria da matriz
		for (i = 0; i < cabecalho[0]; i++)
		{
			free(matriz[i]);
		}

		free(matriz);

		//Libertar a memória do vetor cabeçalho
		free(cabecalho);
	}

	//Fechar os Ficheiros
	fclose(fp);
	fclose(fp_out);
}