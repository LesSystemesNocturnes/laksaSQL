// table.h

#ifndef TABLE_H
#define TABLE_H

#define MAX_COLUMNS 16
#define MAX_ROWS 1024

// 🟦 Ajout de déclarations anticipées pour résoudre l'ordre de compilation
typedef struct Query Query;
#include "tokenizer.h"

typedef struct {
    char *name;
    char *type;
} Column;

typedef struct {
    char *values[MAX_COLUMNS];
} Row;

typedef struct {
    char *name;
    int column_count;
    Column columns[MAX_COLUMNS];
    Row rows[MAX_ROWS];
    int row_count;
} Table;

// 🟦 Fonctions reliées à la gestion des tables
Table *load_table(const char *name);
void save_table(Table *table);
void create_table(const char *name, Token *tokens, int count);
void drop_table(const char *name);
int get_column_index(Table *table, const char *col_name);
void print_row(Row *row, Table *table);
void insert_into_table(Table *table, Token *tokens, int count);
void update_table(Table *table, Query *query);
void delete_from_table(Table *table, Query *query);

#endif // TABLE_H
