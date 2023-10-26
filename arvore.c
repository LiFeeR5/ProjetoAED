#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "funcoes.h"
#include "stack.h"

//Inicia todas variavéis da estrutura Comboio
Comboio* initComboio(int* cabecalho)
{
    Comboio *head = NULL;

    /* allocate initial game board structure */
    head = (Comboio*) malloc(sizeof(Comboio));

    /* now allocate the actual board, just an L x C matrix */
	head->matriz = (int**) malloc(cabecalho[0]*sizeof(int*));
 
    for (int i = 0; i < cabecalho[0]; i++)
    {
        head->matriz[i] = (int*) malloc(cabecalho[1]*sizeof(int));
    }
 
    /* there is no last play yet */
    head->score = 0;
    head->totalmanchas = 0;
    head->cnt = 0;

    head->manchacoord = (int**) malloc(((cabecalho[0]*cabecalho[1])/2) * sizeof(int*));

    for (int i = 0; i < ((cabecalho[0]*cabecalho[1])/2); i++)
    {
        head->manchacoord[i] = (int*) malloc(2*sizeof(int));
    }

    return head;
}

//Cria uma nova matriz e chama o initComboio para inicializar tds as variaveis, copiando a matriz original para a nova matriz
Comboio* copyComboio(Comboio* original, int* cabecalho){
    int i, j;
    Comboio* copy = NULL;

    copy = initComboio(cabecalho);
  
    for(i = 0; i < cabecalho[0]; i++)
    {
        for(j = 0; j < cabecalho[1]; j++)
        {
            copy->matriz[i][j] = original->matriz[i][j];
        }
    }

    return copy;
}

//Retira a mancha que as coordenadas da matriz anterior indicam 
void novaMatriz(Comboio* boardAtual, Comboio* newBoard, int *cabecalho, int* totalScore)
{
	int azuleijoadjacente = 0;

	azuleijoadjacente = Mancha(cabecalho, newBoard->matriz, boardAtual->manchacoord[boardAtual->cnt][0], boardAtual->manchacoord[boardAtual->cnt][1], azuleijoadjacente);
		
	*totalScore += Pontuacao(azuleijoadjacente);
    newBoard->score = Pontuacao(azuleijoadjacente);
	Gravidade(cabecalho, newBoard->matriz, azuleijoadjacente);
}

//copia a board->matriz para a matrizTemporaria para encontrar as coordenadas de todas as manchas dessa matriz. 
//Guarda tds as coordenadas das manchas no board->coordmanchas
void FindAllManchas(Comboio* board, int* cabecalho, int** matrizTemporaria)
{
    int cnt = 0;

    for(int i = 0; i < cabecalho[0]; i++)
    {
        for(int j = 0; j < cabecalho[1]; j++)
        {
            matrizTemporaria[i][j] = board->matriz[i][j];
        }
    }

    for(int i = 0; i < cabecalho[0]; i++)
    {
        for(int j = 0; j < cabecalho[1]; j++)
        {
            int azuleijosadjacentes = 0;
            int valorLC = matrizTemporaria[i][j];
            azuleijosadjacentes = Mancha(cabecalho, matrizTemporaria, i, j, azuleijosadjacentes);

            if(azuleijosadjacentes == 1)
                matrizTemporaria[i][j] = valorLC;

            if (azuleijosadjacentes != 1)
            {
                board->manchacoord[cnt][0] = i;
                board->manchacoord[cnt][1] = j;
                cnt++;
            }
        }
    }

    board->totalmanchas = cnt;     
}


//Cria a nova board, tira a mancha e encontra todas as coordenadas de todas as manchas da nova matriz
Comboio* currentBoard (Comboio* board, int* cabecalho, int* totalScore, int** matrizTemporaria)
{
    Comboio* newBoard = NULL;

    //Copia a matriz para board->matriz e inicializa o board->coordenadas e score
    newBoard = copyComboio(board, cabecalho);

    //retira a mancha, faz a gravidade e soma os pontos ao pontos total
    novaMatriz(board, newBoard, cabecalho, totalScore);

	//copia a board->matriz para a matrizTemporaria e guarda tds as coordenadas das manchas no board->coordmanchas
    FindAllManchas(newBoard, cabecalho, matrizTemporaria);

	return newBoard;
}

