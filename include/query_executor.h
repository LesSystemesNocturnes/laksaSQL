// query_executor.h

#ifndef QUERY_EXECUTOR_H
#define QUERY_EXECUTOR_H

#include "query.h"
#include "table.h"

// 🟦 Exécute une requête SELECT
void execute_select(Query *query, Table *table);

#endif // QUERY_EXECUTOR_H
