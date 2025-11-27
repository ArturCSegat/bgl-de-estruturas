#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.c"
#include "tecnico.c"
#include "item.c"
#include "chamado.c"
#include "fila.c"
#include "heap.c"
#include "bst.c"
#include "fix_std.c" 
#include "globals.c"


char desenha(const char* oq) {
    HORA_ATUAL++;
    system("clear"); 
    
    printf("=== SISTEMA DE ATENDIMENTO ===\n\n");

    if (strcmp(oq, "menu") == 0) {
        printf("1 - Gerenciar Chamados\n");
        printf("2 - Gerenciar Tecnicos\n");
        printf("3 - Gerenciar Estoque\n");
        printf("4 - Sair\n");
    } 

    else if (strcmp(oq, "menu_chamado") == 0) {
        printf("--- Central de Atendimento ---\n");
        printf("1 - Novo Chamado \n");
        printf("2 - Ver chamados em andamento\n");
        printf("3 - Ver fila de chamados\n");
        printf("4 - Ver histórico de prontos\n");
        printf("5 - Voltar\n");
    }

    else if (strcmp(oq, "criar_chamado") == 0) {
        printf("--- Criando Chamado ---\nDescrição do Chamado:");
        return 0;
    }

    else if (strcmp(oq, "visualizar_listas") == 0) {
        printf("=== Chamados em Atendimento ===\n");
	char atendimento_buf[2048];
        lista_print(lista_atendimento, atendimento_buf, print_chamado);
	printf("%s\n", atendimento_buf);
        
        printf("\n=== Chamados Suspensos (Falta de Estoque) ===\n");
	char suspenso_buf[2048];
        lista_print(lista_suspenso, suspenso_buf, print_chamado);
	printf("%s\n", suspenso_buf);
        
        printf("\n1 - Atualizar Chamado\n");
        printf("\n2 - Voltar\n");
        printf("Opção: ");
        return ler_input_char();
    }
    else if (strcmp(oq, "remover_chamado") == 0) {
	    printf("==== Removendo Chamado =====\n\n");
	    printf("Entre com a descrição do chamado: ");
	    return 0;
    }
    else if (strcmp(oq, "ver_historico") == 0) {
	    printf("==== Histórico  =====\n\n");
	    char * buf = malloc(2048);
	    lista_print(historico, buf, print_chamado);
	    printf("%s\n", buf);
	    free(buf);
	    return 0;
    }

    else if (strcmp(oq, "menu_tec") == 0) {
        printf("--- Menu Tecnicos ---\n1. Novo Tecnico\n2. Buscar Tecnico\n3. Listar Todos\n4. Voltar\n");
    }
    else if (strcmp(oq, "add_tec") == 0) { printf("--- Novo Tecnico ---\nNome:\n"); return 0; }
    else if (strcmp(oq, "busca_tec") == 0) { printf("--- Buscar Tecnico ---\nNome:\n"); return 0; }
    else if (strcmp(oq, "lista_tec") == 0) { printf("--- Lista de Tecnicos ---\n"); return 0; }

    else if (strcmp(oq, "menu_est") == 0) {
        printf("--- Menu Estoque ---\n1. Entrada de Item\n2. Consultar Item\n3. Relatorio Geral\n4. Voltar\n");
    }
    else if (strcmp(oq, "add_item") == 0) { printf("--- Entrada de Estoque ---\nNome do Item:\n"); return 0; }
    else if (strcmp(oq, "busca_item") == 0) { printf("--- Consultar Item ---\nNome:\n"); return 0; }
    else if (strcmp(oq, "lista_est") == 0) { printf("--- Relatorio de Estoque ---\n"); return 0; }

    else if (strcmp(oq, "visualizar_filas") == 0) {
        printf("--- Filas de Espera ---\n\n");
        char buffer_heap[1024] = {0};
        print_pq(fila_prioridade, buffer_heap, 1024);
        char buffer_fila[1024] = {0};
        print_q(fila_normal, buffer_fila, 1024);

	const char * con = !empty_pq(fila_prioridade) && !empty_q(fila_normal) ? " -> " : "";
	if (empty_pq(fila_prioridade) && empty_q(fila_normal)) strcpy(buffer_heap, "Filas vazias");
        printf("%s%s%s\n", buffer_heap, con, buffer_fila);

        printf("\n1 - Atender Chamado\n");
        printf("\n2 - Voltar\n");
        printf("Opção: ");
        return ler_input_char();
    }
    
    printf("\nOpção: ");
    return ler_input_char();
}

