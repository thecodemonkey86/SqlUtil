#pragma once

#include "sqlquery.h"
namespace SqlUtil4 {
  class SQLUTIL4SHARED_EXPORT FirebirdSqlQuery : public SqlQuery
  {
  public:
    FirebirdSqlQuery();

    // SqlQuery interface
  public:
    virtual QString toString() override;
  };
}


