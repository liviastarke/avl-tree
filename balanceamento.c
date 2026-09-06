#include "balanceamento.h"
#include "stack.h"

Node * autobalance(Node * tree){

	// if (tree == NULL)
	// 	return NULL;

	calc_tree_height(tree);

	Node * current;

	Stack node_stack;
	init_stack(&node_stack);
	push(&node_stack, current);

	// TODO: Essa função está errada, o valor a ser balanceado tem que ser o mais baixo que está desbalanceado, ou seja, mais longe da raiz.
	//       A dica da IA do google era aproveitar a recursividade na função de inserção para ir atualizando a árvore de cima para baixo 
	//       (que bom que eu não apaguei a versão recursiva). Só espero que essa seja a causa de aparecerem nós preenchidos com lixo de memória que causam SIGSEGV...
	while (!is_empty_stack(&node_stack)){

		int fb;
		current = pop(&node_stack);

		// Calcular o fator de balanceamento e decidir se o nó tem filhos para colocar na pilha
		if (current->dir && current->esq){
			fb = current->esq->height - current->dir->height;
			push(&node_stack, current->esq);
			push(&node_stack, current->dir);
		}
		else if (current->dir){
			fb = -1 - current->dir->height;
			push(&node_stack, current->dir);
		}
		else if (current->esq){
			fb = current->esq->height - 1; // detestei essa repetição de código...
			push(&node_stack, current->esq);
		}
		else{
			fb = 0;
		}

		// Fazer rotações de acordo com o fator de balanceamento
		if (fb < -1){ // se dir é maior, rot esq
			tree = left_rotation(current);
		}
		else if (fb > 1){ // se esq é maior, rot dir
			tree = right_rotation(current);
		}
		// else: tree is balanced

	}
	// } while (!is_empty_stack(&node_stack));
	return tree;
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
