#include "sqlexception.h"



QString SqlUtil3::SqlException::getQuery() const
{
    return query;
}

void SqlUtil3::SqlException::setQuery(const QString &value)
{
    query = value;
}

QString SqlUtil3::SqlException::getLogString() const
{
    if(line>0) {
      return QStringLiteral("query: %1, message: %2, file: %3 in line %4").arg(query, msg,file,QString::number(line));
    }
    return msg;
}

SqlUtil3::SqlException::SqlException(const QString &errorCode, const QString &error,
                                     const QString &query, const QString & sourcefile, int sourceline)
 : QtException(error,sourcefile,sourceline)
{
    this->errorCode= errorCode;
    this->query = query;
}

SqlUtil3::SqlException::SqlException(const QString & errorCode,const QString&error,const QString&query) : QtException(error)
{
    this->errorCode= errorCode;
    this->query = query;
}

SqlUtil3::SqlException::SqlException(const QString & errorCode, const QString &error) : QtException(error)
{
     this->errorCode= errorCode;
}


const QString & SqlUtil3::SqlException::getErrorCode()
{
    return errorCode;
}

