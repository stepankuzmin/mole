#include <QDebug>
#include <QVariant>
#include "qextserialenumerator.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // List all avaliable COM ports
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    qDebug() << "SerialSettings::LoadPorts(): List of ports avaliables:\n";
    for (int i=0; i<ports.size(); i++) {
        qDebug() << "port name: " << ports.at(i).portName;
        qDebug() << "friendly name: " << ports.at(i).friendName;
        qDebug() << "physical name: " << ports.at(i).physName;
        qDebug() << "enumerator name: " << ports.at(i).enumName << "\n";

        // Add port friendly name to COM Ports ComboBox
        this->ui->COMPortsComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
    }

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_ConnectToCOMPortPushButton_clicked()
{
    QString portName = this->ui->COMPortsComboBox->itemData(this->ui->COMPortsComboBox->currentIndex()).toString();
    qDebug() << "Connect to: " << portName;
}
