#ifndef GLOBALS_C
#define GLOBALS_C

#include "fila.c"
#include "heap.c"
#include "bst.c"

#define VOLTOU 69
#define SAIR 67

unsigned long long HORA_ATUAL = 0;
Fila* fila_normal;
Heap* fila_prioridade;
BstNode* arvore_tecnicos = NULL; 
BstNode* arvore_estoque = NULL;
NodeLista* lista_atendimento = NULL;
NodeLista* lista_suspenso = NULL;
NodeLista* historico = NULL;

#endif
