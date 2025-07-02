// where.h

#ifndef WHERE_H
#define WHERE_H

#include "table.h"
#include "tokenizer.h"

typedef struct {
    char *column;
    char *value;
} WhereClause;

int evaluate_where(WhereClause *clause, Row *row, Table *table);
WhereClause *parse_where_clause(Token *tokens, int count);

#endif // WHERE_H
