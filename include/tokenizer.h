#pragma once
typedef struct {
    char *text;
} Token;

int tokenize(char *input, Token *tokens);
