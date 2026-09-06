#ifndef __ARVORE_H__ // assegura que as coisas sejam definidas apenas uma vez
#define __ARVORE_H__

#include "node.h"

Node * init_tree();
Node * insert_node(Node * tree, File inserted);
void set_node(Node ** ptr, File new_file);		// malloc and set, call check pointer
void check_alloc_err(void * ptr);			// check pointer for alloc errors
Node * remove_node(Node * root, int removed_id);	// if last node is removed, return NULL
Node * search_node_id(Node * root, int search_id);
void print_tree(Node * root);
void inOrder(Node * root);
void Reverse_in_Order(Node * root, int depth);
void clean();
void pause();
int check_int();
void check_string(char *string, int tamanho);

#endif

