#ifndef PGSQLQUERY_H
#define PGSQLQUERY_H

#include "sqlquery.h"
namespace SqlUtil3 {
class SQLUTIL3SHARED_EXPORT PgSqlQuery : public SqlQuery
{
public:
    PgSqlQuery(const QSqlDatabase & sqlCon);
    ~PgSqlQuery() = default;
    virtual QString toString();
};

}

#endif // PGSQLQUERY_H
