#include "balanceamento.h"
#include "stack.h"

#include <stddef.h>

Node * autobalance(Node * tree){

	if (tree == NULL)
		return NULL;

	calc_tree_height(tree);

	Stack aux_stack, node_stack;
	init_stack(&aux_stack);
	init_stack(&node_stack);
	push(&aux_stack, tree);

	while (!is_empty_stack(&node_stack)){
		Node * current = pop(&aux_stack);
		push(&node_stack, current);
		if (current->esq)
			push(&aux_stack, current->esq);
		if (current->dir)
			push(&aux_stack, current->dir);
	}

	// TODO: Essa função é ineficiente, o valor a ser balanceado tem que ser o mais baixo que está desbalanceado, ou seja, mais longe da raiz, que é garantido pelo pós ordem.
	//       Mas não é necessário sempre checar a árvore inteira.
	//       A dica da IA do google era aproveitar a recursividade na função de inserção para ir atualizando a árvore de cima para baixo 
	while (!is_empty_stack(&node_stack)){

		Node * current = pop(&node_stack);

		// Calcular o fator de balanceamento
		int fb = calc_fb(current);

		// Fazer rotações de acordo com o fator de balanceamento
		if (fb < -1){ // se dir é maior, rot esq
			tree = left_rotation(current);
		}
		else if (fb > 1){ // se esq é maior, rot dir
			tree = right_rotation(current);
		}
		// else: subtree is balanced, go up in the tree
	}
	return tree;
}

int calc_fb(Node * node){
	if (node == NULL)
		return 0;

	calc_tree_height(node);

	int left_height, right_height;

	if (node->esq)
		left_height = node->esq->height;
	else
		left_height = -1;
	if (node->dir)
                right_height = node->dir->height;
	else
                right_height = -1;

	return left_height - right_height;
}

int calc_tree_height(Node * no_raiz){

	// if (tree == NULL) // Se a árvore é nula ela não tem altura, isso faz sentido? Tem alguma utilidade?
	//	return NAN;

        int altura, altura_direita = 0, altura_esquerda = 0;

        Node * no_atual = no_raiz->esq;

        if (no_atual){
                altura_esquerda += calc_tree_height(no_atual) + 1;
        }

        no_atual = no_raiz->dir;

        if (no_atual){
                altura_direita += calc_tree_height(no_atual) + 1;
        }

        altura = altura_esquerda > altura_direita ? altura_esquerda : altura_direita;

	no_raiz->height = altura;
        return altura;
}

Node * left_rotation(Node * pivot){
	Node * z = pivot->dir;
	Node * t2 = z->esq;
	z->esq = pivot;
	pivot->dir = t2;
	calc_tree_height(pivot);
	calc_tree_height(z);
	return z;
}

Node * right_rotation(Node * pivot){
        Node * z = pivot->esq;
        Node * t2 = z->dir;
        z->dir = pivot;
        pivot->esq = t2;
        calc_tree_height(pivot);
        calc_tree_height(z);
        return z;
}
