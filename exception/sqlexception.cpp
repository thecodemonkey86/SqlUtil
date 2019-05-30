#include "sqlexception.h"



QString SqlUtil3::SqlException::getQuery() const
{
    return query;
}

void SqlUtil3::SqlException::setQuery(const QString &value)
{
    query = value;
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


SqlUtil3::SqlException::~SqlException()
{

}



const QString & SqlUtil3::SqlException::getErrorCode()
{
    return errorCode;
}

