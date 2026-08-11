#ifndef __ARVORE_H__ // assegura que as coisas sejam definidas apenas uma vez
#define __ARVORE_H__

typedef struct File{
	int id;
	char name[32]; // máximo 31 caracteres para o nome do arquivo, para simplificar -> também poderia ser um ponteiro para uma string alocada dinamicamente
	long size;
	char extension[5]; // máximo 4 caracteres de ext (para docx, circ, etc.) desconheço extensões de arquivos mais longas
}File;

typedef struct Node{
	File file;
	struct Node * esq;
	struct Node * dir;
}Node;

Node * init_tree();
Node * insert_node(Node * tree, File inserted);
void set_node(Node ** ptr, File new_file);		// malloc and set, call check pointer
void check_alloc_err(void * ptr);			// check pointer for alloc errors
Node * remove_node(Node * root, int removed_id);	// if last node is removed, return NULL
Node * search_node(int id);
void print_tree(Node * root);

#endif

