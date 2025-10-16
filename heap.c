#include <stdio.h>
#include <stdlib.h>
#include "./pessoa.h"

#define left(i) (2 * i)
#define right(i) (2 * i)+1

typedef struct {
    Pessoa *data;
    size_t size;
    size_t capacity;
} Heap;
#define empty(h) (h->size == 1)

Heap * new_heap() {
    Heap *h = malloc(sizeof(Heap));
    h->data = malloc(sizeof(Pessoa) * 10);
    h->size = 1; // ignorar primeiro indice pra melhorar a formula
    h->capacity = 10;
    return h;
}

void enq(Heap * h, Pessoa p) {
	if (h->size == h->capacity) {
		h->capacity *= 2;
		h->data = realloc(h->data, sizeof(int) * h->capacity);
	}
	h->data[h->size] = p;
	int curr = h->size;
	h->size++;
	while(curr > 1) {
		Pessoa parrent = h->data[curr/2];
		if  (h->data[curr].caso < parrent.caso) {
			Pessoa temp =  parrent;
			h->data[curr/2] = h->data[curr];
			h->data[curr] = temp;
			curr = curr/2;
			continue;
		} 
		break;
	}
}

Pessoa * peek(Heap * h) {
	if (h->size > 1) {
		return &h->data[1];
	}
	return NULL;
}

void pop(Heap * h) {
	Pessoa last = h->data[h->size - 1];
	h->data[h->size - 1].caso = 0;
	h->data[1] = last;
	h->size--;
	int curr = 1;
	while(curr < h->size) {
		Pessoa leftv = h->data[left(curr)];
		Pessoa rightv = h->data[left(curr)];
		int min, max;
		Pessoa minv, maxv;
		min = leftv.caso < rightv.caso ? left(curr) : right(curr);
		max = leftv.caso >= rightv.caso ? left(curr) : right(curr);
		minv = h->data[min];
		maxv = h->data[max];
		
		if (minv.caso > 0 && minv.caso < h->data[curr].caso) {
			Pessoa temp = h->data[curr];
			h->data[curr] = minv;
			h->data[min] = temp;
			curr = min;
			continue;
		}  
		if (maxv.caso > 0 && maxv.caso < h->data[curr].caso) {
			Pessoa temp = h->data[curr];
			h->data[curr] = maxv;
			h->data[max] = temp;
			curr = max;
			continue;
		}
		break;
	}
}

int main(void) {
	Heap * h = new_heap();
	Pessoa p1 = {5, "Joao"};
	Pessoa p2 = {3, "Maria"};
	Pessoa p4 = {1, "Ana"};
	Pessoa p5 = {4, "Lucas"};
	Pessoa p3 = {8, "Artur"};
	enq(h, p1);
	enq(h, p2);
	enq(h, p3);
	enq(h, p4);
	enq(h, p5);
	while (!empty(h)) {
		Pessoa * p = peek(h);
		printf("Caso: %d, Nome: %s\n", p->caso, p->nome);
		pop(h);
	}
}

