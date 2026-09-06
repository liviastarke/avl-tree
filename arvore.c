#include "arvore.h"

#include "balanceamento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	Node * tree = init_tree();
	File new = {0, "meu_arquivo", 8, "txt"};
	
	int option;
	int value;
	int depth = 0;

	while(1){

		clean();
		printf("==================================\n");
		printf("| 1. INSERIR NÓ            \t |\n");
		printf("| 2. REMOVE NÓ             \t |\n");
		printf("| 3. IMPRIME COMPLETO      \t |\n");
		printf("| 4. IMPRIME ID            \t |\n");
		printf("| 5. IMPRIME EM ORDEM      \t |\n");
		printf("| 6. BUSCAR NÓ POR ID      \t |\n");
		printf("| 7. SAIR                  \t |\n");
		printf("==================================\n");
		printf("ESCOLHA UMA OPÇÃO: ");
		scanf("%d", &option); // TODO: sanitizar entrada (scanf não limpa o buffer ao receber entradas inválidas)
		switch(option){
			case 1:
				clean();
				// TODO: entrar o ID e nome do arquivo.
				tree = insert_node(tree, new);
			break;

			case 2:
				clean();
				printf("DIGITE UM VALOR PARA SER REMOVIDO: ");
				scanf("%d", &value);
				tree = remove_node(tree, value);
			break;

			case 3:
				clean();
				print_tree(tree);
			break;
			
			case 4:
				clean();
				emOrdemInversa(tree, depth);
			break;

			case 5:
				clean();
				emOrdem(tree);
			break;

			case 6:
				clean();
				printf("Insira o ID do valor buscado: ");
				scanf("%d", &value);
				Node * search_result = search_node_id(tree, value);
				if (search_result == NULL){
					printf("Não encontrado\n");
					break;
				}
				printf("Encontrado ID %d\n", search_result->file.id); // substituir por função print_node
			break;

			case 7:
				while(tree != NULL)
					tree = remove_node(tree, tree->file.id);
				return 0;

			default:
				clean();
				printf("ERRO: OPÇÃO INVÁLIDA\n");
		}
		pause();
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

/* Inserção sem recursividade, não sei se uso ou mudo... */
Node * insert_node(Node * root, File insertion) {
	if (root == NULL){
		set_node(&root, insertion); // se só tem um nó, eu não preciso balancear.
		calc_tree_height(root);
		return root;
	}

	Node * current = root;
	Node * parent = NULL;

	while (current != NULL) {
		parent = current;
 		if (insertion.id < current->file.id) {
 			current = current->esq;
 		}

		else if (insertion.id > current->file.id) {
 			current = current->dir;
 		}

		else {
			printf("Árvores binárias de busca não permitem elementos duplicados. ID %d já existe.\n", insertion.id);
 			return root;
 		}
 	}

 	if (insertion.id < parent->file.id) {
 		set_node(&parent->esq, insertion);
 	}

	else {
 		set_node(&parent->dir, insertion);
 	}

	root = autobalance(root);
 	return root;
}

/**
 * insert_node recursivo deve ser usado para balancear a árvore.
 * Eu viajo até o fundo em subárvores e volto chamando autabaleanceamento até a raiz.
 */
// Node * insert_node(Node * root, File insertion){
// 	if (root == NULL){
// 		set_node(&root, insertion);
// 		return root;
// 	}
// 
// 	if (insertion.id == root->file.id){
// 		printf("Árvores binárias de busca não permitem elementos duplicados. ID %d já existe.\n", insertion.id);
// 		return root;
// 	}
// 
// 	if (insertion.id < root->file.id){
// 		root->esq = insert_node(root->esq, insertion);
// 	}
// 	else if (insertion.id > root->file.id){
//                 root->dir = insert_node(root->dir, insertion);
//         }
// 
// 	root = autobalance(root);
// 	return root;
// }

void set_node(Node ** ptr, File new_file){
	Node new_node = {new_file, 0, NULL, NULL};
	*ptr = malloc(sizeof(Node));
	check_alloc_err(*ptr);
	**ptr = new_node;
}

void check_alloc_err(void *pointer){
    if (pointer == NULL){
        printf("Fatal: Foi detectado um erro. Saindo...\n");
        exit(EXIT_FAILURE); // terminar o programa com erro
    }
}

Node * remove_node(Node *root, int removed_id){
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

    // O valor a remover não estava na árvore
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
            root = NULL; // agora esse caminho não apresentou o resultado esperado
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

    root = autobalance(root);
    return root;
}

Node * search_node_id(Node * root, int search_id){
	if (root == NULL || root->file.id == search_id){
		return root;
	}

	if (root->file.id < search_id){
		return search_node_id(root->dir, search_id);
	}

	// else (root->file.id > search_value)
	return search_node_id(root->esq, search_id);
}

void print_tree(Node * root){
	if (root == NULL)
		return;
	print_tree(root->esq);
	printf("Nó %d: %s.%s\tTamanho: %ld bytes.\n", root->file.id, root->file.name, root->file.extension, root->file.size);
	print_tree(root->dir);
}

void emOrdem(Node * root){
	if (root == NULL)
        return;

    emOrdem(root->esq);

    printf(" > (%d) ", root->file.id);

    emOrdem(root->dir);
}

void emOrdemInversa(Node * root, int depth){
	if (root == NULL)
        return;

    emOrdemInversa(root->dir, depth + 1);
    
    for(int i = 0; i < depth; i++){
        printf("\t");
    }
    printf(" %d \n", root->file.id);

    emOrdemInversa(root->esq, depth + 1);
}

void clean(){
    printf("\033[H\033[2J"); // Essa sequência simplesmente 'rola' a tela para que não dê para ver nada do que estava lá antes.
			     // Acho bom para debugar, parece que funciona em qualquer plataforma.
    //system("clear");
}

void pause(){
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