//Inicializas a board toda, copia a matriz para a matrizTemporaria para encontrar as coordenadas de tds as manchas da matriz
//Guarda as coordenadas das manchas tds no boardAtual->manchacoor
Comboio* FirstBoard(int* cabecalho, int** matriz, int** matrizTemporaria)
{
    Comboio* boardAtual = NULL;

    boardAtual = initComboio(cabecalho);

    for(int i = 0; i < cabecalho[0]; i++)
    {
        for(int j = 0; j < cabecalho[1]; j++)
        {
            boardAtual->matriz[i][j] = matriz[i][j];
        }
    }

    //copia a board->matriz para a matrizTemporaria e guarda tds as coordenadas das manchas no board->coordmanchas
    FindAllManchas(boardAtual, cabecalho, matrizTemporaria);


    return boardAtual;
}

//Da free da estrutura da matriz atual
void deleteBoard(Comboio *board, int* cabecalho)
{
    for (int i = 0; i < cabecalho[0]; i++)
    {
        free(board->matriz[i]);
    }
    free(board->matriz);

    for (int i = 0; i < ((cabecalho[0]*cabecalho[1])/2); i++)
    {
        free(board->manchacoord[i]);
    }
    free(board->manchacoord);

    free(board);
}

//Comparação do qsort
int compararDecrescente(const void *a, const void *b) {
    // Convertemos os ponteiros void * de volta para o tipo apropriado (int *)
    int *intA = (int *)a;
    int *intB = (int *)b;

    // A lógica da comparação para ordem decrescente
    return (*intB - *intA);
}

//Verifica se este ramo tem uma solução possivel
int ThereIsHope(Comboio* boardAtual, int* cabecalho, int* totalScore, int* array_qsort)
{
    int pontosPossiveis = *totalScore;
    int cnt = 0;
    int tamanho = cabecalho[0]*cabecalho[1];
    int comparador = 0;
    int k = 0;

    for(int i = 0; i < cabecalho[0]; i++)
    {
        for(int j = 0; j < cabecalho[1]; j++)
        {
            array_qsort[k] = boardAtual->matriz[i][j];
            k++;
        }
    }

    // Chama qsort com a função de comparação personalizada
    qsort(array_qsort, tamanho, sizeof(int), compararDecrescente);

    comparador = array_qsort[0];

    for(int i = 0; i < cabecalho[0]*cabecalho[1]; i++) //32221
    {
        if (comparador == array_qsort[i])
            cnt++;

        else if (comparador != array_qsort[i] && cnt == 1)
        {
            cnt = 1;
            comparador = array_qsort[i];
        }
            

        else
        {
            comparador = array_qsort[i];
            pontosPossiveis += Pontuacao(cnt);
            cnt = 1;
         }
    }

    return pontosPossiveis;
}

//Quando recuamos no ramo, adicionamos 1 ao cnt para posteriormente verificar as coordenadas da mancha seguinte
void NextMancha(Comboio* boardAtual)
{
    if (boardAtual->cnt < boardAtual->totalmanchas)
        boardAtual->cnt++;

}

