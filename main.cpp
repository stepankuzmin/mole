#include "mole.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include "testsuite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    Mole *mole = Mole::getInstance();

    TestSuite *testSuite = new TestSuite(&mainWindow);

    QObject::connect(&mainWindow, SIGNAL(showTestSuite()),
                     testSuite, SLOT(show()));

    QObject::connect(mole, SIGNAL(connectionStateChanged(bool)),
                     &mainWindow, SLOT(setConnectionState(bool)));
    QObject::connect(mole, SIGNAL(modulesModeChanged(me_mole_module_mode)),
                     &mainWindow, SLOT(setModulesMode(me_mole_module_mode)));
    QObject::connect(mole, SIGNAL(conversionSynchronizationChanged(me_mole_conversion_synchronization)),
                     &mainWindow, SLOT(setConversionSynchronization(me_mole_conversion_synchronization)));
    QObject::connect(mole, SIGNAL(samplesSizeChanged(uint16)),
                     &mainWindow, SLOT(setSamplesSize(uint16)));
    QObject::connect(mole, SIGNAL(datarateChanged(me_mole_module_datarate)),
                     &mainWindow, SLOT(setDatarate(me_mole_module_datarate)));

    QObject::connect(mole, SIGNAL(mdataDump(MData)),
                     &mainWindow, SLOT(plotMData(MData)));

    mainWindow.show();
    
    return a.exec();
}
