// src/laksaSQL.c

#include <string.h>
#include <strings.h>  // for strcasecmp
#include "laksaSQL.h"

const char *SQL_KEYWORDS[] = {
    "SELECT", "FROM", "WHERE", "INSERT", "INTO", "VALUES",
    "CREATE", "TABLE", "DATABASE", "UPDATE", "SET", "DELETE",
    "DROP", "USE", "ORDER", "BY", "LIMIT", "JOIN", "LEFT",
    "RIGHT", "INNER", "OUTER", "GROUP", "HAVING", "COUNT",
    "SUM", "AVG", "MIN", "MAX", "DISTINCT", "AS", "AND", "OR",
    "NOT", "NULL", "IS", "IN", "BETWEEN", "LIKE", "ALTER",
    "ADD", "COLUMN", "EXIT", "UNION", "EXISTS", "ALL",
    "ANY", "CASE", "WHEN", "THEN", "ELSE", "END", "ASC",
    "DESC", "CAST", "CONVERT", "DEFAULT", "PRIMARY", "KEY",
    "FOREIGN", "REFERENCES", "CHECK", "INDEX", "VIEW",
    "TRIGGER", "NOW", "DATEDIFF", "IF", "BEGIN", "END"
};

const int SQL_KEYWORDS_COUNT = sizeof(SQL_KEYWORDS) / sizeof(SQL_KEYWORDS[0]);

int is_sql_keyword(const char *text) {
    for (int i = 0; i < SQL_KEYWORDS_COUNT; i++) {
        if (strcasecmp(text, SQL_KEYWORDS[i]) == 0) return 1;
    }
    return 0;
}
