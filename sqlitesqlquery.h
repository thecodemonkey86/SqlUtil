#ifndef SQLITESQLQUERY_H
#define SQLITESQLQUERY_H

#include "sqlquery.h"
namespace SqlUtil4 {
class SQLUTIL4SHARED_EXPORT SqliteSqlQuery : public SqlQuery
{
public:
    SqliteSqlQuery();
    ~SqliteSqlQuery() = default;
    virtual QString toString();
};

}

#endif // SQLITESQLQUERY_H