int opcao_fila_normal() {
    desenha("add_normal"); 
    Chamado p; p.hora = HORA_ATUAL; p.caso = 0;
    ler_string(p.desc, 50);
    if (strlen(p.desc)) {
        enq_q(fila_normal, p);
        printf("\n adicionado na fila normal.\n");
    }
    printf("Enter para voltar..."); ler_input_char();
    return VOLTOU;
}

int opcao_fila_prioridade() {
    desenha("add_prio");
    Chamado p; p.hora = HORA_ATUAL;
    ler_string(p.desc, 50);
    if (strlen(p.desc) > 0) {
        printf("Prioridade (0-5): ");
        int prio = ler_input_int();
        if (prio < 0) prio = 0; if (prio > 5) prio = 5;
        p.caso = prio;
        enq_pq(fila_prioridade, p);
        printf("\n adicionaod na fila prioritária (%d).\n", prio);
    }
    printf("Enter para voltar..."); ler_input_char();
    return VOLTOU;
}


int logica_add_tecnico() {
    desenha("add_tec");
    char nome[50]; ler_string(nome, 50);
    if (strlen(nome) > 0) {
        arvore_tecnicos = bst_insert(arvore_tecnicos, nome, Tec);
        printf("\nTécnico cadastrado!\n");
    }
    ler_input_char(); return VOLTOU;
}

int logica_busca_tecnico() {
    desenha("busca_tec");
    char nome[50]; ler_string(nome, 50);
    if (strlen(nome) > 0) {
        BstNode* res = bst_search(arvore_tecnicos, nome);
        if (res && res->tipo == Tec) {
		char * buf = malloc(2048);
		char * b= buf;
		printf("\nEncontrado:\n");
		print_tecnico(res->dados.tecnico, &buf);
		printf("%s\n", b);
		free(buf);
	}
        else printf("\nNão encontrado.\n");
    }
    ler_input_char(); return VOLTOU;
}

int logica_listar_tecnicos() {
    desenha("lista_tec");
    if (!arvore_tecnicos) printf("Nenhum técnico cadastrado.\n");
    else {
	char buf[2048] = {0};
	bst_print_inorder(arvore_tecnicos, buf);
	printf("%s\n", buf);
    }
    printf("\nEnter para voltar..."); ler_input_char(); return VOLTOU;
}

int menu_tecnicos() {
    char op = desenha("menu_tec");
    if (op == '1') logica_add_tecnico();
    else if (op == '2') logica_busca_tecnico();
    else if (op == '3') logica_listar_tecnicos();
    else if (op == '4') return VOLTOU;
    return menu_tecnicos();
}

int logica_add_item() {
    desenha("add_item");
    char nome[50]; ler_string(nome, 50);
    if (strlen(nome) > 0) {
        printf("Quantidade a adicionar: ");
        int qtd = ler_input_int();
        
        arvore_estoque = bst_insert(arvore_estoque, nome, Est);
        BstNode* node = bst_search(arvore_estoque, nome);
        if (node) {
            node->dados.item.quant = qtd; // Aqui define o valor. Se quisesse somar: += qtd
            printf("\nEstoque atualizado: %s = %d\n", nome, node->dados.item.quant);
        }
    }
    ler_input_char(); return VOLTOU;
}

int logica_busca_item() {
    desenha("busca_item");
    char nome[50]; ler_string(nome, 50);
    if (strlen(nome) > 0) {
        BstNode* res = bst_search(arvore_estoque, nome);
        if (res && res->tipo == Est) printf("\nItem: %s | Qtd: %d\n", res->key, res->dados.item.quant);
        else printf("\nItem não cadastrado.\n");
    }
    ler_input_char(); return VOLTOU;
}

