#ifndef FILA_C
#define FILA_C
#include <stdlib.h>
#include <stdio.h>
#include "chamado.h"

typedef struct {
    Chamado p;
    struct Node* next;
} Node;

typedef struct {
	Node* prim;
	Node* fim;
}Fila;

Fila * nova_fila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->prim = NULL;
    f->fim = NULL;
    return f;
}

void enq_q(Fila* f, Chamado p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->p = p;
    newNode->next = NULL;
    if (f->fim != NULL) {
	f->fim->next = (struct Node*)newNode;
    }
    f->fim = newNode;
    if (f->prim == NULL) {
	f->prim = newNode;
    }
}

void deq_q(Fila * f) {
    Node* temp = f->prim;
    f->prim = (Node*)f->prim->next;
    if (f->prim == NULL) {
	f->fim = NULL; // Fila ficou vazia
    }
    free(temp);
}

int print_q(Fila * f, char * to, int n) {
	Node* current = f->prim;
	int count = 0;
	while (current != NULL && count < n) {
		count += sprintf(to + count, "%s", current->p.desc);
		if (current->next != NULL) count += sprintf(to + count, " -> ");
		current = (Node*)current->next;
	}
	return count;
}

void free_q(Fila *f) {
    Node* current = f->prim;
    Node* nextNode;
    while (current != NULL) {
	nextNode = (Node*)current->next;
	free(current);
	current = nextNode;
    }
    free(f);
}

#define empty_q(f) (f->prim == NULL && f->fim == NULL)
#endif
