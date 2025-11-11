#include <stdio.h>
#include "pessoa.h"
#include "./fila.c"
#include "./heap.c"
#include <stdlib.h>

int main () {
	printf("Sistema de Atendimento\n");
	Fila* fila = nova_fila();
	Heap* heap = new_heap();

	unsigned long long hora = 1;
	for (; hora > 0; hora++) {
		printf("Escolha sua opção:\n");
		printf("1 - Adicionar pessoa na fila comum\n");
		printf("2 - Adicionar pessoa na fila prioritária\n");
		printf("3 - Atender próxima pessoa\n");
		printf("4 - Mostrar fila\n");
		printf("5 - Sair\n");
		int opcao;
		scanf("%d", &opcao);
		switch (opcao) {
			case 1: {
					Pessoa p;
					p.hora = hora;
					printf("Digite o nome da pessoa: ");
					scanf("%s", p.nome);
					enq_q(fila, p);
					printf("%s adicionado(a) na fila comum.\n", p.nome);
					break;
				}
			case 2: {
					Pessoa p;
					p.hora = hora;
					printf("Digite o nome da pessoa: ");
					scanf("%s", p.nome);
					printf("Qual dos casos prioritários se aplica?\n");
					printf("1 - Emergência médica\n");
					printf("2 - Idoso (acima de 65 anos)\n");
					printf("3 - Gestante\n");
					printf("4 - Pessoa com deficiência\n");
					scanf("%d", &p.caso);
					enq_pq(heap, p);

					printf("%s adicionado(a) na fila prioritária.\n", p.nome);
					break;
				}
			case 3: {
					if (!empty_pq(heap)) {
						Pessoa* p = peek_pq(heap);
						printf("Atendendo pessoa prioritária: %s\n", p->nome);
						deq_pq(heap);
					} else if (!empty_q(fila)) {
						Node* current = fila->prim;
						printf("Atendendo pessoa comum: %s\n", current->p.nome);
						deq_q(fila);
					} else {
						printf("Não há pessoas para atender.\n");
					}
					break;
				}
			case 4: {
					int n = 1000;
					int i = 0;
					char buffer[1000] = "";
					if (!empty_pq(heap)) {
						i += print_pq(heap, buffer, n);
						n -= i;

					}
					if (!empty_q(fila)) {
						if (n != 1000) {
							int temp = sprintf(buffer + i, " -> ");
							i += temp; n -= temp;
						}
						print_q(fila, buffer + i, n);
					}
					printf("Fila atual: %s\n", buffer);
					break;
				}
			case 5: {
					printf("Saindo do sistema.\n");
					goto end;
				}
			default:
				printf("Opção inválida. Tente novamente.\n");
		}
		system("clear");
	}

end:
	free_q(fila);
	free_pq(heap);
	return 0;
}
