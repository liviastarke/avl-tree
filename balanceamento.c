#include "balanceamento.h"
#include "stack.h"

#include <stddef.h>
#include <stdlib.h>

Node * autobalance(Node * tree, Stack * node_stack){

	if (tree == NULL)
		return NULL;
	
	// TODO: Essa função é ineficiente, o valor a ser balanceado tem que ser o mais baixo que está desbalanceado, ou seja, mais longe da raiz, que é garantido pelo pós ordem.
	//       Mas não é necessário sempre checar a árvore inteira.
	//       A dica da IA do google era aproveitar a recursividade na função de inserção para ir atualizando a árvore de cima para baixo 	
	while (!is_empty_stack(node_stack)){

		AffectedNode * affected = pop(node_stack);

		Node * current = affected->node;
		Node ** node_fth = affected->node_fth;

		// Calcular o fator de balanceamento
		int fb = calc_fb(current);

		// Fazer rotações de acordo com o fator de balanceamento
		if (fb < -1){ // se dir é maior, rot esq

   			Node * new_root;

			if (calc_fb(current->dir) <= 0)
				new_root = left_rotation(current); // eu preciso salvar o ponteiro para o ponteiro para esse nó current, para atualizá-lo. Eu estou matando a árvore.
			else
				new_root = double_left_rotation(current);

			*node_fth = new_root;

			if (affected->father == NULL)
				tree = new_root;
		}
		else if (fb > 1){ // se esq é maior, rot dir

			Node * new_root;

			if (calc_fb(current->esq) >= 0)
			new_root = right_rotation(current);
			else
			new_root = double_right_rotation(current);

			*node_fth = new_root;

			if (affected->father == NULL)
				tree = new_root;
		}

		free(affected);
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

Node * double_left_rotation(Node * pivot){
	pivot->dir = right_rotation(pivot->dir);
	return left_rotation(pivot);
}

Node * double_right_rotation(Node * pivot){
	pivot->esq = left_rotation(pivot->esq);
	return right_rotation(pivot);
}
