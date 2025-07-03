#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "parser.h"
#include "query_executor.h"

int main() {
    printf("LaksaSQL > Tapez une commande SQL\n");
    char input[512];
    while (1) {
        printf("laksaSQL> ");
        fgets(input, sizeof(input), stdin);
        if (strncmp(input, "exit", 4) == 0) break;

        Token tokens[64];
        int count = tokenize(input, tokens);
        if (count == 0) continue;

        Query *query = NULL;
        if (strcmp(tokens[0].text, "SELECT") == 0) {
            query = parse_select(tokens, count);
        }

        if (query) {
            execute_query(query);
            free(query);
        }
    }
    return 0;
}
