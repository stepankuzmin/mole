#include <QDebug>
#include <QApplication>

#include "mole.h"
#include "mainwindow.h"
#include "settingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mole* mole = Mole::getInstance();

    MainWindow w;
    w.show();
    
    return a.exec();
}
