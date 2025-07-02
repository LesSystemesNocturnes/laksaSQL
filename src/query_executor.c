// query_executor.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_executor.h"

// 🟦 Exécution de SELECT avec support pour WHERE, ORDER BY, LIMIT
void execute_select(Query *query, Table *table) {
    if (!query || !table) {
        printf("[-] Erreur : requête ou table invalide.\n");
        return;
    }

    int filtered_count = 0;
    Row *filtered = malloc(sizeof(Row) * table->row_count);

    for (int i = 0; i < table->row_count; i++) {
        if (!query->where_clause || evaluate_where(query->where_clause, &table->rows[i], table)) {
            filtered[filtered_count++] = table->rows[i];
        }
    }

    if (query->order_by_column) {
        int col_index = get_column_index(table, query->order_by_column);
        if (col_index >= 0) {
            for (int i = 0; i < filtered_count - 1; i++) {
                for (int j = 0; j < filtered_count - i - 1; j++) {
                    if (strcmp(filtered[j].values[col_index], filtered[j + 1].values[col_index]) > 0) {
                        Row tmp = filtered[j];
                        filtered[j] = filtered[j + 1];
                        filtered[j + 1] = tmp;
                    }
                }
            }
        }
    }

    int limit = (query->limit > 0) ? query->limit : filtered_count;
    for (int i = 0; i < limit && i < filtered_count; i++) {
        print_row(&filtered[i], table);
    }

    free(filtered);
}
