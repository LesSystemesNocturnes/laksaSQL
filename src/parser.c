// parser.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "query.h"
#include "where.h"

// 🟦 Analyse la requête SELECT
Query *parse_select(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    int i = 1;

    if (strcmp(tokens[i].text, "*") == 0) {
        q->select_all = 1;
        i++;
    }

    if (i >= count || strcmp(tokens[i].text, "FROM") != 0) return NULL;
    i++;

    q->table_name = strdup(tokens[i++].text);

    while (i < count) {
        if (strcmp(tokens[i].text, "WHERE") == 0) {
            q->where_clause = parse_where_clause(tokens + i, count - i);
            i += 3;
        } else if (strcmp(tokens[i].text, "ORDER") == 0 && i+2 < count && strcmp(tokens[i+1].text, "BY") == 0) {
            q->order_by_column = strdup(tokens[i+2].text);
            i += 3;
        } else if (strcmp(tokens[i].text, "LIMIT") == 0 && i+1 < count) {
            q->limit = atoi(tokens[i+1].text);
            i += 2;
        } else {
            i++;
        }
    }

    return q;
}

// 🟦 Analyse INSERT INTO
Query *parse_insert(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    q->table_name = strdup(tokens[2].text);
    q->insert_values_start = 4;
    q->insert_values_count = count - 4;
    return q;
}

// 🟦 Analyse CREATE TABLE
Query *parse_create_table(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    q->table_name = strdup(tokens[2].text);
    q->create_columns_start = 3;
    q->create_columns_count = count - 3;
    return q;
}

// 🟦 Analyse CREATE DATABASE
Query *parse_create_database(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    q->table_name = strdup(tokens[2].text);
    return q;
}

// 🟦 Analyse UPDATE
Query *parse_update(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    q->table_name = strdup(tokens[1].text);
    q->update_column = strdup(tokens[3].text);
    q->update_value = strdup(tokens[5].text);
    return q;
}

// 🟦 Analyse DELETE
Query *parse_delete(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    q->table_name = strdup(tokens[2].text);
    if (count > 3 && strcmp(tokens[3].text, "WHERE") == 0) {
        q->where_clause = parse_where_clause(tokens + 3, count - 3);
    }
    return q;
}

// 🟦 Analyse DROP
Query *parse_drop(Token *tokens, int count) {
    Query *q = calloc(1, sizeof(Query));
    q->table_name = strdup(tokens[2].text);
    return q;
}
