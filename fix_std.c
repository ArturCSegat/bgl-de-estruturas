#ifndef FIX_STD_C
#define FIX_STD_C

// ======================================================================
// pus essas funções pra n ter que lidar com o buffering do stdin ||||||
// ======================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_string(char* buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

char ler_input_char() {
    char buffer[10];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strlen(buffer) > 0) {
            return buffer[0];
        }
    }
    return '\0';
}
int ler_input_int() {
    char buffer[10];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        return atoi(buffer);
    }
    return 0;
}

#endif
