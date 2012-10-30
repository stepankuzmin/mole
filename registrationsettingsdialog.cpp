#include "registrationsettingsdialog.h"
#include "ui_registrationsettingsdialog.h"

RegistrationSettingsDialog::RegistrationSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationSettingsDialog)
{
    ui->setupUi(this);
}

RegistrationSettingsDialog::~RegistrationSettingsDialog()
{
    delete ui;
}
