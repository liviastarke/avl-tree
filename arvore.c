#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arvore.h"

int main(){
	Node * tree = init_tree();
	File new = {0, "meu_arquivo", 8, "txt"};
	insert_node(tree, new);
	print_tree(tree);
	return 0;
}

Node * init_tree(){
	File current = {1, "Sem título", 37215, "pdf"};
	Node * root = NULL;
	root = insert_node(root, current);

	srand(time(NULL));
	for (int i = 0; i < 7; i++){
		current.id = rand();
		root = insert_node(root, current);
	}

	return root;
}

Node * insert_node(Node * root, File insertion){
	if (root == NULL){
		set_node(&root, insertion);
		return root;
	}

	if (insertion.id == root->file.id){
		printf("Árvores binárias de busca não permitem elementos duplicados. ID %d já existe.\n", insertion.id);
		return root;
	}

	if (insertion.id < root->file.id){
		root->esq = insert_node(root->esq, insertion);
	}
	else if (insertion.id > root->file.id){
                root->dir = insert_node(root->dir, insertion);
        }

	return root;
}

void set_node(Node ** ptr, File new_file){
	Node new_node = {new_file, NULL, NULL};
	*ptr = malloc(sizeof(Node));
	check_alloc_err(*ptr);
	**ptr = new_node;
}

void check_alloc_err(void *pointer){
    if (pointer == NULL){
        printf("Foi detectado um erro, não foi possível criar o tabuleiro.\n");
        exit(EXIT_FAILURE); // terminar o programa com erro
    }
}

Node * remove_node(Node * root, int removed_id){
	return root;
}

Node * search_node_id(Node * root, int search_id){
	if (root == NULL || root->file.id == search_id){
		return root;
	}

	if (root->file.id < search_id){
		return search_node_id(root->esq, search_id);
	}

	// else (root->file.id > search_value)
	return search_node_id(root->dir, search_id);
}

void print_tree(Node * root){
	if (root == NULL)
		return;
	printf("Nó %d: %s.%s\tTamanho: %ld bytes.\n", root->file.id, root->file.name, root->file.extension, root->file.size);
	print_tree(root->esq);
	print_tree(root->dir);
}

