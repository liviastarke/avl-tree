#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

int main(){
	node * tree = init_tree();
	node new = {0, 8, "txt", NULL, NULL};
	insert_node(tree, new);
	return 0;
}

node * init_tree(){
	node current = {1, 37215, "pdf", NULL, NULL};
	node * root = NULL;
	root = insert_node(root, current);
	return root;
}

node * insert_node(node * root, node insertion){
	if (root == NULL){
		set_node(&root, insertion);
		//root = malloc(sizeof(node));
		//*root = insertion;
		return root;
	}

	if (insertion.id == root->id){
		printf("Árvores binárias de busca não permitem elementos duplicados. ID %d já existe.\n", insertion.id);
		return root;
	}

	if (insertion.id < root->id){
		if (root->esq){
			root = insert_node(root->esq, insertion);
		}
		else{
			set_node(&(root->esq), insertion);
			//root->esq = (node *) malloc(sizeof(node));
			//*(root->esq) = insertion;
		}
	}
	return root;
}

void set_node(node ** ptr, node new_node){
	*ptr = malloc(sizeof(node));
	check_alloc_err(*ptr);
	**ptr = new_node;
}

void check_alloc_err(void *pointer){
    if (pointer == NULL){
        printf("Foi detectado um erro, não foi possível criar o tabuleiro.\n");
        exit(EXIT_FAILURE); // terminar o programa com erro
    }
}

