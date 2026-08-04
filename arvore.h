#ifndef __ARVORE_H__ // assegura que as coisas sejam definidas apenas uma vez
#define __ARVORE_H__

typedef struct node{
	int id;
	long size;
	char extension[5]; // máximo 4 caracteres de ext (para docx, circ, etc.) desconheço extensões de arquivos mais longas
	struct node * esq;
	struct node * dir;
}node;

node * init_tree();
node * insert_node(node * tree, node inserted);
void set_node();			// malloc and set, call check pointer
void check_alloc_err(void * ptr);	// check pointer for alloc errors

#endif

