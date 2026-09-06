#include "arvore.h"

#include "balanceamento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	
	Node * tree = NULL;

	int option;
	int value;
	int depth = 0;

	while(1){

		clean();
		
		printf("==================================\n");
		printf("| 1. INSERIR NÓ            \t |\n");
		printf("| 2. REMOVE NÓ             \t |\n");
		printf("| 3. IMPRESSÕES            \t |\n");
		printf("| 4. BUSCAR NÓ POR ID      \t |\n");
		printf("| 5. SAIR                  \t |\n");
		printf("==================================\n");
		printf("ESCOLHA UMA OPÇÃO: ");
		option = check_int();

		switch(option){
			case 1:
				while(1){
					clean();
					
					printf("=============================\n");
					printf("| 1.INSERIR NÓ ÚNICO        |\n");
					printf("| 2.INSERIR ARVORE COMPLETA |\n"); // Se o usuário escolher essa opção vai deletar qualquer valor inserido anteriormente na árvore
					printf("| 3.VOLTAR                  |\n");
					printf("=============================\n");
					printf("ESCOLHA UMA OPÇÃO: ");

					option = check_int();

					switch(option){
						case 1:
							File new;

							printf("Digite o ID: ");
							new.id = check_int();

							printf("Digite o nome do arquivo: ");
							check_string(new.name, 32);

							printf("Digite o tamanho do arquivo: ");
							new.size = check_int();

							printf("Digite a extensão: ");
							check_string(new.extension, 5);

							tree = insert_node(tree, new);
						break;

						case 2:
							tree = init_tree();
							printf("ÁRVORE COMPLETA INSERIDA\n");
						break;

						case 3:
						break;
						
						default:
							printf("ERRO: OPÇÃO INVÁLIDA\n");
					}

					if(option == 3)
						break;

					pause();
				}
			break;

			case 2:
				clean();
				printf("DIGITE UM VALOR PARA SER REMOVIDO: ");
				value = check_int();
				tree = remove_node(tree, value);
			break;

			case 3:
				while(1){
					clean();
					
					printf("=============================\n");
					printf("| 1.COMPLETA                |\n");
					printf("| 2.EM ORDEM                |\n"); 
					printf("| 3.FORMA DE GRAFO          |\n");
					printf("| 4.VOLTAR                  |\n");
					printf("=============================\n");
					option = check_int();
					
					switch(option){
						case 1:
							clean();
							print_tree(tree);
						break;

						case 2:
							clean();
							inOrder(tree);
							
						break;

						case 3:
							clean();
							Reverse_in_Order(tree, depth);
						break;

						case 4:
						break;

						default:
							printf("ERRO: OPÇÃO INVÁLIDA\n");
					}
					
					if(option == 4)
						break;

					pause();
				}
			break;

			case 4:
				clean();
				printf("Insira o ID do valor buscado: ");
				value = check_int();

				Node * search_result = search_node_id(tree, value);

				if (search_result == NULL){
					printf("Não encontrado\n");
					break;
				}

				printf("Encontrado ID %d\n", search_result->file.id);
			break;

			case 5:
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

/* Inserção sem recursividade, acho que não vou usar mais... */
// Node * insert_node(Node * root, File insertion) {
// 	if (root == NULL){
// 		set_node(&root, insertion); // se só tem um nó, eu não preciso balancear.
// 		calc_tree_height(root);
// 		return root;
// 	}
// 
// 	Node * current = root;
// 	Node * parent = NULL;
// 
// 	while (current != NULL) {
// 		parent = current;
//  		if (insertion.id < current->file.id) {
//  			current = current->esq;
//  		}
// 
// 		else if (insertion.id > current->file.id) {
//  			current = current->dir;
//  		}
// 
// 		else {
// 			printf("Árvores binárias de busca não permitem elementos duplicados. ID %d já existe.\n", insertion.id);
//  			return root;
//  		}
//  	}
// 
//  	if (insertion.id < parent->file.id) {
//  		set_node(&parent->esq, insertion);
//  	}
// 
// 	else {
//  		set_node(&parent->dir, insertion);
//  	}
// 
// 	// root = autobalance(root);
//  	return root;
// }

/**
 * insert_node recursivo deve ser usado para balancear a árvore.
 * Eu viajo até o fundo em subárvores e volto chamando autabaleanceamento até a raiz.
 */
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

	// root = autobalancing(root);
	return root;
}

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

        Node *child;

        if(current->esq != NULL){
            child = current->esq;
        }else{
            child = current->dir;
        }

        if(current != root){

            if(current == father->esq)
                father->esq = child;
            else
                father->dir = child;

        }else{
            root = child;
        }

        free(current);
    }

    else{

        Node * successor_father = current;
        Node * successor = current->dir;

        while(successor->esq != NULL){
            successor_father = successor;
            successor = successor->esq;
        }

        if(successor_father != current)
            successor_father->esq = successor->dir;
        else
            successor_father->dir = successor->dir;

        current->file = successor->file;

        free(successor);
    }

    //root = autobalance(root);
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

void inOrder(Node * root){
	if (root == NULL)
        return;

    inOrder(root->esq);

    printf(" %d <", root->file.id);

    inOrder(root->dir);
}

void Reverse_in_Order(Node * root, int depth){
	if (root == NULL)
        return;

    Reverse_in_Order(root->dir, depth + 1);
    
    for(int i = 0; i < depth; i++){
        printf("\t");
    }
    printf(" %d \n", root->file.id);

    Reverse_in_Order(root->esq, depth + 1);
}

void clean(){
    printf("\033[H\033[2J"); // Essa sequência simplesmente 'rola' a tela para que não dê para ver nada do que estava lá antes.
			     // Acho bom para debugar, parece que funciona em qualquer plataforma.
    //system("clear");
}

void pause(){
    printf("\nPressione ENTER para continuar...");
    getchar();
}

// alteração no check_int para impedir dele pular a próxima leitura
int check_int(){
    char entrada[100];
    int value;

    while(1){
        fgets(entrada, sizeof(entrada), stdin);

        if(sscanf(entrada, "%d", &value) == 1){ // sscanf lê como se fosse um string
            return value;
        }

        printf("\nVALOR INVÁLIDO!\n");
        printf("DIGITE UM VALOR INTEIRO: ");
    }
}

void check_string(char *string, int tamanho){
    while(1){
        fgets(string, tamanho, stdin);

        if(strchr(string, '\n') == NULL){ // Se ele não encontrar o \n isso indica que a string é maior do que devia
            int c;
            while((c = getchar()) != '\n' && c != EOF);

            printf("\nNOME MUITO GRANDE!\n");
            printf("DIGITE NOVAMENTE: ");
            continue;
        }

        string[strcspn(string, "\n")] = '\0'; // Econtra a posição do \n na string e troca pelo \0

        for(int i = 0; string[i] != '\0'; i++){
            if(string[i] == ' '){
                string[i] = '_';
            }
        }
        return;
    }
}