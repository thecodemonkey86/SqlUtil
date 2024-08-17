#pragma once
#include <QString>
#include <QList>
#include <QPair>
#include <QVariant>
#include "sqlutil4_global.h"
#include <QSqlQuery>

namespace SqlUtil4 {
class SQLUTIL4SHARED_EXPORT SqlQuery
{
public:
    enum OrderDirection{ ORDER_ASC, ORDER_DESC};
    SqlQuery();
    virtual ~SqlQuery();
    SqlQuery& select();
    SqlQuery& select(const QString & selectFields);
    SqlQuery& from(const QString &  fromTable);
    SqlQuery& from(const QString &  fromTable,const QString &  alias);
    SqlQuery& join(const QString &  joinTable, const QString &alias, const QString &  on);
    SqlQuery& join(const QString &  joinTableAlias, const QString &  on);
    SqlQuery& join(const QString &  joinTable, const QString &alias, const QString &  on, const QVariant&param);
    SqlQuery& join(const QString &  joinTableAlias, const QString &  on, const QVariant&param);
    SqlQuery &join(const QString &joinTableAlias, const QString &on, const QSet<int64_t> &params);
    template<class T>SqlQuery &join(const QString &joinTableAlias, const QString &on, const QSet<T> &params)
    {
      for(const auto & param : params)
      {
        this->params.append(param);
      }
      return join(joinTableAlias,on);
    }

    SqlQuery& leftJoin(const QString &  joinTable, const QString &alias, const QString &  on);
    SqlQuery& leftJoin(const QString &  joinTable, const QString &alias, const QString &  on, const QVariant&param);
    SqlQuery& leftJoin(const QString &  joinTable, const QString &alias, const QString &  on, const QList<QVariant>& params);
    SqlQuery& leftJoin(const QString &  joinTable, const QLatin1String &alias, const QLatin1String &  on);

    SqlQuery& leftJoin(const QString &  joinTableAlias, const QString &  on);
    SqlQuery& leftJoin(const QString &  joinTableAlias, const QString &  on, const QVariant&param);
    SqlQuery& leftJoin(const QString &  joinTableAlias, const QString &  on, const QList<QVariant>& params);
    SqlQuery& where(const QString &  whereCond);
    SqlQuery& where(const QString &  whereCond, const QVariant&param);
    SqlQuery& where(const QString &  whereCond, int param);
    SqlQuery& where(const QString &  whereCond, qint64 param);
    SqlQuery& where(const QString &  whereCond, const QList<QVariant>& params);
    SqlQuery& andWhere(const QString &  whereCond);
    SqlQuery& andWhere(const QString &  whereCond, const QVariant&param);
    SqlQuery& andWhere(const QString &  whereCond, const QList<QVariant>& params);
    SqlQuery& orWhere(const QString &  whereCond);
    SqlQuery& whereIn(const QString &  expression, const QList<QVariant>& inParams );
    SqlQuery& whereIn(const QStringList &  columns, const QList<QVariant>& inParams );
    SqlQuery& andWhereIn(const QString &  expression, const QList<QVariant>& inParams );
    SqlQuery& andWhereIn(const QStringList &  columns, const QList<QVariant>& inParams );
    SqlQuery& leftParentheses(const QString &  expression);
    SqlQuery& rightParentheses();
    SqlQuery& limit(int limitResults);
    SqlQuery& orderBy(const QString & orderByExpression);
    SqlQuery& orderBy(const QString & order,  OrderDirection direction);
    SqlQuery& deleteFrom(const QString &  table);
    QSqlQuery execQuery(const QSqlDatabase & sqlCon);
    void execute(const QSqlDatabase & sqlCon);
    int fetchInt(const QSqlDatabase & sqlCon);
    uint fetchUInt(const QSqlDatabase & sqlCon);
    virtual QString toString()=0;
    #ifdef QT_DEBUG
    QString debugAsString();
      void debug();
    #endif

public:
    static const QString IN;
    static const QString AND;
    static const QString OR;
    static const QChar LP;
    static const QChar RP;
//    static const QString ON;
    //    static const QString JOIN;

protected:
    QString selectFields;
    QString fromTable;
    QString orderByExpression;
    QList<QString > joinTables;
    QList<QString> conditions;
    QList<QString> group;
    int limitResults;
    QString deleteFromTable;
    QList<QVariant> params;
};


}

