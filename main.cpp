#include <QDebug>
#include <QApplication>



#include "mole.h"
#include "mainwindow.h"
#include "settingsdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mole *mole = Mole::getInstance();

    int mole_descriptor = -1;
    int ret = 0;

    ret = mole->init();
    if (ret < 0)
        qDebug() << "Can't me_init(), ret=" << ret;
    qDebug() << "getDefaultRetries" << mole->getDefaultRetries();

    MainWindow w;
    w.show();
    
    return a.exec();
}
