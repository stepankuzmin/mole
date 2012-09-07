#include <QApplication>
#include "mainwindow.h"
#include "mole-engine-test.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mole_engine_test();

    MainWindow w;
    w.show();
    
    return a.exec();
}
