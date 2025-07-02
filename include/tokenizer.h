// tokenizer.h

#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct {
    char *text;
    int type; // Type de jeton, si on veut le supporter plus tard
} Token;

Token *tokenize(const char *input, int *count);
void free_tokens(Token *tokens, int count);

#endif // TOKENIZER_H
