#include "sqlcon.h"


SqlUtil3::Sql::Sql()
{
}

SqlUtil3::Sql::~Sql()
{

}

QSqlDatabase SqlUtil3::Sql::connectMySql(const QString &host, const QString &user, const QString &pass, const QString &dbname, int port)
{
    QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"));
        con.setHostName(host);
        con.setDatabaseName(dbname);
        con.setUserName(user);
        con.setPassword(pass);
        con.setPort(port);
        if(con.open()) {
            return con;
        } else {
            throw SqlException(con.lastError().nativeErrorCode(),
                               con.driver()->lastError().text());
        }
}
