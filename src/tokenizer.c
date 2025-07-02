// tokenizer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

// 🟦 Fonction utilitaire pour extraire les jetons d'une commande SQL
Token *tokenize(const char *input, int *count) {
    Token *tokens = malloc(sizeof(Token) * 128);
    int token_count = 0;

    const char *delims = " ,();\n\t";
    char *copy = strdup(input);
    char *tok = strtok(copy, delims);

    while (tok != NULL) {
        tokens[token_count].text = strdup(tok);
        tokens[token_count].type = 0;
        token_count++;
        tok = strtok(NULL, delims);
    }

    free(copy);
    *count = token_count;
    return tokens;
}

// 🟦 Libère la mémoire des jetons
void free_tokens(Token *tokens, int count) {
    for (int i = 0; i < count; i++) {
        free(tokens[i].text);
    }
    free(tokens);
}
