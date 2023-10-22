#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"


//Recebe o nome do ficheiro de entrada e devolve o nome do ficheiro de saida
char* FileOutName(char* argv[])
{
	char* fileoutname = argv[1]; //Recebe o nome do ficheiro de entrada
	char token = '.';
	char* posicaotoken = strrchr(fileoutname, token); //Retorna um ponteiro para a posiçao do ultimo '.' (token)
	strcpy(posicaotoken, ".singlestep"); //Acrescenta a extensao desejada na posiçao do ultimo '.' (token)

	return fileoutname;
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
		for (int i = 0; i <= (cabecalho[1] - 1); i++)
		{
			tamanhoqueda[i] = 0;
		}

		//Percorre as linhas de baixo para cima, ao longo das colunas 
		for (int col = 0; col <= (cabecalho[1] - 1); col++)
		{
			for (int li = 0; li <= (cabecalho[0] - 1); li++)
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

				for (int j = 0; j <= (Colvazias - 1); j++)
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

//Ver a matriz toda, começamos a ver em l=0 e c=0, se nao encontrarmos uma mancha passamos a frente se encontrarmos tiramos, fazemos a gravidade e chamamos outra vez do inicio
int RemoverManchas(int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente, int numjogadas, int** play)
{
	int coordenadaLC = matriz[l][c];
	azuleijoadjacente = Mancha(cabecalho, matriz, l, c, azuleijoadjacente);
	//Ver quando ha mancha
	if (azuleijoadjacente > 1)
	{
		//Meter noutra função
		play[numjogadas][0] = l + 1;
		play[numjogadas][1] = c + 1;


		//tamanho maximo l x c/2


		numjogadas++;
		Gravidade(cabecalho, matriz, azuleijoadjacente);
		RemoverManchas(cabecalho, matriz, 0, 0, 0, numjogadas, play);
	}

	//Se nao houver
	//vai para frente
	else if (azuleijoadjacente == 1 && c + 1 < cabecalho[1])
	{
		matriz[l][c] = coordenadaLC;
		RemoverManchas(cabecalho, matriz, l, c + 1, 0, numjogadas, play);
	}


	//vai para a linha de cima				//L							//C
	else if (azuleijoadjacente == 1 && l + 1 < cabecalho[0] && c + 1 == cabecalho[1])
	{
		matriz[l][c] = coordenadaLC;
		RemoverManchas(cabecalho, matriz, l + 1, 0, 0, numjogadas, play);
	}
	
	return numjogadas;
}

void Variante1(FILE* fp_out, int* cabecalho, int** matriz, int l, int c, int azuleijoadjacente, int numjogadas, int pontos, int** play)
{
	numjogadas = RemoverManchas(cabecalho, matriz, l, c, azuleijoadjacente, numjogadas, play);
	pontos = Pontuacao(azuleijoadjacente);

	fprintf(fp_out, "%d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2]);
	fprintf(fp_out, "%d %d\n", numjogadas, pontos);

	for(int i=0; i < numjogadas; i++)
	{
		fprintf(fp_out, "%d %d\n", play[i][0], play[i][1]);
	}
}