#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "funcoes.h"
#include "stack.h"

struct _Comboio
{
    int **matriz;
    int coordenadas[2];
    int score;
};


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
    head->coordenadas[0] = 0;
    head->coordenadas[1] = 0;
    head->score = 0;

    return head;
}

Comboio* FirstBoard(int* cabecalho, int** matriz)
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


    return boardAtual;
}

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

    //Vamos começar a procurar manchas na mesma coordenada, pois nos casos em que uma nova mancha é formada com a queda de 
    //azuleijos, a coordenada atual tambem vai pertencer a esta mancha
    copy->coordenadas[0] = original->coordenadas[0];
    copy->coordenadas[1] = original->coordenadas[1];
    copy->score = 0;//podemos tirar isto, esta feito no initComboio

    return copy;
}


//getNewBoardMove  
void novaMatriz(Comboio* boardAtual, int *cabecalho, int* totalScore)
{
	int azuleijoadjacente = 0;

	azuleijoadjacente = Mancha(cabecalho, boardAtual->matriz, boardAtual->coordenadas[0], boardAtual->coordenadas[1], azuleijoadjacente);
		
    //if (azuleijoadjacente > 1)
	{
		*totalScore += Pontuacao(azuleijoadjacente);
        boardAtual->score = Pontuacao(azuleijoadjacente);
		Gravidade(cabecalho, boardAtual->matriz, azuleijoadjacente);

        boardAtual->coordenadas[0] = 0;
        boardAtual->coordenadas[1] = 0;
	}
}


//makeBoardMove  //Tira a mancha e cria a nova board
Comboio* currentBoard (Comboio* board, int* cabecalho, int* totalScore)
{
    Comboio* newBoard = NULL;

    newBoard = copyComboio(board, cabecalho);
    novaMatriz(newBoard, cabecalho, totalScore);
	//chamar a função mancha com as coordenadas que quremos tirar

	return newBoard;
}

void deleteBoard(Comboio *board, int L)
{
    for (int i = 0; i < L; i++)
    {
        free(board->matriz[i]);
    }
    free(board->matriz);

    free(board);
}

int ProcuraMancha(Comboio* boardAtual, int* cabecalho, int l, int c)
{
	int existeMancha = 0;

	//Verificar se está dentro da matriz 
	if (l + 1 <= (cabecalho[0] - 1))
	{
		//verifica se em cima da coordenada o valor é igual ao valor da coordenada recebida
		if (boardAtual->matriz[l + 1][c] != -1 && boardAtual->matriz[l][c] == boardAtual->matriz[l + 1][c])
		{
			existeMancha = 1;
            return existeMancha;
		}
	}

	//Verificar se está dentro da matriz 
	if (c + 1 <= (cabecalho[1] - 1))
	{
		//verifica se à direita da coordenada o valor é igual ao valor da coordenada recebida
		if (boardAtual->matriz[l][c + 1] != -1 && boardAtual->matriz[l][c] == boardAtual->matriz[l][c + 1])
		{
			existeMancha = 1;
            return existeMancha;
		}
	}

	//Verificar se está dentro da matriz 
	if (l - 1 >= 0)
	{
		//verifica se em baixo da coordenada o valor é igual ao valor da coordenada recebida
		if (boardAtual->matriz[l - 1][c] != -1 && boardAtual->matriz[l][c] == boardAtual->matriz[l - 1][c])
		{
			existeMancha = 1;
            return existeMancha;
		}
	}

	//Verificar se está dentro da matriz
	if (c - 1 >= 0)
	{
		//verifica se à esquerda da coordenada o valor é igual ao valor da coordenada recebida
		if (boardAtual->matriz[l][c - 1] != -1 && boardAtual->matriz[l][c] == boardAtual->matriz[l][c - 1])
		{
			existeMancha = 1;
            return existeMancha;
		}
	}

    return existeMancha;
}

//Ver a matriz toda, começamos a ver em l=0 e c=0, se nao encontrarmos uma mancha passamos a frente, até chegar ao fim returnando 0, se encontrarmos returnamos 1
int VerificarMatriz(Comboio* board, int* cabecalho, int l, int c)
{
    //Recebe 1 se existir mancha, ou 0 se nao existir mancha
	int existeMancha = ProcuraMancha(board, cabecalho, l, c);

	//Se houver returnamos 1
	if (existeMancha == 1)
    {
        board->coordenadas[0] = l;
        board->coordenadas[1] = c;
        return existeMancha;
    }
	//Se nao houver
	//vai para frente                       //C
	else if (existeMancha == 0 && c + 1 < cabecalho[1])
		existeMancha = VerificarMatriz(board, cabecalho, l, c + 1);


	//vai para a linha de cima			    //L						//C
	else if (existeMancha == 0 && l + 1 < cabecalho[0] && c + 1 == cabecalho[1])
		existeMancha = VerificarMatriz(board, cabecalho, l + 1, 0);

    return existeMancha;
}

int CountNum(Comboio* boardAtual, int* cabecalho)
{
    int totalNum = 0;

    for(int i = 0; i < cabecalho[0]; i++)
    {
        for(int j = 0; j < cabecalho[1]; j++)
        {
            if(boardAtual->matriz[i][j] != -1)
                totalNum++;
        }
    }

    return totalNum;
}

