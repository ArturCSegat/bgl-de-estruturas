#ifndef TECNICO_C
#define TECNICO_C
#include "lista.c"
#include "chamado.h"
#include "tecnico.h"


void print_tecnico(Tecnico t, char ** out) {
    *out += sprintf(*out, "Técnico: %s | Chamados em atendimento: %d\n", 
	    t.nome, lista_count(t.chamados));

    *out += sprintf(*out, "Chamados:\n");
    lista_print(t.chamados, *out, print_chamado);
    while(**out)(*out)++;
}

#endif
