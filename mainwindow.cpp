#include "qwt_plot.h"

#include "mainwindow.h"
#include "settingsdialog.h"
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
}

void MainWindow::on_action_settings_activated()
{
    //SettingsDialog *settingsDialog = new SettingsDialog(this);
    //settingsDialog->show();

    SettingsDialog sd(this);
    sd.exec();
}
