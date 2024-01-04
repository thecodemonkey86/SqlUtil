#include "sqlcon.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QVector>
#include <QSet>
#include <QRegularExpression>
#ifdef QT_DEBUG
#include <QDebug>
#endif
#include <exception/qtexception.h>
#include <exception/sqlexception.h>
#include <QSqlError>
#include <QSqlDriver>
using namespace SqlUtil4;

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

QSqlDatabase Sql::connectIbase(const QString &host, const QString &user, const QString &pass, const QString &dbFile, int port)
{
  QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QIBASE"));

  con.setDatabaseName(QStringLiteral("%1/%2:%3").arg(host, QString::number(port), dbFile));

  con.setConnectOptions("CHARSET=UNICODE_FSS");
  con.setUserName(user);
  con.setPassword(pass);

  if(con.open()) {
    return con;
  } else {
    throwExceptionWithLine(con.lastError().text());
  }
}

QSqlDatabase Sql::connectIbase(const QString &host, const QString &user, const QString &pass, const QString &dbFile, const QString &conName, int port)
{
  QSqlDatabase con = QSqlDatabase::addDatabase(QStringLiteral("QIBASE"),conName);

  con.setDatabaseName(QStringLiteral("%1/%2:%3").arg(host, QString::number(port), dbFile));

  con.setConnectOptions("CHARSET=UNICODE_FSS");
  con.setUserName(user);
  con.setPassword(pass);

  if(con.open()) {
    return con;
  } else {
    throwExceptionWithLine(con.lastError().text());
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

QSqlDatabase Sql::connectSqlite(const QString &dbFile)
{
  auto con = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
  con.setDatabaseName(dbFile);


  if(con.open()) {
    return con;
  } else {
    throw SqlException(con.lastError().nativeErrorCode(),
                       con.driver()->lastError().text());
  }
}
QSqlDatabase Sql::connectSqlite(const QString &dbFile,const QString & connectionName)
{
  auto con = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"),connectionName);
  con.setDatabaseName(dbFile);


  if(con.open()) {
    #ifdef QT_DEBUG
    qDebug()<<connectionName;
#endif
//#ifdef QT_DEBUG
//    auto q=Sql::query(con,"pragma COMPILE_OPTIONS");
//    while(q.next())
//    {
//        qDebug()<<q.value(0);
//    }
//#endif
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

            throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                      !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sql,QVariantList() << param));
        }
        return q;

    }


    throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),
                       sqlCon.driver()->lastError().text(),getDebugString(sql,QVariantList() << param));
}
QSqlQuery Sql::query(const QSqlDatabase & sqlCon, const QString & sql) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql)) {
        if(!q.exec()) {

            throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                      !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),sql);
        }
        return q;

    }


    throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),
                       sqlCon.driver()->lastError().text(),sql);
}

QSqlQuery Sql::query(const QSqlDatabase & sqlCon, const QString & sql, const QList<QVariant> & params) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);

    if(q.prepare(sql)) {
        for(int i = 0; i < params.size(); i++) {
            q.addBindValue(params.at(i));

        }
        if(!q.exec()) {
#ifdef QT_DEBUG
          qDebug().noquote() << "Error:"+ Sql::getDebugString(sql,params);
#endif
            throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                              !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sql, params));
        }
        return q;

    }
    throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),
                       sqlCon.driver()->lastError().text(),sql);
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QList<QVariant> &params) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(!q.prepare(sqlQuery))
    {
      #ifdef QT_DEBUG
      qDebug().noquote() << sqlCon.lastError().databaseText();
      qDebug().noquote() << getDebugString(sqlQuery,params);
      #endif
      throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                !q.lastError().text().isEmpty()? q.lastError().text():sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, params));

    }
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }

    if(!q.exec()) {
#ifdef QT_DEBUG
      qDebug().noquote() << sqlQuery;
      qDebug().noquote() << "Query:"+ Sql::getDebugString(sqlQuery,params);
      qDebug().noquote() << "Error:"+q.lastError().text();
#endif
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                           !q.lastError().text().isEmpty()? q.lastError().text():sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, params));
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, int64_t param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, int param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, const QString& param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
    }
}

void Sql::execute(const QSqlDatabase &sqlCon, const QString &sqlQuery, const QVariant &param)
{
  QSqlQuery q(sqlCon);
  bool res = q.prepare(sqlQuery);
  q.addBindValue(param);

  res = res & q.exec();


  if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
  }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, double param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, bool param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
    }
}


void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery, float param) {
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sqlQuery);
    q.addBindValue(QVariant::fromValue(param));

    res = res & q.exec();


    if(!res) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),getDebugString(sqlQuery, QVariantList() << param ));
    }
}

