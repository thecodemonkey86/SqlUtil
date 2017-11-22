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
    sqlcon.cpp \
    exception/sqlexception.cpp

HEADERS += \
        sqlutil3_global.h \ 
    sqlcon.h \
    exception/sqlexception.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_9_0_MinGW_32bit/release/ -lQtCommon2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_9_0_MinGW_32bit/debug/ -lQtCommon2
else:unix: LIBS += -L$$PWD/../build-QtCommon2-Desktop_Qt_5_9_0_MinGW_32bit/ -lQtCommon2

INCLUDEPATH += $$PWD/../QtCommon2

