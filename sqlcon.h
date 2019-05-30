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
    Sql() = default;
    Sql(const Sql& ) = default;
    ~Sql() = default;


public:
    static QSqlDatabase connectMySql(const QString & host, const QString & user, const QString & pass, const QString & dbname, int port = 3306);
    static QSqlDatabase connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname, int port=5432);
    static QSqlDatabase connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname, const QString&conName, int port=5432);
    static QSqlDatabase connectPg(const QString& host, const QString& user, const QString& pass, int port=5432);

    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QList<QVariant> &params);

    static QSqlQuery query(const QSqlDatabase & sqlCon,const QString& sql, const QVariant&);
    static QSqlQuery query(const QSqlDatabase & sqlCon,const QString& sql);
    static QSqlQuery query(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QList<QVariant>&  params) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QList<QPair<QString,QVariant>>&  params) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QVariant&param) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QString&param) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql) ;
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql, const QVariant & param);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql, const QString & param);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql,  const QList<QPair<QString,QVariant>>&  params);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString &sql);
    static QString fetchString(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static QString fetchString(const QSqlDatabase & sqlCon,const QString& sql, const QVariant&  param);
    static QString fetchString(const QSqlDatabase & sqlCon,const QString& sql);
    static int insert(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static QString getDebugString(const QString & sql, const QList<QVariant> & params);

};
}



#endif // SQL_H
