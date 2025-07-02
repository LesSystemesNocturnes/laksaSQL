// parser.h

#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "query.h"

Query *parse_select(Token *tokens, int count);
Query *parse_insert(Token *tokens, int count);
Query *parse_create_table(Token *tokens, int count);
Query *parse_create_database(Token *tokens, int count);
Query *parse_update(Token *tokens, int count);
Query *parse_delete(Token *tokens, int count);
Query *parse_drop(Token *tokens, int count);

#endif // PARSER_H
