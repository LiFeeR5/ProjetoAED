#ifndef STACK_H
#define STACK_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define Item void*

typedef struct stack_ Stack;

typedef struct stackBestRamo_ StackBestRamo;

Stack*  createStack (unsigned capacity);
int     isFull (Stack*);
int     isEmpty (Stack*);
void    push (Stack*, Item);
Item    pop (Stack* stack);
Item    peekFisrt(Stack* stack, int index);
void    deleteStack (Stack *stack);
int     getTop(Stack *stack);

#endif