void Sql::execute(const QSqlDatabase & sqlCon, const QString &sqlQuery) {
    QSqlQuery q(sqlCon);
    if(!q.exec(sqlQuery)) {
        throwSqlExceptionWithLine(q.lastError().nativeErrorCode(),
                                  !q.lastError().text().isEmpty() ?q.lastError().text() :  sqlCon.driver()->lastError().text(),sqlQuery);
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

    throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql, QVariantList() << param ));
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

   throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql, QVariantList() << param ));
}

QSqlRecord Sql::fetchRow(const QSqlDatabase & sqlCon, const QString & sql) {
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if(q.prepare(sql) &&  q.exec() && q.next()) {
        return q.record();
    }

     throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), sql);
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

    throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql,  params ));
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QSqlRecord Sql::fetchRow(const QSqlDatabase &sqlCon, const QString &sql, const QVector<int64_t> &params)
{
  QSqlQuery q(sqlCon);
  q.setForwardOnly(true);
  if(q.prepare(sql)) {

    for(int i = 0; i < params.size(); i++) {
      q.addBindValue(QVariant(params.at(i)));

    }
    if(q.exec()) {

      if(q.next()) {
        return q.record();
      }
    }

  }

  QVariantList vparams;
  for(auto p:params)
  {
      vparams += QVariant(p);
  }
  throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql, vparams ));
}
#endif

QSqlRecord Sql::fetchRow(const QSqlDatabase &sqlCon, const QString &sql, const QSet<int64_t> &params)
{
  QSqlQuery q(sqlCon);
  q.setForwardOnly(true);
  if(q.prepare(sql)) {

    for(auto p:params) {
      q.addBindValue(QVariant(p));

    }
    if(q.exec()) {

      if(q.next()) {
        return q.record();
      }
    }

  }

  QVariantList vparams;
  for(auto p:params)
  {
      vparams += QVariant(p);
  }
  throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql, vparams ));
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
#ifdef QT_DEBUG
    qDebug().noquote() << getDebugString(sql,params);
#endif

    throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql, params ));
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString &sql, const QVariant &param)
{
    bool ok;
    int val = fetchRow(sqlCon,sql, param).value(0).toInt(&ok);
    if(!ok) {
        throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, QVariantList() << param));
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString &sql, const QString &param)
{
    bool ok;
    int val = fetchRow(sqlCon,sql, param).value(0).toInt(&ok);
    if(!ok) {
        throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, QVariantList() << param));
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString & sql, const QList<QVariant> & params){
    bool ok;
    int val = fetchRow(sqlCon, sql, params).value(0).toInt(&ok);
    if(!ok) {
        throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, params));
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString &sql, const QList<QPair<QString, QVariant> > &params)
{
    bool ok;
    int val = fetchRow(sqlCon,sql, params).value(0).toInt(&ok);
    if(!ok) {
        throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, params));
    }
    return val;
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
int Sql::fetchInt(const QSqlDatabase &sqlCon, const QString &sql, const QVector<int64_t> &params)
{
  bool ok;
  int val = fetchRow(sqlCon, sql, params).value(0).toInt(&ok);
  if(!ok) {


    throwSqlExceptionWithLine("", "Invalid query",sql);
  }
  return val;
}
#endif
int Sql::fetchInt(const QSqlDatabase &sqlCon, const QString &sql, const QSet<int64_t> &params)
{
    bool ok;
    int val = fetchRow(sqlCon, sql, params).value(0).toInt(&ok);
    if(!ok) {
      throwSqlExceptionWithLine("", "Invalid query",sql);
    }
    return val;
}

int Sql::fetchInt(const QSqlDatabase & sqlCon, const QString & sql){
    bool ok;
    int val = fetchRow(sqlCon,sql).value(0).toInt(&ok);
    if(!ok) {
        throwSqlExceptionWithLine("", "Invalid query",sql);
    }
    return val;
}

int64_t Sql::fetchInt64(const QSqlDatabase & sqlCon, const QString & sql){
    bool ok;
    int64_t val = fetchRow(sqlCon,sql).value(0).toLongLong(&ok);
    if(!ok) {
        throwSqlExceptionWithLine("", "Invalid query",sql);
    }
    return val;
}


int64_t Sql::fetchInt64(const QSqlDatabase & sqlCon, const QString & sql, const QVariantList & params){
    bool ok;
    int64_t val = fetchRow(sqlCon,sql,params).value(0).toLongLong(&ok);
    if(!ok) {
        QVariantList vparams;
        for(auto p:params)
        {
            vparams += QVariant(p);
        }
        throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, vparams ));
    }
    return val;
}

