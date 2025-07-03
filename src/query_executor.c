// query_executor.c — Exécute les requêtes SQL avec fonctions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_executor.h"

void execute_query(Query *query) {
    switch (query->type) {
        case QUERY_SELECT:
            printf("[+] SELECT query on table '%s'\n", query->table_name);
            if (query->select_function) {
                if (strcmp(query->select_function, "COUNT") == 0) {
                    printf("→ COUNT(%s)\n", query->select_column);
                    printf("Résultat: 10\n"); // ⚠️ Placeholder
                } else if (strcmp(query->select_function, "SUM") == 0) {
                    printf("→ SUM(%s)\n", query->select_column);
                    printf("Résultat: 247\n"); // ⚠️ Placeholder
                } else {
                    printf("[-] Fonction '%s' non prise en charge.\n", query->select_function);
                }
            } else if (query->select_all) {
                printf("→ Affichage de toutes les colonnes.\n");
            } else {
                printf("→ Colonne sélectionnée: %s\n", query->select_column);
            }
            break;
        default:
            printf("[-] Ce type de requête n’est pas encore pris en charge ici.\n");
            break;
    }
}
