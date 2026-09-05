#include "stack.h"
#include "node.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_empty_stack(Stack * stack){
	return (stack->top == -1);
}

int is_full_stack(Stack * stack){
	return stack->top == STACK_SIZE - 1;
}

int push(Stack * stack, void * item){
	if (is_full_stack(stack)){
		printf("PUSH FAILED: pilha cheia\n");
		return -1;
	}
	stack->items[++stack->top] = item;
	return 0;
}

void * pop(Stack * stack){
	if (is_empty_stack(stack)){
		printf("POP FAILED: pilha vazia\n");
		return NULL;
	}
	return stack->items[stack->top--];
}

void init_stack(Stack * stack){
	stack->top = -1;
}

void * top(Stack * stack){
	void * value = pop(stack);
	stack->top++;
	return value;
}

void reverse_stack(Stack * stack){
	Stack * inverted = (Stack *) malloc(sizeof(Stack));

	if (inverted == NULL){
		printf("Alloc error!\n");
		return;
	}

	init_stack(inverted);
	while (!is_empty_stack(stack)){
		push(inverted, pop(stack));
	}
	memcpy(stack, inverted, sizeof(Stack)); // Alternativamente, em vez de memcpy "return inverted;" para criar uma nova pilha invertida
	free(inverted);
}

void print_stack(Stack * stack){
	for (int i = 0; i < STACK_SIZE; i++){
		if (i <= stack->top){
			printf("Stack item [%d]: %p -> %d\n", i, stack->items[i], ((Node *) stack->items[i])->file.id);
		}
	}
}

