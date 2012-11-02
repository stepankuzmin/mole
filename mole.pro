#-------------------------------------------------
#
# Project created by QtCreator 2012-10-15T20:23:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mole
TEMPLATE = app

DEPENDPATH +=.
INCLUDEPATH +=.
TRANSLATIONS += mole_ru.ts

CONFIG += qwt\
        extserialport

win32: INCLUDEPATH += $$PWD/3rdparty/Qwt-6.0.1/include
win32: LIBS += -L$$PWD/3rdparty/Qwt-6.0.1/lib -lqwt
win32: LIBS += -L$$PWD/3rdparty/mole-engine/include
win32: LIBS += -L$$PWD/3rdparty/mole-engine/lib/ -lmole-engine

SOURCES += main.cpp\
        mainwindow.cpp \
        mole.cpp \
        registrationsettingsdialog.cpp

HEADERS  += mainwindow.h \
            mole.h \
            registrationsettingsdialog.h \
            3rdparty/mole-engine/include/mole-engine/mole-engine-test-suite.h \
            3rdparty/mole-engine/include/mole-engine/mole-engine.h \
            3rdparty/mole-engine/include/seg/Segy.h \
            3rdparty/mole-engine/include/shared/config.h \
            3rdparty/mole-engine/include/shared/common.h \

FORMS    += mainwindow.ui \
            registrationsettingsdialog.ui

