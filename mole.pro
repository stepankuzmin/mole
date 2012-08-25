#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T12:38:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mole
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    include/mole-engine/mole-engine-test-suite.h \
    include/mole-engine/mole-engine.h \
    include/seg/Segy.h \
    include/shared/config.h \
    include/shared/common.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lmole-engine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lmole-engine
else:symbian: LIBS += -lmole-engine
else:unix: LIBS += -L$$PWD/lib/ -lmole-engine

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