int64_t Sql::fetchInt64(const QSqlDatabase &sqlCon, const QString &sql, const QString &param)
{
  bool ok;
  int64_t val = fetchRow(sqlCon,sql, param).value(0).toLongLong(&ok);
  if(!ok) {
    throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, QVariantList() << param));
  }
  return val;
}

int64_t Sql::fetchInt64(const QSqlDatabase &sqlCon, const QString &sql, const QVariant &param)
{
  bool ok;
  int64_t val = fetchRow(sqlCon,sql, param).value(0).toLongLong(&ok);
  if(!ok) {
    throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, QVariantList() << param));
  }
  return val;
}

uint Sql::fetchUInt(const QSqlDatabase & sqlCon, const QString & sql){
  bool ok;
  uint val = fetchRow(sqlCon,sql).value(0).toUInt(&ok);
  if(!ok) {
    throwSqlExceptionWithLine("", "Invalid query",sql);
  }
  return val;
}


uint Sql::fetchUInt(const QSqlDatabase & sqlCon, const QString & sql, const QVariantList & params){
  bool ok;
  uint val = fetchRow(sqlCon,sql,params).value(0).toUInt(&ok);
  if(!ok) {
    QVariantList vparams;
    for(auto p:params)
    {
      vparams += QVariant(p);
    }
    throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, vparams ));
  }
  return val;
}

uint Sql::fetchUInt(const QSqlDatabase &sqlCon, const QString &sql, const QString &param)
{
  bool ok;
  uint val = fetchRow(sqlCon,sql, param).value(0).toUInt(&ok);
  if(!ok) {
    throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, QVariantList() << param));
  }
  return val;
}

uint Sql::fetchUInt(const QSqlDatabase &sqlCon, const QString &sql, const QVariant &param)
{
  bool ok;
  uint val = fetchRow(sqlCon,sql, param).value(0).toUInt(&ok);
  if(!ok) {
    throwSqlExceptionWithLine("", "Invalid query",getDebugString(sql, QVariantList() << param));
  }
  return val;
}
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
uint Sql::fetchUInt(const QSqlDatabase &sqlCon, const QString &sql, const QVector<int64_t> &params)
{
  bool ok;
  uint val = fetchRow(sqlCon, sql, params).value(0).toUInt(&ok);
  if(!ok) {


    throwSqlExceptionWithLine("", "Invalid query",sql);
  }
  return val;
}
#endif

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

int64_t Sql::insert(const QSqlDatabase &sqlCon, const QString &sql, const QList<QVariant> &params)
{
    QSqlQuery q(sqlCon);
    bool res = q.prepare(sql);
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }

    res &= q.exec();
    if(res) {
       return q.lastInsertId().toLongLong();
    }

    throwSqlExceptionWithLine(q.lastError().nativeErrorCode(), q.lastError().text(), getDebugString(sql,params));
}

QString SqlUtil4::Sql::getDebugString(const QString &sql, const QList<QVariant> &params) {
  QString result(sql);
  for(int i = 0; i < params.size(); i++) {
    //       qDebug()<<params.at(i).typeName();
    QString v = QString(params.at(i).typeName()) != QStringLiteral("QByteArray") ? params.at(i).toString() : QString(params.at(i).toByteArray().toHex());
    QRegularExpression e("^[0-9][0-9]*$");
    result.replace(result.indexOf(QChar('?')), 1,
                   v.isNull() ? QStringLiteral("NULL") : e.match(v).hasMatch() ? v : QStringLiteral("'") + v + QStringLiteral("'"));
  }
  return result;
}


QString SqlUtil4::Sql::getDebugString(const QString &sql, QList<QPair<QString,QVariant>> params) {
  QString result(sql);
  std::sort(params.begin(),params.end(),[](const QPair<QString,QVariant>&a,const QPair<QString,QVariant>&b){
    return a.first.length() > b.first.length();
  });
  for(int i = 0; i < params.size(); i++) {
    //       qDebug()<<params.at(i).typeName();
    QString v = QString(params[i].second.typeName()) != QStringLiteral("QByteArray") ? params[i].second.toString() : QString(params[i].second.toByteArray().toHex());
    QRegularExpression e("^[0-9][0-9]*$");
    result.replace(":"+params[i].first, v.isNull() ? QStringLiteral("NULL") :e.match(v).hasMatch() ? v : QStringLiteral("'") + v + QStringLiteral("'"));
  }
  return result;
}

void Sql::beginTransaction(const QSqlDatabase &sqlCon)
{
    sqlCon.driver()->beginTransaction();
}

void Sql::commitTransaction(const QSqlDatabase &sqlCon)
{
    sqlCon.driver()->commitTransaction();
}

void Sql::rollbackTransaction(const QSqlDatabase &sqlCon)
{
    sqlCon.driver()->rollbackTransaction();
}
