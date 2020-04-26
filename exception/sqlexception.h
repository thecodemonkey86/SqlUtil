#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include "exception/qtexception.h"
#include "sqlutil3_global.h"
#define throwSqlExceptionWithLine(errorCode,error,query) throw SqlUtil3::SqlException(errorCode,error,query, __FILE__, __LINE__)

namespace SqlUtil3 {
class SQLUTIL3SHARED_EXPORT SqlException : public QtCommon2::QtException
{
private: QString errorCode;
private: QString query;
public:
    SqlException(const QString & errorCode, const QString&error,const QString&query,const QString&file, int line);
    SqlException(const QString & errorCode, const QString&error,const QString&query);
    SqlException(const QString & errorCode, const QString&error) ;
    const QString & getErrorCode();
    QString getQuery() const;
    void setQuery(const QString &value);
    virtual QString getLogString() const override;
};
}
#endif // SQLEXCEPTION_H
