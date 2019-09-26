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
