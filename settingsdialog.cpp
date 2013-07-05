#include "settingsdialog.h"
#include "ui_settingsdialog.h"

/*
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Datarate items
    ui->datarateComboBox->addItem("250", QVariant(ME_MMD_250));
    ui->datarateComboBox->addItem("500", QVariant(ME_MMD_500));
    ui->datarateComboBox->addItem("1000", QVariant(ME_MMD_1000));
    ui->datarateComboBox->addItem("2000", QVariant(ME_MMD_2000));
    ui->datarateComboBox->addItem("4000", QVariant(ME_MMD_4000));

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

void SettingsDialog::on_setConversionSynchronizationPushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    if (ui->synchronizationSoftwareRadioButton->isChecked()) {
        mole->setConversionSynchronization(ME_MCS_SOFT);
    }
    else if (ui->synchronizationExternalRadioButton->isChecked()) {
        mole->setConversionSynchronization(ME_MCS_EXTERNAL);
    }
}

void SettingsDialog::on_setSamplesSizePushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    uint16 samplesSize = ui->samplesComboBox->currentText().toInt();
    mole->setSamplesSize(samplesSize);
}

void SettingsDialog::on_setDataratePushButton_clicked()
{
    int datarate = ME_MMD_COUNT;
    Mole *mole = Mole::getInstance();
    datarate = ui->datarateComboBox->itemData(ui->datarateComboBox->currentIndex()).toInt();
    switch (datarate) {
        case ME_MMD_250: {
            mole->setDatarate(ME_MMD_250);
        } break;
        case ME_MMD_500: {
            mole->setDatarate(ME_MMD_500);
        } break;
        case ME_MMD_1000: {
            mole->setDatarate(ME_MMD_1000);
        } break;
        case ME_MMD_2000: {
            mole->setDatarate(ME_MMD_2000);
        } break;
        case ME_MMD_4000: {
            mole->setDatarate(ME_MMD_4000);
        } break;
    }
}

void SettingsDialog::on_buttonBox_accepted()
{
}
*/