int ThereIsHope(Comboio* boardAtual, int* cabecalho, int* totalScore)
{
    int pontosPossiveis = *totalScore;


    int totalNum = CountNum(boardAtual, cabecalho);
    pontosPossiveis += Pontuacao(totalNum);

    return pontosPossiveis;
}

void StillMancha(Comboio* boardAtual, int* cabecalho)///////////////////CONFIRMAR
{
    int l = boardAtual->coordenadas[0];
    int c = boardAtual->coordenadas[1];

    if (c + 1 <= (cabecalho[1] - 1))// ou (c <= (cabecalho[1] - 1)
    {
        if(boardAtual->matriz[l][c] != boardAtual->matriz[l][c+1])
        {
            {
                boardAtual->coordenadas[1]++;
                exit;
            }
        }

        else
        {
            boardAtual->coordenadas[1]++;
            StillMancha(boardAtual, cabecalho);
        }
    }

    if (l + 1 <= (cabecalho[0] - 1))//(l <= (cabecalho[0] - 1))
    {
            if(boardAtual->matriz[l][c] != boardAtual->matriz[l+1][0])
            {//vai para a linha de cima
                {
                    boardAtual->coordenadas[0]++;
                    boardAtual->coordenadas[1] = 0;
                    exit;
                }
            }

            else
            {
                boardAtual->coordenadas[0]++;
                boardAtual->coordenadas[1] = 0;
                StillMancha(boardAtual, cabecalho);
            }
    }
}

Comboio* DFS(Stack *stack, int* cabecalho, int** matriz, int* totalScore)
{
    int thereAreStains = 0;
    Comboio* boardAtual = NULL;
    int cheack = 0;
    int numplays = 0;

    boardAtual = FirstBoard(cabecalho, matriz); //temos de por a matriz inicial aqui sem tirar nenhuma mancha
    push(stack, (Item) boardAtual);


    while(1)
    {
        if(cheack == 1)
            break;
        
        if(isEmpty(stack))
            break;

        boardAtual = (Comboio*)pop(stack);
        //////////////////////////////////////////////////////////////////////////////////// VER ISTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
        if(numplays > 0)
        {
            //vai para frente
            if (boardAtual->coordenadas[1] + 1 < cabecalho[1])
                boardAtual->coordenadas[1]++;


            //vai para a linha de cima			    //L						//C
            else if (boardAtual->coordenadas[0] + 1 < cabecalho[0] && boardAtual->coordenadas[1] + 1 == cabecalho[1])
            {
                boardAtual->coordenadas[0]++;
                boardAtual->coordenadas[1] = 0;
            }
        }

        while(1)
        {
            thereAreStains = VerificarMatriz(boardAtual, cabecalho, boardAtual->coordenadas[0], boardAtual->coordenadas[1]);

            if(*totalScore >= cabecalho[2] && thereAreStains == 0)//nao ha mais manchas na matriz
            {
                cheack = 1;
                push(stack,(Item)boardAtual);
                return boardAtual;
                break;
            }
        


            if(thereAreStains == 0)
            {
                numplays--;
                *totalScore -= boardAtual->score;//Confirmar isto
                deleteBoard(boardAtual, cabecalho[0]);
                break;
            }

            else if(ThereIsHope(boardAtual, cabecalho, totalScore) < cabecalho[2])
            { 
                numplays--;
                *totalScore -= boardAtual->score;//Confirmar isto           
                deleteBoard(boardAtual, cabecalho[0]);
                break;
            }
        
            else 
            {
                numplays++;
                push(stack,(Item)boardAtual);
                boardAtual = currentBoard(boardAtual, cabecalho, totalScore);
            }
        }
    }
    deleteStack(stack);
    return NULL;
}

void Variante2(Comboio* solucao, FILE* fp_out, int* cabecalho, int** matriz)
{
    Stack* stack = createStack(cabecalho[0]*cabecalho[1]/2);
    int totalScore = 0;

    solucao = DFS(stack, cabecalho, matriz, &totalScore);


    fprintf(fp_out, "%d %d %d\n", cabecalho[0], cabecalho[1], cabecalho[2]);

    if(solucao == NULL)
    {
        fprintf(fp_out, "0 -1\n");
        deleteBoard(solucao, cabecalho[0]);
    } 
    
    else
    {
       
        
        int top = getTop(stack); 
        
        fprintf(fp_out, "%d %d\n", top, totalScore);
        
        for(int i = 0; i < top; i++)
        {
            solucao = (Comboio*)peekFisrt(stack, i);
            fprintf(fp_out, "%d %d\n", solucao->coordenadas[0] +1, solucao->coordenadas[1] +1);
            deleteBoard(solucao, cabecalho[0]);
        }

        /*while(!isEmpty(stack))
        {
             deleteBoard((Comboio*)pop(stack),cabecalho[0]);
        }

        deleteStack(stack);*/

        //Free do ultimo elemento da stack
        solucao = (Comboio*)peekFisrt(stack, top);
        deleteBoard(solucao, cabecalho[0]); //implicit declaration

        deleteStack(stack);
    }
}