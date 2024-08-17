#pragma once


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

