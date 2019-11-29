#ifndef SQLUTIL_H
#define SQLUTIL_H

#include "sqlutil3_global.h"
namespace SqlUtil3 {
class SQLUTIL3SHARED_EXPORT SqlUtil
{

public:
    SqlUtil();
    static QString getPlaceholders(int count);
    static QString getArrayPlaceholders(int count);
    static QString getTuplePlaceholders(int numberOfTuples, int tupleItemCount);
};
}


#endif // SQLUTIL_H
