#include "sqlutil.h"
#include <QString>

SqlUtil3::SqlUtil::SqlUtil()
{
}

QString SqlUtil3::SqlUtil::getPlaceholders(int count)
{
    QString placeholders;
    placeholders.reserve(count*2+1);
    placeholders[0] = '(';
    for(int i=1;i<placeholders.capacity()-1; i++) {
        if (i%2==0) {
            placeholders[i] = ',';
        } else {
            placeholders[i] = '?';
        }
    }
    placeholders[placeholders.capacity()-1] = ')';
    return placeholders;
}

QString SqlUtil3::SqlUtil::getTuplePlaceholders(int numberOfTuples, int tupleItemCount)
{
  QString placeholders;
  placeholders.reserve((2*numberOfTuples+1)*tupleItemCount+tupleItemCount-1);
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

QString SqlUtil3::SqlUtil::getArrayPlaceholders(int count)
{
  QString placeholders;
  placeholders.reserve(count*2+1);
  placeholders[0] = '[';
  for(int i=1;i<placeholders.capacity()-1; i++) {
    if (i%2==0) {
      placeholders[i] = ',';
    } else {
      placeholders[i] = '?';
    }
  }
  placeholders[placeholders.capacity()-1] = ']';
  return placeholders;
}
