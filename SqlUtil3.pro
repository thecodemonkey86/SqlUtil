#-------------------------------------------------
#
# Project created by QtCreator 2017-11-22T23:29:52
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = SqlUtil3
TEMPLATE = lib

DEFINES += SQLUTIL3_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    firebirdsqlquery.cpp \
    pgsqlquery.cpp \
    sqlcon.cpp \
    exception/sqlexception.cpp \
    sqlitesqlquery.cpp \
    sqlquery.cpp \
    sqlutil.cpp

HEADERS += \
        firebirdsqlquery.h \
        pgsqlquery.h \
        sqlitesqlquery.h \
        sqlquery.h \
        sqlutil.h \
        sqlutil3_global.h \ 
    sqlcon.h \
    exception/sqlexception.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

COMPILER = ""
ARCH = ""

msvc {

 COMPILER = "MSVC2017"
 MSVC_VER = $$(VisualStudioVersion)
 equals(MSVC_VER, 16.0){
     COMPILER = "MSVC2019"
 }

    equals(QMAKE_TARGET.arch, "x86_64"){
        ARCH = "64bit"
    } else {
         ARCH = "32bit"
    }

}


gcc {
    COMPILER = "MinGW"

equals(QMAKE_TARGET.arch, "x86_64"){
    ARCH = "64_bit"
} else {
     ARCH = "32_bit"
}
}

CONFIG(release, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/release/ -lQtCommon2
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../build/QtCommon2-Desktop_Qt_$${QT_MAJOR_VERSION}_$${QT_MINOR_VERSION}_$${QT_PATCH_VERSION}_$${COMPILER}_$${ARCH}/debug/ -lQtCommon2

INCLUDEPATH += $$PWD/../QtCommon2

