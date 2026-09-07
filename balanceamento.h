#ifndef __BALANCEAMENTO_H__
#define __BALANCEAMENTO_H__

#include "arvore.h" // preciso conhecer Node!

int calc_fb(Node * node);
int calc_tree_height(Node * no_raiz);
Node * left_rotation(Node * pivot); // pivot é um bom nome???
Node * right_rotation(Node * pivot);
Node * double_left_rotation(Node * pivot);
Node * double_right_rotation(Node * pivot);
Node * autobalance(Node * tree);

#endif

