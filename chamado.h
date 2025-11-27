#ifndef CHAMADO_H
#define CHAMADO_H

#include "tecnico.h"
#include "item.c"

typedef struct {
	char desc[50];
	Tecnico  * tecnico;
	Item itens[10];
	int itens_len;
	unsigned long long hora;
	int caso;
} Chamado;

void print_chamado(NodeLista* node, char ** out);
#endif
