#include <QApplication>
#include <QTranslator>

#include "mole.h"
#include "mainwindow.h"
#include "registrationsettingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("mole_" + QLocale::system().name());
    a.installTranslator(&translator);

    Mole *mole = Mole::getInstance();

    MainWindow mainWindow;
    RegistrationSettingsDialog registrationSettingsDialog;

    mainWindow.showMaximized();

    QObject::connect(&mainWindow,                   SIGNAL(showRegistrationSettingsDialog()),
                     &registrationSettingsDialog,   SLOT(show()));

    QObject::connect(&registrationSettingsDialog,   SIGNAL(registrationModeChanged(QString)),
                     &mainWindow,                   SLOT(setRegistrationMode(QString)));

    QObject::connect(&registrationSettingsDialog,   SIGNAL(moduleDatarateChanged(int)),
                     &mainWindow,                   SLOT(setModuleDatarate(int)));

    QObject::connect(mole,          SIGNAL(stageChanged(me_test_suite_stage)),
                     &mainWindow,   SLOT(setStage(me_test_suite_stage)));

    QObject::connect(mole,          SIGNAL(dataDump(uint8,uint8,uint16,QList<double>,QList<double>)),
                     &mainWindow,   SLOT(plotData(uint8,uint8,uint16,QList<double>,QList<double>)));

    QObject::connect(mole,          SIGNAL(dataDump2(uint8,uint8,uint16,QVector<double>,QVector<double>)),
                     &mainWindow,   SLOT(plotData2(uint8,uint8,uint16,QVector<double>,QVector<double>)));

    //QObject::connect(mole, SIGNAL(stateChange(QString)), &w, SLOT(setStatusBarText(QString)));
    
    return a.exec();
}
