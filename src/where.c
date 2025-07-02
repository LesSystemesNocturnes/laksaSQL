// where.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "where.h"

// 🟦 Évalue si la ligne satisfait la clause WHERE
int evaluate_where(WhereClause *clause, Row *row, Table *table) {
    if (!clause) return 1;
    int col_index = get_column_index(table, clause->column);
    if (col_index < 0) return 0;
    return strcmp(row->values[col_index], clause->value) == 0;
}

// 🟦 Parse une clause WHERE de type simple: colonne = valeur
WhereClause *parse_where_clause(Token *tokens, int count) {
    if (count < 4) return NULL;
    WhereClause *clause = malloc(sizeof(WhereClause));
    clause->column = strdup(tokens[1].text);
    clause->value = strdup(tokens[3].text);
    return clause;
}
