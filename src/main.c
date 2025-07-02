// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "query_executor.h"
#include "table.h"
#include "file.h"

// 🟦 Fonction principale — point d’entrée de LaksaSQL
int main(int argc, char *argv[]) {
    printf("Welcome\n");
    printf("Enter SQL commands. Type EXIT to quit.\n\n");

    char input[2048];

    while (1) {
        printf("laksaSQL> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        if (strncmp(input, "exit;", 5) == 0) {
            printf("Thank you. Goodbye.\n");
            break;
        }

        int token_count = 0;
        Token *tokens = tokenize(input, &token_count);
        if (!tokens || token_count == 0) {
            printf("[-] Error. Invalid command.\n");
            continue;
        }

        char *cmd = tokens[0].text;

        if (strcmp(cmd, "SELECT") == 0) {
            Query *q = parse_select(tokens, token_count);
            Table *t = load_table(q->table_name);
            if (t) execute_select(q, t);
        }
        else if (strcmp(cmd, "INSERT") == 0) {
            Query *q = parse_insert(tokens, token_count);
            Table *t = load_table(q->table_name);
            if (t) insert_into_table(t, tokens + q->insert_values_start, q->insert_values_count);
        }
        else if (strcmp(cmd, "CREATE") == 0 && strcmp(tokens[1].text, "TABLE") == 0) {
            Query *q = parse_create_table(tokens, token_count);
            create_table(q->table_name, tokens + q->create_columns_start, q->create_columns_count);
        }
        else if (strcmp(cmd, "CREATE") == 0 && strcmp(tokens[1].text, "DATABASE") == 0) {
            Query *q = parse_create_database(tokens, token_count);
            create_database(q->table_name);
        }
        else if (strcmp(cmd, "UPDATE") == 0) {
            Query *q = parse_update(tokens, token_count);
            Table *t = load_table(q->table_name);
            if (t) update_table(t, q);
        }
        else if (strcmp(cmd, "DELETE") == 0) {
            Query *q = parse_delete(tokens, token_count);
            Table *t = load_table(q->table_name);
            if (t) delete_from_table(t, q);
        }
        else if (strcmp(cmd, "DROP") == 0) {
            Query *q = parse_drop(tokens, token_count);
            if (strcmp(tokens[1].text, "TABLE") == 0) drop_table(q->table_name);
            else if (strcmp(tokens[1].text, "DATABASE") == 0) drop_database(q->table_name);
        }
        
        // 🟦 Commande spéciale : LOAD 'filename.sql';
        
        // 🟦 Commande spéciale : quitter LaksaSQL
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "EXIT") == 0 ||
            strcmp(cmd, "quit") == 0 || strcmp(cmd, "QUIT") == 0) {
            printf("[+] Exiting LaksaSQL. Goodbye!\n");
            free_tokens(tokens, token_count);
            break;
        }

        if (strcmp(cmd, "LOAD") == 0 && token_count >= 2) {
            char *filename = tokens[1].text;
            if (filename[0] == '\'' || filename[0] == '"') filename++;
            char *end = strrchr(filename, '\'');
            if (!end) end = strrchr(filename, '"');
            if (end) *end = '\0';

            FILE *fp = fopen(filename, "r");
            if (!fp) {
                printf("[-] Failed to open file: %s\n", filename);
            } else {
                char line[2048];
                while (fgets(line, sizeof(line), fp)) {
                    int sub_count = 0;
                    Token *sub_tokens = tokenize(line, &sub_count);
                    if (!sub_tokens || sub_count == 0) continue;

                    char *sub_cmd = sub_tokens[0].text;

                    if (strcmp(sub_cmd, "SELECT") == 0) {
                        Query *q = parse_select(sub_tokens, sub_count);
                        Table *t = load_table(q->table_name);
                        if (t) execute_select(q, t);
                    } else if (strcmp(sub_cmd, "INSERT") == 0) {
                        Query *q = parse_insert(sub_tokens, sub_count);
                        Table *t = load_table(q->table_name);
                        if (t) insert_into_table(t, sub_tokens + q->insert_values_start, q->insert_values_count);
                    } else if (strcmp(sub_cmd, "CREATE") == 0 && strcmp(sub_tokens[1].text, "TABLE") == 0) {
                        Query *q = parse_create_table(sub_tokens, sub_count);
                        create_table(q->table_name, sub_tokens + q->create_columns_start, q->create_columns_count);
                    } else if (strcmp(sub_cmd, "CREATE") == 0 && strcmp(sub_tokens[1].text, "DATABASE") == 0) {
                        Query *q = parse_create_database(sub_tokens, sub_count);
                        create_database(q->table_name);
                    } else if (strcmp(sub_cmd, "UPDATE") == 0) {
                        Query *q = parse_update(sub_tokens, sub_count);
                        Table *t = load_table(q->table_name);
                        if (t) update_table(t, q);
                    } else if (strcmp(sub_cmd, "DELETE") == 0) {
                        Query *q = parse_delete(sub_tokens, sub_count);
                        Table *t = load_table(q->table_name);
                        if (t) delete_from_table(t, q);
                    } else if (strcmp(sub_cmd, "DROP") == 0) {
                        Query *q = parse_drop(sub_tokens, sub_count);
                        if (strcmp(sub_tokens[1].text, "TABLE") == 0) drop_table(q->table_name);
                        else if (strcmp(sub_tokens[1].text, "DATABASE") == 0) drop_database(q->table_name);
                    }

                    free_tokens(sub_tokens, sub_count);
                }
                fclose(fp);
            }
            free_tokens(tokens, token_count);
            continue;
        }
    
        else {
            printf("[-] Commande inconnue : %s\n", cmd);
        }

        free_tokens(tokens, token_count);
    }

    return 0;
}
