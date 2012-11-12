#include <QDebug>

#include "registrationsettingsdialog.h"
#include "ui_registrationsettingsdialog.h"

RegistrationSettingsDialog::RegistrationSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationSettingsDialog)
{
    ui->setupUi(this);
    ui->moduleModeComboBox->addItem("Sleep",        QVariant(ME_MMM_SLEEP));
    ui->moduleModeComboBox->addItem("Seismic",      QVariant(ME_MMM_SEISMIC));
    ui->moduleModeComboBox->addItem("Inclinometer", QVariant(ME_MMM_INCLINOMETER));

    ui->testGeneratorModeComboBox->addItem("ON", QVariant(ME_MMTG_ON));
    ui->testGeneratorModeComboBox->addItem("OFF", QVariant(ME_MMTG_OFF));

    ui->moduleDatarateComboBox->addItem("ME_MMD_250",   QVariant(ME_MMD_250));
    ui->moduleDatarateComboBox->addItem("ME_MMD_500",   QVariant(ME_MMD_500));
    ui->moduleDatarateComboBox->addItem("ME_MMD_1000",  QVariant(ME_MMD_1000));
    ui->moduleDatarateComboBox->addItem("ME_MMD_2000",  QVariant(ME_MMD_2000));
    ui->moduleDatarateComboBox->addItem("ME_MMD_4000",  QVariant(ME_MMD_4000));
}

RegistrationSettingsDialog::~RegistrationSettingsDialog()
{
    delete ui;
}

void RegistrationSettingsDialog::on_buttonBox_accepted()
{
}

void RegistrationSettingsDialog::on_setModuleModePushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    switch (ui->moduleModeComboBox->itemData(ui->moduleModeComboBox->currentIndex()).toInt()) {
    case ME_MMM_SLEEP: {
        mole->setModuleMode(ME_MMM_SLEEP);
    } break;
    case ME_MMM_SEISMIC: {
        mole->setModuleMode(ME_MMM_SEISMIC);
    } break;
    case ME_MMM_INCLINOMETER: {
        mole->setModuleMode(ME_MMM_INCLINOMETER);
    } break;
    }
}

void RegistrationSettingsDialog::on_setDataratePushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    switch (ui->moduleDatarateComboBox->itemData(ui->moduleDatarateComboBox->currentIndex()).toInt()) {
    case ME_MMD_250: {
        mole->setModuleDatarate(ME_MMD_250);
    } break;
    case ME_MMD_500: {
        mole->setModuleDatarate(ME_MMD_500);
    } break;
    case ME_MMD_1000: {
        mole->setModuleDatarate(ME_MMD_1000);
    } break;
    case ME_MMD_2000: {
        mole->setModuleDatarate(ME_MMD_2000);
    } break;
    case ME_MMD_4000: {
        mole->setModuleDatarate(ME_MMD_4000);
    } break;
    }
}

void RegistrationSettingsDialog::on_setTestGeneratorModePushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    switch(ui->testGeneratorModeComboBox->itemData(ui->testGeneratorModeComboBox->currentIndex()).toInt()) {
        case ME_MMTG_OFF: {
            mole->setModuleTestGeneratorAll(ME_MMTG_OFF);
        } break;
        case ME_MMTG_ON: {
            mole->setModuleTestGeneratorAll(ME_MMTG_OFF);
        } break;
    }
}
