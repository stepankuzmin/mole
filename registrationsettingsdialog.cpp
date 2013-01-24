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

    ui->inputModeComboBox->addItem("ME_MMI_TERMINATOR", QVariant(ME_MMI_TERMINATOR));
    ui->inputModeComboBox->addItem("ME_MMI_GEOPHONE", QVariant(ME_MMI_GEOPHONE));
    ui->inputModeComboBox->addItem("ME_MMI_SIN", QVariant(ME_MMI_SIN));
    ui->inputModeComboBox->addItem("ME_MMI_IN_PHASE", QVariant(ME_MMI_IN_PHASE));
    ui->inputModeComboBox->addItem("ME_MMI_GEOPHONE_WITH_SIN", QVariant(ME_MMI_GEOPHONE_WITH_SIN));
    ui->inputModeComboBox->addItem("ME_MMI_COUNT", QVariant(ME_MMI_COUNT));

    ui->testGeneratorModeComboBox->addItem("ON", QVariant(ME_MMTG_ON));
    ui->testGeneratorModeComboBox->addItem("OFF", QVariant(ME_MMTG_OFF));

    ui->moduleDatarateComboBox->addItem("250",   QVariant(ME_MMD_250));
    ui->moduleDatarateComboBox->addItem("500",   QVariant(ME_MMD_500));
    ui->moduleDatarateComboBox->addItem("1000",  QVariant(ME_MMD_1000));
    ui->moduleDatarateComboBox->addItem("2000",  QVariant(ME_MMD_2000));
    ui->moduleDatarateComboBox->addItem("4000",  QVariant(ME_MMD_4000));

    emit registrationModeChanged(QString("Testing!11"));
}

RegistrationSettingsDialog::~RegistrationSettingsDialog()
{
    delete ui;
}

void RegistrationSettingsDialog::on_buttonBox_accepted()
{
    emit registrationModeChanged(QString("Testing"));
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
    int moduleDatarate;
    moduleDatarate = ui->moduleDatarateComboBox->itemData(ui->moduleDatarateComboBox->currentIndex()).toInt();

    Mole *mole = Mole::getInstance();
    switch (moduleDatarate) {
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

    emit moduleDatarateChanged(moduleDatarate);
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

void RegistrationSettingsDialog::on_setInputModePushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    switch (ui->testGeneratorModeComboBox->itemData(ui->testGeneratorModeComboBox->currentIndex()).toInt()) {
        case ME_MMI_TERMINATOR: {
            mole->setModuleInputAll(ME_MMI_TERMINATOR);
        } break;
        case ME_MMI_GEOPHONE: {
            mole->setModuleInputAll(ME_MMI_GEOPHONE);
        } break;
        case ME_MMI_SIN: {
            mole->setModuleInputAll(ME_MMI_SIN);
        } break;
        case ME_MMI_IN_PHASE: {
            mole->setModuleInputAll(ME_MMI_IN_PHASE);
        } break;
        case ME_MMI_GEOPHONE_WITH_SIN: {
            mole->setModuleInputAll(ME_MMI_GEOPHONE_WITH_SIN);
        } break;
        case ME_MMI_COUNT: {
            mole->setModuleInputAll(ME_MMI_COUNT);
        } break;
    }
}
