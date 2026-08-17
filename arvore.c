#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arvore.h"

int main(){
	Node * tree = init_tree();
	File new = {0, "meu_arquivo", 8, "txt"};
	
	int option;
	int value;

	while(1){

		clean();
		printf("==========================\n");
		printf("| 1. INSERT NODE\t |\n");
		printf("| 2. REMOVE NODE\t |\n");
		printf("| 3. PRINT TREE \t |\n");
		printf("| 4. EXIT       \t |\n");
		printf("==========================\n");
		printf("CHOSE AN OPTION: ");
		scanf("%d", &option);
		switch(option){
			case 1:
				clean();
				insert_node(tree, new);
				pause();
			break;

			case 2:
				clean();
				printf("DIGIT A VALUE TO BE ROMOVED: ");
				scanf("%d", &value);
				remove_node(tree, value);
				pause();
			break;

			case 3:
				clean();
				print_tree(tree);
				pause();
			break;
			
			case 4:
				return 0;
			
			default:
				clean();
				printf("ERROR: OPTION INVALID\n");
				pause();
		}
	}
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

Node *remove_node(Node *root, int removed_id){
    if(root == NULL)
        return root;

    Node * current = root;
    Node * father = NULL;

    while(current != NULL && current->file.id != removed_id){
        father = current;

        if(removed_id < current->file.id){
            current = current->esq;
        }else{
            current = current->dir;
        }
    }

    if(current == NULL){
        return root;
    }


    if(current->esq == NULL && current->dir == NULL){

        if(current != root){

            if(father->esq == current){
                father->esq = NULL;
            }else{
                father->dir = NULL;
            }

        }else{
            root = NULL;
        }

        free(current);
    }


    else if(current->esq == NULL || current->dir == NULL){

        Node *son;

        if(current->esq != NULL){
            son = current->esq;
        }else{
            son = current->dir;
        }

        if(current != root){

            if(current == father->esq)
                father->esq = son;
            else
                father->dir = son;

        }else{
            root = son;
        }

        free(current);
    }

    else{

        Node * sucessor_father = current;
        Node * sucessor = current->dir;

        while(sucessor->esq != NULL){
            sucessor_father = sucessor;
            sucessor = sucessor->esq;
        }

        if(sucessor_father != current)
            sucessor_father->esq = sucessor->dir;
        else
            sucessor_father->dir = sucessor->dir;

        current->file = sucessor->file;

        free(sucessor);
    }

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

void clean(){
    system("clear");
}

void pause(){
    printf("\nPress ENTER to continue...");
    getchar();
    getchar();
}

