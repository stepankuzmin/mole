#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T14:17:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mole
TEMPLATE = app

win32: LIBS += -L$$PWD/3rdparty/mole-engine/include
win32: LIBS += -L$$PWD/3rdparty/mole-engine/lib/ -lmole-engine
win32: INCLUDEPATH += $$PWD/3rdparty/qwt/include
win32: LIBS += -L$$PWD/3rdparty/qwt/lib -lqwt
win32: include(3rdparty/qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    mole.cpp \
    testsuite.cpp \
    sd3.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    mole.h \
    testsuite.h \
    sd3.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    testsuite.ui
