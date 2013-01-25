#include "mole.h"
#include "mainwindow.h"
#include "settingsdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mole *mole = Mole::getInstance();
    MainWindow mainWindow;
    SettingsDialog settingsDialog;

    QObject::connect(&mainWindow, SIGNAL(showSettingsDialog()),
                     &settingsDialog, SLOT(show()));

    QObject::connect(mole, SIGNAL(connectionStatusChanged(me_mole_connection_status)),
                     &mainWindow, SLOT(setConnectionStatus(me_mole_connection_status)));
    QObject::connect(mole, SIGNAL(conversionSynchronizationChanged(me_mole_conversion_synchronization)),
                     &mainWindow, SLOT(setConversionSynchronization(me_mole_conversion_synchronization)));

    mainWindow.show();
    
    return a.exec();
}
