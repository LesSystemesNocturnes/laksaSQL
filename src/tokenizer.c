#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

int tokenize(char *input, Token *tokens) {
    int count = 0;
    char *tok = strtok(input, " (),;\n");
    while (tok && count < 64) {
        tokens[count++].text = tok;
        tok = strtok(NULL, " (),;\n");
    }
    return count;
}