int logica_listar_estoque() {
    desenha("lista_est");
    if (!arvore_estoque) printf("Estoque vazio.\n");
    else {
	    char buf[2048] = {0};
	    bst_print_inorder(arvore_estoque, buf);
	    printf("%s\n", buf);
    }

    printf("\nEnter para voltar..."); ler_input_char(); return VOLTOU;
}

int menu_estoque() {
    char op = desenha("menu_est");
    if (op == '1') logica_add_item();
    else if (op == '2') logica_busca_item();
    else if (op == '3') logica_listar_estoque();
    else if (op == '4') return VOLTOU;
    return menu_estoque();
}

int logica_criar_chamado() {
    desenha("criar_chamado");

    Chamado novo = {0};
    ler_string(novo.desc, 50);
    novo.itens_len = 0;

    while(novo.itens_len < 10) {
        printf("\nItem %d/10 (Enter vazio para finalizar): ", novo.itens_len + 1);
        char nome_item[50]; ler_string(nome_item, 50);
        if (strlen(nome_item) == 0) break;

        printf("Quantidade necessária: ");
        int qtd = ler_input_int();
        if (qtd <= 0) continue;

        strcpy(novo.itens[novo.itens_len].nome, nome_item);
        novo.itens[novo.itens_len].quant = qtd;
        novo.itens_len++;
    }

    printf("Tem prioridade?\nsim: 1\nnao: 2\n");
    char s = ler_input_char();
    if (s == '1') {
	    printf("Que prioridade? (0-5)\n");
	    novo.caso  = ler_input_int();
	    enq_pq(fila_prioridade, novo);
    } else enq_q(fila_normal, novo);


    printf("Chamado %s criado\n", novo.desc);
    printf("Enter para continuar...");
    ler_input_char();
    return VOLTOU;
}


int opcao_atender_chamado() {
    Chamado * chamado = malloc(sizeof(Chamado));
    int from_prio = 0;

    if (!empty_pq(fila_prioridade)) {
	memcpy(chamado, peek_pq(fila_prioridade), sizeof(Chamado));
	deq_pq(fila_prioridade);
	from_prio = 1;
    } else if (!empty_q(fila_normal)) {
	memcpy(chamado, &fila_normal->prim->p, sizeof(Chamado));
	deq_q(fila_normal);
    } else {
	printf("Nenhum chamado na fila.\n");
	printf("Enter para voltar..."); ler_input_char();
	return VOLTOU;
    }

    printf("Atendendo chamado: %s\n", chamado->desc);
    printf("Selecione um técnico:\n");
    char nome_tec[50];
    ler_string(nome_tec, 50);
    BstNode* tec_node = bst_search(arvore_tecnicos, nome_tec);
    if (!tec_node || tec_node->tipo != Tec) {
	printf("Técnico não encontrado. Cancelando atendimento.\n");
	if (from_prio) enq_pq(fila_prioridade, *chamado);
	else enq_q(fila_normal, *chamado);
	free(chamado);
	printf("Enter para continuar...");
	ler_input_char();
	return VOLTOU;
    }
    printf("Técnico %s selecionado.\n", tec_node->key);
    int valido = 1;
    for (int i = 0; i < chamado->itens_len; i++) {
	    BstNode* item_node = bst_search(arvore_estoque, chamado->itens[i].nome);
	    if (!item_node || item_node->tipo != Est || item_node->dados.item.quant < chamado->itens[i].quant) {
		    printf("Item %s insuficiente no estoque. Chamado suspenso.\n", chamado->itens[i].nome);
		    valido = 0;
		    break;
	    }
    }

    chamado->tecnico = &tec_node->dados.tecnico;
    tec_node->dados.tecnico.chamados = 
	    lista_add(tec_node->dados.tecnico.chamados, (void*)chamado, valido ? EM_AT : SUSP);

    if (valido) {
	    lista_atendimento = lista_add(lista_atendimento, (void*)chamado, EM_AT);
    } else lista_suspenso = lista_add(lista_suspenso, (void*)chamado, SUSP);

    printf("Chamado atendido com sucesso.\n");
    printf("Enter para continuar...");
    ler_input_char();
    return VOLTOU;
}

