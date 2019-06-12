#include "firebirdsqlquery.h"
using namespace SqlUtil3;

FirebirdSqlQuery::FirebirdSqlQuery(const QSqlDatabase & sqlCon) : SqlQuery(sqlCon) {

}


QString FirebirdSqlQuery::toString() {
    QString query;
    if(!selectFields.isEmpty()) {
        if(limitResults > 0) {
            query += QStringLiteral("SELECT FIRST %1 %2 FROM %3").arg(QString::number(limitResults), selectFields, fromTable);
        } else {
            query += QStringLiteral("SELECT %1 FROM %2").arg(selectFields, fromTable);
        }

    } else if(!deleteFromTable.isEmpty()) {
        query += QStringLiteral("DELETE FROM %1").arg(deleteFromTable);
    }

    for(int i = 0; i < joinTables.size(); i++) {
        query += joinTables.at(i);
    }

    if(!conditions.empty()) {
        query += QStringLiteral(" WHERE ");


        for(const QString & cond : conditions) {
            query += cond;
        }
    }

    if(group.size() > 0) {
        query += QStringLiteral(" GROUP BY %1").arg(group.at(0));
        for(int i = 1; i < group.size(); i++) {
            query += QStringLiteral(", %1").arg(group.at(i));
        }
    }

    return query;
}
