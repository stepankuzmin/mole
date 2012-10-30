#include <QApplication>
#include <QTranslator>

#include "mole.h"
#include "mainwindow.h"
#include "connectiondialog.h"
#include "registrationsettingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("mole_" + QLocale::system().name());
    a.installTranslator(&translator);


    Mole *mole = Mole::getInstance();

    MainWindow w;
    ConnectionDialog connectionDialog;
    RegistrationSettingsDialog registrationSettingsDialog;

    w.show();

    QObject::connect(&w, SIGNAL(showConnectionDialog()), &connectionDialog, SLOT(show()));
    QObject::connect(&w, SIGNAL(showRegistrationSettingsDialog()), &registrationSettingsDialog, SLOT(show()));

    QObject::connect(mole, SIGNAL(stateChange(QString)), &w, SLOT(setStatusBarText(QString)));
    
    return a.exec();
}
