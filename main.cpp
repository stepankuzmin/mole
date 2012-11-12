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

    MainWindow w;
    RegistrationSettingsDialog registrationSettingsDialog;

    w.showMaximized();

    QObject::connect(&w, SIGNAL(showRegistrationSettingsDialog()), &registrationSettingsDialog, SLOT(show()));
    QObject::connect(mole, SIGNAL(stageChanged(me_test_suite_stage)), &w, SLOT(setStage(me_test_suite_stage)));

    QObject::connect(mole, SIGNAL(dataDump(uint8,uint8,uint16,QList<double>,QList<double>)),
                     &w, SLOT(plotData(uint8,uint8,uint16,QList<double>,QList<double>)));

    //QObject::connect(mole, SIGNAL(stateChange(QString)), &w, SLOT(setStatusBarText(QString)));
    
    return a.exec();
}
