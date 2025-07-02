// table.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "query.h"
#include "where.h"

// 🟦 Charge une table à partir du fichier .ldb
Table *load_table(const char *name) {
    char path[256];
    snprintf(path, sizeof(path), "data/%s.ldb", name);

    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    Table *t = malloc(sizeof(Table));
    fread(t, sizeof(Table), 1, f);
    fclose(f);
    return t;
}

// 🟦 Sauvegarde une table dans un fichier .ldb
void save_table(Table *table) {
    char path[256];
    snprintf(path, sizeof(path), "data/%s.ldb", table->name);

    FILE *f = fopen(path, "wb");
    if (!f) return;
    fwrite(table, sizeof(Table), 1, f);
    fclose(f);
}

// 🟦 Création d’une table avec colonnes
void create_table(const char *name, Token *tokens, int count) {
    Table *t = calloc(1, sizeof(Table));
    t->name = strdup(name);
    t->column_count = count / 2;
    for (int i = 0, j = 0; j < count && i < MAX_COLUMNS; j += 2, i++) {
        t->columns[i].name = strdup(tokens[j].text);
        t->columns[i].type = strdup(tokens[j + 1].text);
    }
    save_table(t);
    free(t);
    printf("[+] Table '%s' créée avec succès.\n", name);
}

// 🟦 Suppression d’une table
void drop_table(const char *name) {
    char path[256];
    snprintf(path, sizeof(path), "data/%s.ldb", name);
    remove(path);
    printf("[-] Table '%s' supprimée.\n", name);
}

// 🟦 Trouver l’indice d’une colonne
int get_column_index(Table *table, const char *col_name) {
    for (int i = 0; i < table->column_count; i++) {
        if (strcmp(table->columns[i].name, col_name) == 0) return i;
    }
    return -1;
}

// 🟦 Affiche une ligne
void print_row(Row *row, Table *table) {
    for (int i = 0; i < table->column_count; i++) {
        printf("%s", row->values[i]);
        if (i < table->column_count - 1) printf(" | ");
    }
    printf("\n");
}

// 🟦 Insertion dans la table
void insert_into_table(Table *table, Token *tokens, int count) {
    Row *row = &table->rows[table->row_count];
    for (int i = 0; i < table->column_count && i < count; i++) {
        row->values[i] = strdup(tokens[i].text);
    }
    table->row_count++;
    save_table(table);
    printf("[+] Données insérées.\n");
}

// 🟦 Mise à jour des données
void update_table(Table *table, Query *query) {
    int col_index = get_column_index(table, query->update_column);
    if (col_index < 0) return;

    for (int i = 0; i < table->row_count; i++) {
        if (evaluate_where(query->where_clause, &table->rows[i], table)) {
            free(table->rows[i].values[col_index]);
            table->rows[i].values[col_index] = strdup(query->update_value);
        }
    }
    save_table(table);
    printf("[~] Données mises à jour.\n");
}

// 🟦 Suppression de lignes
void delete_from_table(Table *table, Query *query) {
    int new_count = 0;
    for (int i = 0; i < table->row_count; i++) {
        if (!evaluate_where(query->where_clause, &table->rows[i], table)) {
            table->rows[new_count++] = table->rows[i];
        }
    }
    table->row_count = new_count;
    save_table(table);
    printf("[-] Données supprimées.\n");
}
