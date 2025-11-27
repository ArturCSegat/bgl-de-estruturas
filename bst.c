#ifndef BST_C
#define BST_C

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tecnico.c"
#include "item.c"

typedef enum {
	Tec,
	Est,
} TipoBst;

typedef struct Node {
	char key[50];
	struct Node* left;
	struct Node* right;
	TipoBst tipo;
	union {
		Tecnico tecnico;  
		Item item;
	} dados;
} BstNode;

// --- Implementação das Funções ---

BstNode* bst_create_node(char* key, TipoBst tipo) {
    BstNode* node = (BstNode*)malloc(sizeof(BstNode));
    strcpy(node->key, key);
    node->tipo = tipo;
    node->left = NULL;
    node->right = NULL;
    
    if (tipo == Est) {
        node->dados.item.quant = 0;
        strcpy(node->dados.item.nome, key);
    }
    if (tipo == Tec) {
        strcpy(node->dados.item.nome, key);
	node->dados.tecnico.chamados = NULL;
    }
    return node;
}

BstNode* bst_insert(BstNode* root, char* key, TipoBst tipo) {
    if (root == NULL) return bst_create_node(key, tipo);

    int cmp = strcmp(key, root->key);

    if (cmp < 0)
        root->left = bst_insert(root->left, key, tipo);
    else if (cmp > 0)
        root->right = bst_insert(root->right, key, tipo);
    
    return root;
}

BstNode* bst_search(BstNode* root, char* key) {
    if (root == NULL || strcmp(root->key, key) == 0)
        return root;

    if (strcmp(key, root->key) < 0)
        return bst_search(root->left, key);
    
    return bst_search(root->right, key);
}

// Nova função: Travessia In-Order para listar
char * bst_print_inorder(BstNode* root, char * buf) {
    if (root != NULL) {
        buf = bst_print_inorder(root->left, buf);
        
        if (root->tipo == Tec) {
	    print_tecnico(root->dados.tecnico, &buf);
	    buf += sprintf(buf, "===================================\n");
        } else {
            buf += sprintf(buf, "  [ITEM] %s | Qtd: %d\n", root->key, root->dados.item.quant);
        }

        buf = bst_print_inorder(root->right, buf);
    }
    return buf;
}

void free_bst(BstNode* root) {
    if (root != NULL) {
	free_bst(root->left);
	free_bst(root->right);
	free(root);
    }
}

#endif
