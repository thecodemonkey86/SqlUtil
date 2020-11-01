#include "sqlquery.h"
#include <QFile>
#include <QSqlDriver>
#ifdef QT_DEBUG
#include <QDebug>
#endif
#include <QSqlRecord>
using namespace SqlUtil3;

SqlQuery::SqlQuery(const QSqlDatabase & sqlCon)
{
    this->limitResults = 0;
    this->sqlCon = sqlCon;
}

SqlQuery::~SqlQuery() {

}

SqlQuery&SqlQuery::select()
{
    this->selectFields = QLatin1String("*");
    return *this;
}

SqlQuery&SqlQuery::select(const QString &selectFields)
{
    this->selectFields = selectFields;
    return *this;
}

SqlQuery&SqlQuery::from(const QString &fromTable)
{
    this->fromTable = fromTable;
    return *this;
}

SqlQuery&SqlQuery::from(const QString &fromTable, const QString &alias)
{
    this->fromTable = QLatin1String("%1 %2").arg(fromTable,alias);
    return *this;
}

SqlQuery&SqlQuery::join(const QString &joinTable, const QString &alias, const QString & on)
{
    this->joinTables.append(QLatin1String(" JOIN %1 %2 ON %3").arg( joinTable, alias, on));
    return *this;
}

SqlQuery&SqlQuery::join(const QString &joinTableAlias, const QString &on)
{
    this->joinTables.append(QLatin1String(" JOIN %1 ON %2").arg( joinTableAlias,on));
    return *this;
}

SqlQuery&SqlQuery::join(const QString &joinTable, const QString &alias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return join(joinTable,alias,on);
}

SqlQuery&SqlQuery::join(const QString &joinTableAlias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return join(joinTableAlias,on);
}


SqlQuery&SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString & on)
{
    this->joinTables.append(QLatin1String(" LEFT JOIN %1 %2 ON %3").arg(joinTable, alias,on));
    return *this;
}

SqlQuery&SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return leftJoin(joinTable,alias,on);
}

SqlQuery&SqlQuery::leftJoin(const QString &joinTable, const QString &alias, const QString &on, const QList<QVariant> &params)
{
    this->params.append(params);
    return leftJoin(joinTable,alias,on);
}

SqlQuery&SqlQuery::leftJoin(const QString &joinTable, const QLatin1String &alias, const QLatin1String &on)
{
    this->joinTables.append(QLatin1String(" LEFT JOIN %1 %2 ON %3").arg(joinTable, alias,on));
    return *this;
}

SqlQuery&SqlQuery::leftJoin(const QString &joinTableAlias, const QString &on)
{
    this->joinTables.append(QLatin1String(" LEFT JOIN %1 ON %2").arg(joinTableAlias,on));
    return *this;
}

SqlQuery&SqlQuery::leftJoin(const QString &joinTableAlias, const QString &on, const QVariant &param)
{
    this->params.append(param);
    return leftJoin(joinTableAlias,on);
}

SqlQuery&SqlQuery::leftJoin(const QString &joinTableAlias, const QString &on, const QList<QVariant> &params)
{
    this->params.append(params);
    return leftJoin(joinTableAlias,on);
}

SqlQuery&SqlQuery::where(const QString &whereCond)
{
    if (!conditions.empty()) {
        this->conditions.append(AND);
    }
    this->conditions.append(whereCond);
    return *this;
}

SqlQuery&SqlQuery::where(const QString &whereCond, const QVariant &param)
{

    this->params.append(param);
    return where(whereCond);
}

SqlQuery&SqlQuery::where(const QString &whereCond, int param)
{

    this->params.append(QVariant::fromValue(param));
    return where(whereCond);
}

SqlUtil3::SqlQuery &SqlUtil3::SqlQuery::where(const QString &whereCond, qint64 param)
{
    this->params.append(QVariant::fromValue(param));
    return where(whereCond);
}

SqlQuery&SqlQuery::where(const QString &whereCond, const QList<QVariant>& params)
{

    this->params.append(params);
    return where(whereCond);
}

SqlQuery&SqlQuery::andWhere(const QString &whereCond)
{
    this->conditions.append(AND);
    this->conditions.append(whereCond);
    return *this;
}

SqlQuery&SqlQuery::andWhere(const QString &whereCond, const QList<QVariant>& params)
{
    this->params.append(params);
    this->conditions.append(AND);
    this->conditions.append(whereCond);
    return *this;
}

SqlQuery&SqlQuery::andWhere(const QString &whereCond, const QVariant &param)
{
    this->conditions.append(AND);
    this->conditions.append(whereCond);
    this->params.append(param);
    return *this;
}


SqlQuery&SqlQuery::orWhere(const QString &whereCond)
{
    this->conditions.append(OR);
    this->conditions.append(whereCond);
    return *this;
}
SqlQuery&SqlQuery::whereIn(const QStringList &columns, const QList<QVariant> &inParams)
{
    QStringList placeholdersList;
    placeholdersList.reserve(columns.size());

    for(int j=0;j<inParams.size()/ columns.size();j++) {
        QString placeholders;
        placeholders.reserve(columns.size()*2+1);
        placeholders[0] = LP;
        for(int i=1;i<placeholders.capacity()-1; i++) {
            if (i%2==0) {
                placeholders[i] = ',';
            } else {
                placeholders[i] = '?';
            }
        }
        placeholders[placeholders.capacity()-1] = RP;
        placeholdersList.append(placeholders);
    }

    this->conditions.append(LP);
    this->conditions.append(columns.join(QChar(',')));
    this->conditions.append(RP);
    this->conditions.append(IN);
    this->conditions.append(LP);
    this->conditions.append(placeholdersList.join(QChar(',')));
    this->conditions.append(RP);
    this->params.append(inParams);
    return *this;
}

