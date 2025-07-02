// file.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// 🟦 Crée un répertoire pour une base de données
void create_database(const char *name) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mkdir -p data/%s", name);
    system(cmd);
    printf("[+] Base de données '%s' créée.\n", name);
}

// 🟦 Supprime un répertoire de base de données
void drop_database(const char *name) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "rm -rf data/%s", name);
    system(cmd);
    printf("[-] Base de données '%s' supprimée.\n", name);
}
