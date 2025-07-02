// query.h

#ifndef QUERY_H
#define QUERY_H

#include "where.h"

typedef struct Query {
    char *table_name;
    int select_all;
    char *order_by_column;
    int limit;
    WhereClause *where_clause;

    int insert_values_start;
    int insert_values_count;

    char *update_column;
    char *update_value;

    int create_columns_start;
    int create_columns_count;
} Query;

#endif // QUERY_H
