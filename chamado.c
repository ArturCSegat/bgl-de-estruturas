#ifndef CHAMADO_C
#define CHAMADO_C

#include "item.c"
#include "lista.c"
#include "bst.c"
#include "globals.c"
#include <stdio.h>
#include "chamado.h"

void print_chamado(NodeLista* node, char ** out) {
   Chamado * chamado = (Chamado*) node->dados;
    int i = 0;
    *out += sprintf(*out, "--------------------------------\n");
    *out += sprintf(*out, "Situação: %s | Tecnico: %s\n", chamado->desc, chamado->tecnico->nome);
    *out += sprintf(*out, "Status: %s\n", (node->tipo == SUSP ? "[SUSPENSO]" : "[EM ATENDIMENTO]"));

    *out += sprintf(*out, "Lista de Materiais:\n");
        
    // Loop pelos itens do chamado
    for(int i = 0; i < chamado->itens_len; i++) {
	    char* nome_item = chamado->itens[i].nome;
	    int qtd_necessaria = chamado->itens[i].quant;
	    int qtd_estoque = 0;

	    BstNode* node_est = bst_search(arvore_estoque, nome_item);

	    if (node_est != NULL && node_est->tipo == Est) {
		    qtd_estoque = node_est->dados.item.quant;
	    }

	    *out += sprintf(*out, "  > %-15s | Precisa: %-3d / Estoque Atual: %d\n", 
			    nome_item, qtd_necessaria, qtd_estoque);
    }
    *out += sprintf(*out, "--------------------------------\n");
}

int cmp_chamado(void * a, void *b) {
	Chamado * ca = (Chamado*)a;
	Chamado * cb = (Chamado*)b;
	return strcmp(ca->desc, cb->desc) == 0;
}

#endif
