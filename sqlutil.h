#ifndef SQLUTIL_H
#define SQLUTIL_H

#include "sqlutil4_global.h"
namespace SqlUtil4 {
class SQLUTIL4SHARED_EXPORT SqlUtil
{

public:
    SqlUtil();
    static QString getPlaceholders(int count);
    static QString getArrayPlaceholders(int count);
    static QString getTuplePlaceholders(int numberOfTuples, int tupleItemCount);
};
}


#endif // SQLUTIL_H