SqlQuery&SqlQuery::whereIn(const QString &expression, const QList<QVariant> &inParams)
{
    QString placeholders;
    placeholders.reserve(inParams.size()*2+3);
    placeholders[0] = LP;
    for(int i=1;i<placeholders.capacity()-1; i++) {
        if (i%2==0) {
            placeholders[i] = ',';
        } else {
            placeholders[i] = '?';
        }
    }
    placeholders[placeholders.capacity()-1] = RP;
    this->conditions.append(expression);
    this->conditions.append(IN);
    this->conditions.append(placeholders);
    this->params.append(inParams);
    return *this;
}

SqlQuery&SqlQuery::andWhereIn(const QString &expression, const QList<QVariant> &inParams)
{
    this->conditions.append(AND);
    return whereIn(expression, inParams);
}

SqlQuery&SqlQuery::andWhereIn(const QStringList &columns, const QList<QVariant> &inParams)
{
    this->conditions.append(AND);
    return whereIn(columns, inParams);
}


SqlQuery&SqlQuery::leftParentheses(const QString &expression)
{
    this->conditions.append(LP);
    this->conditions.append(expression);
    return *this;
}

SqlQuery&SqlQuery::rightParentheses()
{
    this->conditions.append(RP);
    return *this;
}

SqlQuery&SqlQuery::limit(int limitResults)
{
    this->limitResults = limitResults;
    return *this;
}

SqlQuery&SqlQuery::orderBy(const QString &orderBy, OrderDirection direction)
{
    this->orderByExpression = QLatin1String("%1 %2 ").arg(orderBy, direction == SqlQuery::ORDER_ASC ? "asc" : "desc");
    return *this;
}

SqlQuery&SqlQuery::orderBy(const QString &orderByExpression)
{
    this->orderByExpression = orderByExpression;
    return *this;
}

SqlQuery&SqlQuery::deleteFrom(const QString &table)
{
    this->deleteFromTable = table;
    return *this;
}

QSqlQuery SqlQuery::execQuery()
{
    QSqlQuery q(sqlCon);
    q.setForwardOnly(true);
    if (q.prepare(toString())) {


        for(const QVariant & p : params) {
            q.addBindValue(p);

        }
        if (!q.exec()) {
            QString msg=q.lastError().text();
#ifdef QT_DEBUG
            qDebug()<<msg;
            qDebug()<<q.driver()->lastError().text();
#endif
            throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),sqlCon.lastError().text(), toString());
        }
        return q;

    } else {


#ifdef QT_DEBUG
        QString msg=q.lastError().text();
        qDebug()<<msg;
#endif
        throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),sqlCon.lastError().text(), toString());
    }

}


void SqlQuery::execute()
{
    QSqlQuery q(sqlCon);
    bool res = q.prepare(toString());
    for(int i = 0; i < params.size(); i++) {
        q.addBindValue(params.at(i));

    }

    res = res & q.exec();


    if(!res) {
#ifdef QT_DEBUG
        debug();
#endif
        throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),sqlCon.lastError().text(), toString());
    }
}

int SqlQuery::fetchInt()
{
    bool ok = false;
    auto query = execQuery();
    if(query.next()) {
      int i =  query.record().value(0).toInt(&ok);
      if(!ok) {
          throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),sqlCon.lastError().text(), toString());
      }
      return i;
    } else {
      throwExceptionWithLine("could not fetch row in query "+toString());
    }
}

uint SqlQuery::fetchUInt()
{
  bool ok = false;
  auto query = execQuery();
  if(query.next()) {
    uint i =  query.record().value(query.record().fieldName(0)).toUInt(&ok);
    if(!ok) {
      throwSqlExceptionWithLine(sqlCon.lastError().nativeErrorCode(),sqlCon.lastError().text(), toString());
    }
    return i;
  } else {
    throwExceptionWithLine("could not fetch row in query "+toString());
  }
}

#ifdef QT_DEBUG
void SqlQuery::debug()
{

    QString result(toString());
    for(int i=0;i<params.size();i++) {
        //       qDebug()<<params.at(i).typeName();
        QString v= QString(params.at(i).typeName())!= QString( "QByteArray") ? params.at(i).toString() :QString(params.at(i).toByteArray().toHex());
        QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')),1,
                       v.isNull()?QLatin1String("NULL"): e.exactMatch(v)?v:QLatin1String("'")+ v+ QLatin1String("'"));
    }
    qDebug() << result;


}


QString SqlQuery::debugAsString()
{
    QString result(toString());
    for(int i=0;i<params.size();i++) {
        //       qDebug()<<params.at(i).typeName();
        QString v= QString(params.at(i).typeName())!= QString( "QByteArray") ? params.at(i).toString() :QString(params.at(i).toByteArray().toHex());
        QRegExp e("^[0-9][0-9]*$");
        result.replace(result.indexOf(QChar('?')),1,
                       v.isNull()?QLatin1String("NULL"): e.exactMatch(v)?v:QLatin1String("'")+ v+ QLatin1String("'"));
    }
    return result;
}
#endif
const QString SqlQuery::IN(" IN ");
const QString SqlQuery::AND(" AND ");
const QString SqlQuery::OR(" OR ");
const QChar SqlQuery::LP('(');
const QChar SqlQuery::RP(')');
//const QString SqlQuery::ON = QLatin1String(" ON ");
//const QString SqlQuery::JOIN = QLatin1String(" JOIN ");


