#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "funcoes.h"
#include "stack.h"

//Ver a matriz toda, começamos a ver em l=0 e c=0, se nao encontrarmos uma mancha passamos a frente se encontrarmos tiramos, fazemos a gravidade e chamamos outra vez do inicio
int RemoverManchas(int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente, int numjogadas, int** play, int* pontos)
{
	int coordenadaLC = matriz[l][c];
	azuleijoadjacente = Mancha(cabecalho, matriz, l, c, azuleijoadjacente);
	//Ver quando ha mancha
	if (azuleijoadjacente > 1)
	{
		//Meter noutra função
		play[numjogadas][0] = l + 1;
		play[numjogadas][1] = c + 1;


		*pontos += Pontuacao(azuleijoadjacente);


		numjogadas++;
		Gravidade(cabecalho, matriz, azuleijoadjacente);

		numjogadas = RemoverManchas(cabecalho, matriz, 0, 0, 0, numjogadas, play, pontos);
	}

	//Se nao houver
	//vai para frente
	else if (azuleijoadjacente == 1 && c + 1 < cabecalho[1])
	{
		matriz[l][c] = coordenadaLC;
		numjogadas = RemoverManchas(cabecalho, matriz, l, c + 1, 0, numjogadas, play, pontos);
	}


	//vai para a linha de cima						//L						//C
	else if (azuleijoadjacente == 1 && l + 1 < cabecalho[0] && c + 1 == cabecalho[1])
	{
		matriz[l][c] = coordenadaLC;
		numjogadas = RemoverManchas(cabecalho, matriz, l + 1, 0, 0, numjogadas, play, pontos);
	}

	return numjogadas;
}

//check
void Variante1(FILE* fp_out, int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente, int* pontos)
{
	int** play;

	int tamanho = ((cabecalho[0] * cabecalho[1])) / 2;

	play = (int**)malloc(tamanho * sizeof(int*));

	for (int i = 0; i < tamanho; i++)
	{
		play[i] = (int*)malloc(2 * sizeof(int));
	}

	int numjogadas = RemoverManchas(cabecalho, matriz, l, c, azuleijoadjacente, 0, play, pontos);

	fprintf(fp_out, "%d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2]);

	if (numjogadas != 0)
	{
		fprintf(fp_out, "%d %d\n", numjogadas, *pontos);

		for (int i = 0; i < numjogadas; i++)
		{
			fprintf(fp_out, "%d %d\n", play[i][0], play[i][1]);
		}
	}

	else
	{
		fprintf(fp_out, "0 0");
	}

	for (int i = 0; i < tamanho; i++)
	{
		free(play[i]);
	}
	free(play);
}

void FreeV2(int** matrizTemporaria, int* qsort_array, int* cabecalho)
{
	free(qsort_array);

	for (int i = 0; i < cabecalho[0]; i++)
	{
		free(matrizTemporaria[i]);
	}
	free(matrizTemporaria);
}

void Variante2(Comboio* solucao, FILE* fp_out, int* cabecalho, int** matriz)
{
	Stack* stack = createStack(cabecalho[0] * cabecalho[1] / 2);
	int totalScore = 0;
	int** matrizTemporaria;
	int* qsort_array;

	qsort_array = (int*)malloc(cabecalho[0] * cabecalho[1] * sizeof(int));

	matrizTemporaria = (int**)malloc(cabecalho[0] * sizeof(int*));/////////////////Dar FREE NO FINAL DA VARIANTE 2

	for (int i = 0; i < cabecalho[0]; i++)
	{
		matrizTemporaria[i] = (int*)malloc(cabecalho[1] * sizeof(int));
	}

	solucao = DFS2(stack, cabecalho, matriz, &totalScore, matrizTemporaria, qsort_array);

	FreeV2(matrizTemporaria, qsort_array, cabecalho);

	fprintf(fp_out, "%d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2]);

	if (solucao == NULL)
		fprintf(fp_out, "0 -1\n");

	else
	{
		int top = getTop(stack);

		fprintf(fp_out, "%d %d\n", top, totalScore);

		for (int i = 0; i < top; i++)
		{
			solucao = (Comboio*)peekFisrt(stack, i);
			fprintf(fp_out, "%d %d\n", solucao->manchacoord[solucao->cnt][0] + 1, solucao->manchacoord[solucao->cnt][1] + 1);
			deleteBoard(solucao, cabecalho);
		}

		//Free do ultimo elemento da stack
		solucao = (Comboio*)peekFisrt(stack, top);

		deleteBoard(solucao, cabecalho);
		deleteStack(stack);
	}
}






void FreeV3(int** matrizTemporaria, int** saveBestRamo, int* qsort_array, int* cabecalho, int linhas)
{
	free(qsort_array);

	for (int i = 0; i < linhas + 1; i++)
	{
		free(saveBestRamo[i]);
	}
	free(saveBestRamo);

	for (int i = 0; i < cabecalho[0]; i++)
	{
		free(matrizTemporaria[i]);
	}
	free(matrizTemporaria);
}

void Variante3(FILE* fp_out, int* cabecalho, int** matriz)
{
	Stack* stack = createStack(cabecalho[0] * cabecalho[1] / 2);
	int** matrizTemporaria;
	int** saveBestRamo;
	int* qsort_array;
	int PontosAtuais = 0;

	int linhas = ((cabecalho[0] * cabecalho[1]) / 2);

	qsort_array = (int*)malloc(cabecalho[0] * cabecalho[1] * sizeof(int));

	saveBestRamo = (int**)malloc((linhas + 1) * sizeof(int*));

	for (int i = 0; i < linhas + 1; i++)
	{
		saveBestRamo[i] = (int*)malloc(2 * sizeof(int));
	}

	matrizTemporaria = (int**)malloc(cabecalho[0] * sizeof(int*));/////////////////Dar FREE NO FINAL DA VARIANTE 2

	for (int i = 0; i < cabecalho[0]; i++)
	{
		matrizTemporaria[i] = (int*)malloc(cabecalho[1] * sizeof(int));
	}

	DFS3(stack, cabecalho, matriz, matrizTemporaria, saveBestRamo, qsort_array, &PontosAtuais);

	fprintf(fp_out, "%d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2]);

	if (saveBestRamo[0][0] == 0)
	{
		fprintf(fp_out, "0 -1");
	}

	else
	{
		int i = 0;

		fprintf(fp_out, "%d %d\n", saveBestRamo[i][0], saveBestRamo[i][1]);

		for (int i = 1; i <= saveBestRamo[0][0]; i++)
		{
			fprintf(fp_out, "%d %d\n", saveBestRamo[i][0] + 1, saveBestRamo[i][1] + 1);
		}
	}

	FreeV3(matrizTemporaria, saveBestRamo, qsort_array, cabecalho, linhas);
}