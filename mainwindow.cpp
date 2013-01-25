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

void MainWindow::setConnectionStatus(me_mole_connection_status connectionStatus) {
    QString label;

    switch (connectionStatus) {
        case ME_MCS_CONNECTED:      label = tr("Connected"); break;
        case ME_MCS_DISCONNECTED:   label = tr("Disonnected"); break;
    }

    ui->connectionStatusLabel->setText(label);
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
