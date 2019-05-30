#ifndef SQLUTIL_H
#define SQLUTIL_H

#include "sqlutil3_global.h"
namespace SqlUtil3 {
class SQLUTIL3SHARED_EXPORT SqlUtil
{

public:
    SqlUtil();
    static QString getPlaceholders(int count);
};
}


#endif // SQLUTIL_H
