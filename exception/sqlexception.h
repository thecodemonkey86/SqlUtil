#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include "exception/qtexception.h"
#include "sqlutil3_global.h"


namespace SqlUtil3 {
class SQLUTIL3SHARED_EXPORT SqlException : public QtCommon2::QtException
{
private: QString errorCode;
private: QString query;
public:
    SqlException(const QString & errorCode, const QString&error,const QString&query);
    SqlException(const QString & errorCode, const QString&error) ;
    virtual ~SqlException();
    const QString & getErrorCode();
    QString getQuery() const;
    void setQuery(const QString &value);
};
}
#endif // SQLEXCEPTION_H
