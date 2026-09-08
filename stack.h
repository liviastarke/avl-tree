#ifndef __STACK_H__
#define __STACK_H__

#include "node.h"

#define STACK_SIZE 100

// Estrutura Pilha: LIFO - Last In, First Out
typedef struct Stack{
	void * items[STACK_SIZE];
	int top;
}Stack;

typedef struct AffectedNode{
	Node * node;
	Node * father;
	Node ** node_fth;
} AffectedNode;

int is_empty_stack(Stack * stack);

int is_full_stack(Stack * stack);

// Empilhar
int push(Stack * stack, void * item);

// Desempilhar
void * pop(Stack * stack);

void init_stack(Stack * stack);

// Retorna o valor no topo da pilha sem retirá-lo de lá.
void * top(Stack * stack);

void reverse_stack(Stack * stack);

void print_stack(Stack * stack);

#endif

