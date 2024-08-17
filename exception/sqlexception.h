#pragma once


#include "exception/qtexception.h"
#include "sqlutil4_global.h"
#define throwSqlExceptionWithLine(errorCode,error,query) throw SqlUtil4::SqlException(errorCode,error,query, __FILE__, __LINE__)

namespace SqlUtil4 {
class SQLUTIL4SHARED_EXPORT SqlException : public QtCommon2::QtException
{
private: QString errorCode;
private: QString query;
public:
    SqlException(const QString & errorCode, const QString&error,const QString&query,const QString&file, int line);
    SqlException(const QString & errorCode, const QString&error,const QString&query);
    SqlException(const QString & errorCode, const QString&error) ;
    virtual ~SqlException()=default;
    const QString & getErrorCode();
    QString getQuery() const;
    void setQuery(const QString &value);
    virtual QString getLogString() const override;
};
}
