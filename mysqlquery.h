#pragma once

#include "sqlquery.h"
namespace SqlUtil4 {
class SQLUTIL4SHARED_EXPORT MySqlQuery : public SqlQuery
{
public:
    MySqlQuery();
    ~MySqlQuery() = default;
    virtual QString toString();
};

}

