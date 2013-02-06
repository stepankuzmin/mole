#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // List all available COM ports
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i=0; i<ports.size(); i++)
        ui->COMPortsComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_toggleConnectionPushButton_toggled(bool checked)
{
    Mole *mole = Mole::getInstance();
    if (checked) {
        QString portName = ui->COMPortsComboBox->itemData(ui->COMPortsComboBox->currentIndex()).toString();
        std::string str = portName.toStdString();
        const char *portString = str.c_str();
        if (mole->connect(portString) < 0) {
            ui->toggleConnectionPushButton->setChecked(false);
            QMessageBox::critical(0, "Error", "Can't open connection.");
        }
        else {
            ui->toggleConnectionPushButton->setText(tr("Disconnect"));
        }
    }
    else {
        if (mole->disconnect()) {
            ui->toggleConnectionPushButton->setText(tr("Connect"));
        }
    }
}

void SettingsDialog::on_setModulesModePushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    if (ui->moduleModeSleepRadioButton->isChecked()) {
        mole->setModulesMode(ME_MMM_SLEEP);
    }
    else if(ui->moduleModeSeismicRadioButton->isChecked()) {
        mole->setModulesMode(ME_MMM_SEISMIC);
    }
    else if(ui->moduleModeInclinometerRadioButton->isChecked()) {
        mole->setModulesMode(ME_MMM_INCLINOMETER);
    }
}

void SettingsDialog::on_toggleConversionPushButton_toggled(bool checked)
{
    Mole *mole = Mole::getInstance();
    if (checked) {
        if (ui->softwareSynchronizationRadioButton->isChecked()) {
            mole->setConversionSynchronization(ME_MCS_SOFT);
        }
        else if (ui->ExternalSynchronizationRadioButton->isChecked()) {
            mole->setConversionSynchronization(ME_MCS_EXTERNAL);
        }
        if (mole->startConversion()) {
            ui->toggleConversionPushButton->setText(tr("Stop conversion"));
        }
        else {
            ui->toggleConversionPushButton->setChecked(false);
        }
    }
    else {
        if (mole->stopConversion()) {
            ui->toggleConversionPushButton->setText(tr("Start conversion"));
        }
        else {
            ui->toggleConversionPushButton->setChecked(true);
        }
    }
}

void SettingsDialog::on_buttonBox_accepted()
{
}
