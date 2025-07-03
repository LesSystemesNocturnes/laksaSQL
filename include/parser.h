#pragma once
#include "query.h"
#include "tokenizer.h"

Query *parse_select(Token *tokens, int count);
Query *parse_insert(Token *tokens, int count);
Query *parse_create_table(Token *tokens, int count);
Query *parse_create_database(Token *tokens, int count);
Query *parse_update(Token *tokens, int count);
Query *parse_delete(Token *tokens, int count);
Query *parse_drop(Token *tokens, int count);
// parser.h
Query *parse_select(Token *tokens, int count);

