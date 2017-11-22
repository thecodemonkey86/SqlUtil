#ifndef SQL_H
#define SQL_H

#include "sqlutil3_global.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include "exception/sqlexception.h"

namespace SqlUtil3 {
class SQLUTIL3SHARED_EXPORT Sql
{

private:
    Sql();
    ~Sql();


public:
    static QSqlDatabase connectMySql(const QString & host, const QString & user, const QString & pass, const QString & dbname, int port = 3306);
};
}



#endif // SQL_H
