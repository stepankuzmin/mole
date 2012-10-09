#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    qDebug("construct");
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    qDebug("destruct");
    delete ui;
}