Comboio* DFS2(Stack *stack, int* cabecalho, int** matriz, int* totalScore, int** matrizTemporaria, int* qsort_array)
{
    Comboio* boardAtual = NULL;
    int check = 0;

    boardAtual = FirstBoard(cabecalho, matriz, matrizTemporaria); //inicializamos tudo e ja sabemos as coordenadas das manchas
    push(stack, (Item) boardAtual);


    while(1)
    {
        if(check == 1)
            break;
        
        if(isEmpty(stack))
            break;

        boardAtual = (Comboio*)pop(stack);

        if(check == 2)
        {
            NextMancha(boardAtual);
            check = 0;
        }

        while(1)
        {
            if(*totalScore >= cabecalho[2] && boardAtual->totalmanchas == 0)//nao ha mais manchas na matriz
            {
                check = 1;
                push(stack,(Item)boardAtual);
                return boardAtual;
                break;
            }
            if(boardAtual->totalmanchas == 0 || boardAtual->cnt == boardAtual->totalmanchas)
            {
                check = 2;
                *totalScore -= boardAtual->score;//Confirmar isto
                //numplays = 1;
                deleteBoard(boardAtual, cabecalho);
                break;
            }
            else if(ThereIsHope(boardAtual, cabecalho, totalScore, qsort_array) < cabecalho[2])
            { 
                check = 2;
                *totalScore -= boardAtual->score;     
                deleteBoard(boardAtual, cabecalho);
                break;
            }
            else 
            {
                push(stack,(Item)boardAtual);
                boardAtual = currentBoard(boardAtual, cabecalho, totalScore, matrizTemporaria);//inicializamos tudo e ja sabemos as coordenadas das manchas
            }
        }
    }
    deleteStack(stack);
    return NULL;
}

void DFS3(Stack *stack, int* cabecalho, int** matriz, int** matrizTemporaria, int** saveBestRamo, int* qsort_array, int* PontosAtuais)
{
    Comboio* boardAtual = NULL;
    Comboio* aux = NULL;
    int check = 0;
    int numplays = 0;
    int PontosMaximos = 0;

    boardAtual = FirstBoard(cabecalho, matriz, matrizTemporaria); //inicializamos tudo e ja sabemos as coordenadas das manchas
    push(stack, (Item) boardAtual);


    while(1)
    {   
        if(isEmpty(stack))
            break;

        boardAtual = (Comboio*)pop(stack);

        if(check == 2)
        {
            NextMancha(boardAtual);
            check = 0;
        }

        while(1)
        {
            if(boardAtual->totalmanchas == 0 && *PontosAtuais > PontosMaximos)//nao ha mais manchas na matriz
            {
                
                for(int i = 0; i < numplays +1; i++)
                {
                    if(i == 0)
                    {
                        saveBestRamo[i][0] = numplays;
                        saveBestRamo[i][1] = *PontosAtuais;
                    }

                    else
                    {
                        aux = (Comboio*)peekFisrt(stack, i-1);
                        saveBestRamo[i][0] = aux->manchacoord[aux->cnt][0];
                        saveBestRamo[i][1] = aux->manchacoord[aux->cnt][1];
                    }
                }

                PontosMaximos = *PontosAtuais;
                numplays--;
                check = 2;
                *PontosAtuais -= boardAtual->score; //Desnecessário, pois boardAtual->score = 0
                deleteBoard(boardAtual, cabecalho);
                break;
            }
            if(boardAtual->totalmanchas == 0 || boardAtual->cnt == boardAtual->totalmanchas)
            {
                numplays--;
                check = 2;
                *PontosAtuais -= boardAtual->score;
                deleteBoard(boardAtual, cabecalho);
                break;
            }
            else if(ThereIsHope(boardAtual, cabecalho, PontosAtuais, qsort_array) < PontosMaximos)
            {
                ThereIsHope(boardAtual, cabecalho, PontosAtuais, qsort_array);
                numplays--;
                check = 2;
                *PontosAtuais -= boardAtual->score;       
                deleteBoard(boardAtual, cabecalho);
                break;
            }
            else 
            {
                numplays++;
                push(stack,(Item)boardAtual);
                boardAtual = currentBoard(boardAtual, cabecalho, PontosAtuais, matrizTemporaria);//inicializamos tudo e ja sabemos as coordenadas das manchas
            }
        }
    }
    deleteStack(stack);
}