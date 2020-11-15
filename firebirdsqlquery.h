#ifndef FIREBIRDSQLQUERY_H
#define FIREBIRDSQLQUERY_H
#include "sqlquery.h"
namespace SqlUtil3 {
  class SQLUTIL3SHARED_EXPORT FirebirdSqlQuery : public SqlQuery
  {
  public:
    FirebirdSqlQuery();

    // SqlQuery interface
  public:
    virtual QString toString() override;
  };
}


#endif // FIREBIRDSQLQUERY_H
