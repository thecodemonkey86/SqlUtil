#include "sqlutil.h"
#include <QString>

SqlUtil4::SqlUtil::SqlUtil()
{
}

QString SqlUtil4::SqlUtil::getPlaceholders(int count)
{
    QString placeholders;
    placeholders.resize(count*2+1,QChar('\0'));
    placeholders[0] = '(';
    for(int i=1;i<placeholders.length()-1; i++) {
        if (i%2==0) {
            placeholders[i] = ',';
        } else {
            placeholders[i] = '?';
        }
    }
    placeholders[placeholders.length()-1] = ')';
    return placeholders;
}

QString SqlUtil4::SqlUtil::getTuplePlaceholders(int numberOfTuples, int tupleItemCount)
{
  QString placeholders;
  placeholders.resize((2*numberOfTuples+1)*tupleItemCount+tupleItemCount-1);
  placeholders += "(?";
  for(int i = 1;i < tupleItemCount; i++) {
    placeholders += ",?";
  }
  placeholders += (')');
  for(int j = 1; j < numberOfTuples; j++) {
    placeholders += ",(?";
    for(int i = 1;i < tupleItemCount; i++) {
      placeholders += ",?";
    }
    placeholders += ')';
  }
  return placeholders;
}

QString SqlUtil4::SqlUtil::getArrayPlaceholders(int count)
{
  QString placeholders;
  placeholders.resize(count*2+1,QChar('\0'));
  placeholders[0] = '[';
  for(int i=1;i<placeholders.length()-1; i++) {
    if (i%2==0) {
      placeholders[i] = ',';
    } else {
      placeholders[i] = '?';
    }
  }
  placeholders[placeholders.length()-1] = ']';
  return placeholders;
}
