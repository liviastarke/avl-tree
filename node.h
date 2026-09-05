#ifndef __NODE_H__
#define __NODE_H__

typedef struct File{
	int id;
	char name[32]; // máximo 31 caracteres para o nome do arquivo, para simplificar -> também poderia ser um ponteiro para uma string alocada dinamicamente
	long size;
	char extension[5]; // máximo 4 caracteres de ext (para docx, circ, etc.) desconheço extensões de arquivos mais longas
}File;

typedef struct Node{
	File file;
	int height;
	struct Node * esq;
	struct Node * dir;
}Node;

#endif
