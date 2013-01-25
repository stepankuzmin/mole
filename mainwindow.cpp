#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // Destroy mole
    Mole *mole = Mole::getInstance();
    mole->~Mole();
}

void MainWindow::on_actionSettings_triggered()
{
    emit showSettingsDialog();
}

void MainWindow::setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization) {
    QString label;

    switch (conversionSynchronization) {
        case ME_MCS_COUNT:      label = tr("ME_MCS_COUNT"); break;
        case ME_MCS_SOFT:       label = tr("Software"); break;
        case ME_MCS_EXTERNAL:   label = tr("External"); break;
    }

    ui->conversionSynchronizationLabel->setText(label);
}
