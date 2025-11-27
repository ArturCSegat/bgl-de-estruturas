     #ifndef LISTA_C
#define LISTA_C

#include <stdlib.h>
#include <stdio.h>

typedef enum {
	HIST,
	SUSP,
	EM_AT,
} TipoLista;

typedef struct NodeLista {
    TipoLista tipo;
	void* dados; // deve fazer cast Chamado* para evitar dependência circular
	struct NodeLista* next;
	struct NodeLista* prev;
} NodeLista;

NodeLista* lista_add(NodeLista* head, void* dados, TipoLista tipo) {
    NodeLista* novo = malloc(sizeof(NodeLista));
    novo->dados = dados;
    novo->tipo = tipo;
    novo->next = head; 
    novo->prev = NULL;

    if (head != NULL) {
        head->prev = novo;
    }
    return novo;
}

int lista_count(NodeLista * head) {
    int count = 0;
    NodeLista* curr = head;
    while (curr != NULL) {
	count++;
	curr = curr->next;
    }
    return count;
}

void lista_print(NodeLista* head, char*buf,  void (*print_func)(NodeLista*, char**)) {
    NodeLista* curr = head;
    if (curr == NULL) {
	sprintf(buf, "Esta Lista esta vazia\n");
    }
    while(curr != NULL) {
	print_func(curr, &buf);
	buf += sprintf(buf, "\n");
        curr = curr->next;
    }
}

NodeLista * lista_pop(NodeLista ** head, void * needle, int (*cmp)(void* d1, void*d2)) {
	if (!needle) {
		return NULL;
	}

	NodeLista * curr = *head;
	while (curr != NULL) {
        	if (cmp(needle, curr->dados)) {
                        if (curr->prev && curr->next) {
				curr->next->prev = curr->prev;
				curr->prev->next = curr->next;
			} else if (curr->prev) {
				curr->prev->next = NULL;
			} else if (curr->next) {
				curr->next->prev = NULL;
			}

			if(curr == *head) {
				*head = curr->next;
				if (*head) {
					(**head).prev = NULL;
				}
			}

			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

void free_lista(NodeLista * head, void (*free_dados)(void *)) {
	NodeLista * curr = head;
	while (curr != NULL) {
		NodeLista * next = curr->next;
		if (free_dados) {
			free_dados(curr->dados);
		}
		free(curr);
		curr = next;
	}
}

#endif     
