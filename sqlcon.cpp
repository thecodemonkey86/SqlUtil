#include "sqlcon.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#ifdef QT_DEBUG
#include <QDebug>
#endif

using namespace SqlUtil3;

QSqlDatabase Sql::connectMySql(const QString &host, const QString &user, const QString &pass,const QString &dbname,const QString &conname , int port)
{
    QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QMYSQL"),conname);
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

QSqlDatabase Sql::connectFirebird(const QString &host, const QString &user, const QString &pass, const QString &dbFile, int port)
{
  QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("qtfirebird"));
  con.setDatabaseName(QStringLiteral("%1/%2:%3").arg(host, QString::number(port), dbFile));

  con.setConnectOptions("CHARSET=UNICODE_FSS");
  con.setUserName(user);
  con.setPassword(pass);

  if(con.open()) {
    return con;
  } else {
    throw SqlException(con.lastError().nativeErrorCode(),
                       con.driver()->lastError().text());
  }
}

QSqlDatabase Sql::connectPg(const QString & host, const QString & user, const QString & pass, int port) {
    QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    con.setHostName(host);
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


QSqlDatabase Sql::connectPg(const QString & host, const QString & user, const QString & pass, const QString & dbname, int port) {
    QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"));
    con.setHostName(host);
    con.setDatabaseName(dbname);
    con.setUserName(user);
    con.setPassword(pass);
    con.setPort(port);
    if(con.open()) {
        return con;
    } else {
        throw SqlException(con.lastError().nativeErrorCode(),con.driver()->lastError().text());
    }
}

QSqlDatabase Sql::connectPg(const QString & host, const QString & user, const QString & pass, const QString & dbname, const QString&conName, int port) {
    QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"),conName);
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

QSqlQuery Sql::query(const QSqlDatabase & sqlCon, const QString & sql, const QVariant & param) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(!q.exec()) {

            throw SqlException(sqlCon.lastError().nativeErrorCode(),
                               sqlCon.driver()->lastError().text(),sql);
        }
        return q;

    }


    throw SqlException(sqlCon.lastError().nativeErrorCode(),
                       sqlCon.driver()->lastError().text(),sql);
}
QSqlQuery Sql::query(const QSqlDatabase & sqlCon, const QString & sql) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        if(!q.exec()) {

            throw SqlException(sqlCon.lastError().nativeErrorCode(),
                               sqlCon.driver()->lastError().text(),sql);
        }
        return q;

    }


    throw SqlException(sqlCon.lastError().nativeErrorCode(),
                       sqlCon.driver()->lastError().text(),sql);
}

QSqlQuery Sql::query(const QSqlDatabase & sqlCon, const QString & sql, const QList<QVariant> & params) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
#ifdef QT_DEBUG
    qDebug().noquote() << "Error:"+ Sql::getDebugString(sql,params);
#endif
    if(q.prepare(sql)) {
        for(int i = 0; i < params.size(); i++) {
            q.addBindValue(params.at(i));

        }
        if(!q.exec()) {
            throw SqlException(sqlCon.lastError().nativeErrorCode(),
                               sqlCon.driver()->lastError().text(),sql);
        }
        return q;

    }
    throw SqlException(sqlCon.lastError().nativeErrorCode(),
                       sqlCon.driver()->lastError().text(),sql);
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QList<QVariant> &params) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    bool res = q.prepare(sqlQuery);
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }

    res = res & q.exec();


    if(!res) {
#ifdef QT_DEBUG
      qDebug().noquote() << "Error:"+ Sql::getDebugString(sqlQuery,params);
#endif
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           !sqlCon.lastError().text().isEmpty()? sqlCon.lastError().text():sqlCon.driver()->lastError().text(),sqlQuery);
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, int64_t param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           sqlCon.driver()->lastError().text());
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, int param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           sqlCon.driver()->lastError().text());
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QString& param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           sqlCon.driver()->lastError().text());
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, double param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           sqlCon.driver()->lastError().text());
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, bool param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           sqlCon.driver()->lastError().text());
    }
}


void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, float param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throw SqlException(sqlCon.lastError().nativeErrorCode(),
                           sqlCon.driver()->lastError().text());
    }
}


QSqlRecord Sql::fetchRow(const QSqlDatabase & sqlCon, const QString & sql, const QVariant & param) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

    throw SqlException(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
}

QSqlRecord Sql::fetchRow(const QSqlDatabase & sqlCon, const QString &sql, const QString &param)
{
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        q.addBindValue(param);
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

   throw SqlException(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
}

QSqlRecord Sql::fetchRow(const QSqlDatabase & sqlCon, const QString & sql) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql) &&  q.exec() && q.next()) {
        return q.record();
    }

     throw SqlException(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
}


QSqlRecord Sql::fetchRow(const QSqlDatabase & sqlCon, const QString & sql, const QList<QVariant> & params) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {

        for(int i = 0; i < params.size(); i++) {
            q.addBindValue(params.at(i));

        }
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

   throw SqlException(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
}

QSqlRecord Sql::fetchRow(const QSqlDatabase & sqlCon, const QString &sql, const QList<QPair<QString, QVariant> > &params)
{
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {

        for(int i = 0; i < params.size(); i++) {
            q.bindValue(QStringLiteral(":%1").arg(params[i].first),params[i].second);

        }
        if(q.exec()) {

            if(q.next()) {
                return q.record();
            }
        }

    }

    throw SqlException(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString &sql, const QVariant &param)
{
    bool ok;
    int val = fetchRow(sqlCon,sql, param).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException("", "Invalid query",sql);
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString &sql, const QString &param)
{
    bool ok;
    int val = fetchRow(sqlCon,sql, param).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException("", "Invalid query",sql);
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString & sql, const QList<QVariant> & params){
    bool ok;
    int val = fetchRow(sqlCon, sql, params).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException("", "Invalid query",sql);
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString &sql, const QList<QPair<QString, QVariant> > &params)
{
    bool ok;
    int val = fetchRow(sqlCon,sql, params).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException("", "Invalid query",sql);
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString & sql){
    bool ok;
    int val = fetchRow(sqlCon,sql).value(0).toInt(&ok);
    if(!ok) {
        throw SqlException("", "Invalid query",sql);
    }
    return val;
}

QString Sql::fetchString(const QSqlDatabase & sqlCon, const QString &sql, const QList<QVariant> &params)
{
    return fetchRow(sqlCon,sql, params).value(0).toString();
}

QString Sql::fetchString(const QSqlDatabase & sqlCon, const QString &sql, const QVariant &param)
{
    return fetchRow(sqlCon,sql, param).value(0).toString();
}

QString Sql::fetchString(const QSqlDatabase & sqlCon, const QString &sql)
{
    return fetchRow(sqlCon,sql).value(0).toString();
}

int Sql::insert(const QSqlDatabase &sqlCon, const QString &sql, const QList<QVariant> &params)
{
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sql);
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }



    res &= q.exec();
    if(res) {
        int id = q.lastInsertId().toInt();

        return id;
    }

    throw SqlException(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
}

QString SqlUtil3::Sql::getDebugString(const QString &sql, const QList<QVariant> &params) {
    QString result(sql);
    for(int i = 0; i < params.size(); i++) {
        //       qDebug()<<params.at(i).typeName();
        QString v = QString(params.at(i).typeName()) != QStringLiteral("QByteArray") ? params.at(i).toString() : QString(params.at(i).toByteArray().toHex());
        QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')), 1,
                       v.isNull() ? QStringLiteral("NULL") : e.exactMatch(v) ? v : QStringLiteral("'") + v + QStringLiteral("'"));
    }
    return result;
}
