// query.h — extended to support ALTER TABLE

#ifndef QUERY_H
#define QUERY_H

#include "where.h"

typedef enum {
    QUERY_SELECT,
    QUERY_INSERT,
    QUERY_CREATE_TABLE,
    QUERY_CREATE_DATABASE,
    QUERY_UPDATE,
    QUERY_DELETE,
    QUERY_DROP,
    QUERY_ALTER_TABLE
} QueryType;

typedef enum {
    ALTER_ADD,
    ALTER_DROP,
    ALTER_RENAME,
    ALTER_UNKNOWN
} AlterAction;

typedef struct Query {
    QueryType type;
    char *table_name;

    // SELECT
    int select_all;
    char *select_function;
    char *select_column;
    char *order_by_column;
    int limit;

    // INSERT
    int insert_values_start;
    int insert_values_count;

    // CREATE TABLE
    int create_columns_start;
    int create_columns_count;

    // UPDATE
    char *update_column;
    char *update_value;

    // WHERE
    WhereClause *where_clause;

    // ALTER TABLE
    AlterAction alter_action;
    char *alter_column_name;
    char *alter_column_type;

} Query;

#endif