int opcao_remover_chamado() {
	desenha("remover_chamado");
	char desc[50];
	ler_string(desc, 50);

	NodeLista * chamado_at = lista_pop(&lista_atendimento, desc, cmp_chamado);
	NodeLista * chamado_sus = lista_pop(&lista_suspenso, desc, cmp_chamado);
	NodeLista * chamado_n = chamado_at ? chamado_at : chamado_sus;
	if (!chamado_n) {
		printf("Chamado não encontrado\nEnter para continuar...\n");
		ler_input_char();
		return VOLTOU;
	}
	Chamado * chamado = (Chamado*) chamado_n->dados;

	if (chamado_n->tipo == EM_AT) {
		for (int i = 0; i<chamado->itens_len; i++) {
			BstNode* item_node = bst_search(arvore_estoque, chamado->itens[i].nome);
			if (item_node && item_node->tipo == Est) {
				item_node->dados.item.quant -= chamado->itens[i].quant;
			}
			printf("%d\n", i);
		}

		chamado_n->tipo = HIST;
		historico = lista_add(historico, (void*)chamado, HIST);
	} else {
		int valido = 1;
		for (int i = 0; i < chamado->itens_len; i++) {
			BstNode* item_node = bst_search(arvore_estoque, chamado->itens[i].nome);
			if (!item_node || item_node->tipo != Est || item_node->dados.item.quant < chamado->itens[i].quant) {
				printf("Item %s insuficiente no estoque. Chamado suspenso.\n", chamado->itens[i].nome);
				valido = 0;
				break;
			}
		}

		if (valido) {
			lista_atendimento = lista_add(lista_atendimento, (void*)chamado, EM_AT);
		} else lista_suspenso = lista_add(lista_suspenso, (void*)chamado, SUSP);
	}

	printf("Chamado atualizado com sucesso.\n");
	printf("Enter para continuar...");
	ler_input_char();
	return VOLTOU;
}

int logica_visualizar_listas() {
    char op = desenha("visualizar_listas"); // Agora imprime dentro do desenha
    if (op == '1') return opcao_remover_chamado();
    if (op == '2') return VOLTOU;
    return logica_visualizar_listas();
}

int opcao_ver_filas() {
    char op = desenha("visualizar_filas");
    if (op == '1') return opcao_atender_chamado();
    if (op == '2') return VOLTOU;
    return opcao_ver_filas();
}

int opcao_ver_histórico() {
    desenha("ver_historico");
    printf("Funcionalidade não implementada ainda.\n");
    printf("Enter para voltar..."); ler_input_char();
    return VOLTOU;
}

int menu_chamado() {
    char op = desenha("menu_chamado");
    if (op == '1') logica_criar_chamado();
    else if (op == '2') logica_visualizar_listas();
    else if (op == '3') opcao_ver_filas();
    else if (op == '4') opcao_ver_histórico();
    else if (op == '5') return VOLTOU;
    return menu_chamado();
}

void menu_principal() {
    while(1) {
        char opcao = desenha("menu");
        int r = 0;

        if (opcao == '1') r = menu_chamado();
        else if (opcao == '2') r = menu_tecnicos();
        else if (opcao == '3') r = menu_estoque();
        else if (opcao == '4') r = SAIR;

        if (r == SAIR) {
            system("clear");
            printf("Encerrando sistema...\n");
            // Aqui deveria ter os frees de todas as estruturas
            free_q(fila_normal);
            free_pq(fila_prioridade);
            exit(0);
        }
    }
}

int main() {
    // Inicialização
    fila_normal = nova_fila();
    fila_prioridade = new_heap();
    arvore_tecnicos = NULL;
    arvore_estoque = NULL;
    lista_atendimento = NULL;
    lista_suspenso = NULL;

    menu_principal();
    
    free_q(fila_normal);
    free_pq(fila_prioridade);
    free_bst(arvore_tecnicos);
    free_bst(arvore_estoque);
    free_lista(lista_atendimento, NULL);
    free_lista(lista_suspenso, NULL);
    free_lista(historico, NULL);

    return 0;
}                   
