#ifndef PGSQLQUERY_H
#define PGSQLQUERY_H

#include "sqlquery.h"
namespace SqlUtil4 {
class SQLUTIL4SHARED_EXPORT PgSqlQuery : public SqlQuery
{
public:
    PgSqlQuery();
    ~PgSqlQuery() = default;
    virtual QString toString();
};

}

#endif // PGSQLQUERY_H
