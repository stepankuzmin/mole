#include "mole.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include "testsuite.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mole *mole = Mole::getInstance();

    MainWindow mainWindow;
    SettingsDialog *settingsDialog = new SettingsDialog(&mainWindow);
    TestSuite *testSuite = new TestSuite(&mainWindow);

    QObject::connect(&mainWindow, SIGNAL(showSettingsDialog()),
                     settingsDialog, SLOT(show()));
    QObject::connect(&mainWindow, SIGNAL(showTestSuite()),
                     testSuite, SLOT(show()));
    QObject::connect(testSuite, SIGNAL(showSettingsDialog()),
                     settingsDialog, SLOT(show()));

    QObject::connect(mole, SIGNAL(connectionStateChanged(bool)),
                     &mainWindow, SLOT(setConnectionState(bool)));
    QObject::connect(mole, SIGNAL(modulesModeChanged(me_mole_module_mode)),
                     &mainWindow, SLOT(setModulesMode(me_mole_module_mode)));
    QObject::connect(mole, SIGNAL(conversionSynchronizationChanged(me_mole_conversion_synchronization)),
                     &mainWindow, SLOT(setConversionSynchronization(me_mole_conversion_synchronization)));
    QObject::connect(mole, SIGNAL(dataDump(uint8,uint8,uint16,QVector<double>,QVector<double>)),
                     &mainWindow, SLOT(plotData(uint8,uint8,uint16,QVector<double>,QVector<double>)));

    mainWindow.showMaximized();
    
    return a.exec();
}
