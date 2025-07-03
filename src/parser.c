// parser.c — Analyseur syntaxique SQL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "laksaSQL.h"

// 🟩 Fonction principale de parsing des requêtes
Query *parse_query(Token *tokens, int count) {
    if (count == 0) return NULL;

    Query *q = calloc(1, sizeof(Query));

    if (strcmp(tokens[0].text, "CREATE") == 0 && strcmp(tokens[1].text, "DATABASE") == 0) {
        q->type = QUERY_CREATE_DATABASE;
        q->table_name = strdup(tokens[2].text);
    } else if (strcmp(tokens[0].text, "CREATE") == 0 && strcmp(tokens[1].text, "TABLE") == 0) {
        q->type = QUERY_CREATE_TABLE;
        q->table_name = strdup(tokens[2].text);
        q->create_columns_start = 3;
        q->create_columns_count = count - 3;
    } else if (strcmp(tokens[0].text, "INSERT") == 0 && strcmp(tokens[1].text, "INTO") == 0) {
        q->type = QUERY_INSERT;
        q->table_name = strdup(tokens[2].text);
        q->insert_values_start = 4;
        q->insert_values_count = count - 4;
    } else if (strcmp(tokens[0].text, "SELECT") == 0) {
        q->type = QUERY_SELECT;
        if (strcmp(tokens[1].text, "*") == 0) {
            q->select_all = 1;
        } else if (strcmp(tokens[2].text, "(") == 0 && strcmp(tokens[4].text, ")") == 0) {
            q->select_function = strdup(tokens[1].text);
            q->select_column = strdup(tokens[3].text);
        } else {
            q->select_column = strdup(tokens[1].text);
        }
        q->table_name = strdup(tokens[3].text);
    } else if (strcmp(tokens[0].text, "UPDATE") == 0) {
        q->type = QUERY_UPDATE;
        q->table_name = strdup(tokens[1].text);
        q->update_column = strdup(tokens[3].text);
        q->update_value = strdup(tokens[5].text);
    } else if (strcmp(tokens[0].text, "DELETE") == 0 && strcmp(tokens[1].text, "FROM") == 0) {
        q->type = QUERY_DELETE;
        q->table_name = strdup(tokens[2].text);
    } else if (strcmp(tokens[0].text, "DROP") == 0 && strcmp(tokens[1].text, "TABLE") == 0) {
        q->type = QUERY_DROP;
        q->table_name = strdup(tokens[2].text);
    } else if (strcmp(tokens[0].text, "ALTER") == 0 && strcmp(tokens[1].text, "TABLE") == 0) {
        q->type = QUERY_ALTER_TABLE;
        q->table_name = strdup(tokens[2].text);

        if (strcmp(tokens[3].text, "ADD") == 0) {
            q->alter_action = ALTER_ADD;
            q->alter_column_name = strdup(tokens[4].text);
            q->alter_column_type = strdup(tokens[5].text);
        } else if (strcmp(tokens[3].text, "DROP") == 0) {
            q->alter_action = ALTER_DROP;
            q->alter_column_name = strdup(tokens[4].text);
        } else if (strcmp(tokens[3].text, "RENAME") == 0 && strcmp(tokens[4].text, "TO") == 0) {
            q->alter_action = ALTER_RENAME;
            q->alter_column_name = strdup(tokens[5].text); // réutilisé pour le nouveau nom de table
        } else {
            q->alter_action = ALTER_UNKNOWN;
        }
    } else {
        free(q);
        return NULL;
    }

    return q;
}

// parse_select — Alias pour parse_query
Query *parse_select(Token *tokens, int count) {
    return parse_query(tokens, count);
}
