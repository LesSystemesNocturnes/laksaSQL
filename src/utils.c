// utils.c

#include <string.h>
#include "utils.h"

// 🟦 Supprime les sauts de ligne d'une chaîne
void trim_newline(char *str) {
    char *p = strchr(str, '\n');
    if (p) *p = '\0';
}
