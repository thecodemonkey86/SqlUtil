#ifndef SQLUTIL4_GLOBAL_H
#define SQLUTIL4_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLUTIL4_LIBRARY)
#  define SQLUTIL4SHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLUTIL4SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLUTIL4_GLOBAL_H