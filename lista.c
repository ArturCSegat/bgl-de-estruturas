#include <stdlib.h>
#include <stdio.h>
#include "pessoa.h"

typedef struct {
    Pessoa p;
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

void enq(Fila* f, Pessoa p) {
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

void deq(Fila * f) {
    Node* temp = f->prim;
    f->prim = (Node*)f->prim->next;
    if (f->prim == NULL) {
	f->fim = NULL; // Fila ficou vazia
    }
    free(temp);
}

void print(Fila * f) {
	Node* current = f->prim;
	while (current != NULL) {
		printf("%s", current->p.nome);
		if (current->next != NULL) printf(" -> ");
		current = (Node*)current->next;
	}
	printf("\n");
}

#define empty(f) (f->prim == NULL && f->fim == NULL)
