#include "balanceamento.h"

Node * autobalance(Node * tree){
	calc_tree_height(tree);

	Node * actual_node = tree;
	// LOOP HERE, HOW?
	int fb = actual_node->dir->height - actual_node->dir->height;

	if (fb < 1){ // se dir é maior, rot esq
		left_rotation(actual_node);
	}
	else if (fb > 1){ // se esq é maior, rot dir
		right_rotation(actual_node);
	}
	// else: tree is balanced
}

int calc_tree_height(Node * no_raiz){

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
