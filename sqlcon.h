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
  static QSqlDatabase connectMySql(const QString & host, const QString & user, const QString & pass, const QString & dbname,const QString&conName=QLatin1String("qt_sql_default_connection"), int port = 3306);

    static Q_DECL_DEPRECATED QSqlDatabase connectFirebird(const QString & host, const QString & user, const QString & pass, const QString & dbFile, int port);
    static QSqlDatabase connectIbase(const QString & host, const QString & user, const QString & pass, const QString & dbFile, int port);
    static QSqlDatabase connectIbase(const QString & host, const QString & user, const QString & pass, const QString & dbFile, const QString&conName, int port);
    static QSqlDatabase connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname, int port=5432);
    static QSqlDatabase connectPg(const QString& host, const QString& user, const QString& pass, const QString& dbname, const QString&conName, int port=5432);
    static QSqlDatabase connectPg(const QString& host, const QString& user, const QString& pass, int port=5432);
    static QSqlDatabase connectSqlite(const QString &dbFile);
    static QSqlDatabase connectSqlite(const QString &dbFile, const QString &connectionName);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QList<QVariant> &params);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, int64_t param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, int param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, double param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, bool param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, float param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QString &param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QVariant &param);
    static void execute(const QSqlDatabase & sqlCon, const QString &sqlQuery);

    static QSqlQuery query(const QSqlDatabase & sqlCon,const QString& sql, const QVariant&);
    static QSqlQuery query(const QSqlDatabase & sqlCon,const QString& sql);
    static QSqlQuery query(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QList<QVariant>&  params) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QVector<int64_t>&  params) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QSet<int64_t>&  params) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QList<QPair<QString,QVariant>>&  params) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QVariant&param) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql, const QString&param) ;
    static QSqlRecord fetchRow(const QSqlDatabase & sqlCon, const QString& sql) ;
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql, const QVariant & param);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql, const QString & param);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql,  const QList<QPair<QString,QVariant>>&  params);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql,  const QVector<int64_t>&  params);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString& sql,  const QSet<int64_t>&  params);
    static int fetchInt(const QSqlDatabase & sqlCon,const QString &sql);
    static int64_t fetchInt64(const QSqlDatabase & sqlCon,const QString &sql);
    static int64_t fetchInt64(const QSqlDatabase & sqlCon,const QString &sql, const QVariantList & params);
    static QString fetchString(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static QString fetchString(const QSqlDatabase & sqlCon,const QString& sql, const QVariant&  param);
    static QString fetchString(const QSqlDatabase & sqlCon,const QString& sql);
    static int64_t insert(const QSqlDatabase & sqlCon,const QString& sql, const QList<QVariant>&  params);
    static QString getDebugString(const QString & sql, const QList<QVariant> & params);
    static QString getDebugString(const QString &sql, QList<QPair<QString, QVariant> > params);
    static void beginTransaction(const QSqlDatabase & sqlCon);
    static void commitTransaction(const QSqlDatabase & sqlCon);
    static void rollbackTransaction(const QSqlDatabase & sqlCon);




};
}



#endif // SQL_H
