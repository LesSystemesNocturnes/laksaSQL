// include/laksaSQL.h

#ifndef LAKSASQL_H
#define LAKSASQL_H

extern const char *SQL_KEYWORDS[];
extern const int SQL_KEYWORDS_COUNT;

int is_sql_keyword(const char *text);

#endif
