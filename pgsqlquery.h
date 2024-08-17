#pragma once


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

