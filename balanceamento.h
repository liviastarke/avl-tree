#ifndef __BALANCEAMENTO_H__
#define __BALANCEAMENTO_H__

#include "arvore.h" // preciso conhecer Node!

int calc_tree_height(Node * no_raiz);
Node * left_rotation(Node * pivot); // pivot é um bom nome???
Node * right_rotation(Node * pivot);

#endif

