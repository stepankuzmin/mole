#include <QDebug>
#include "qextserialenumerator.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    qDebug("construct");
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    qDebug() << "SerialSettings::LoadPorts(): List of ports avaliables:\n";
    for (int i=0; i<ports.size(); i++) {
        qDebug() << "port name: " << ports.at(i).portName;
        qDebug() << "friendly name: " << ports.at(i).friendName;
        qDebug() << "physical name: " << ports.at(i).physName;
        qDebug() << "enumerator name: " << ports.at(i).enumName;
    }
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    qDebug("destruct");
    delete ui;
}
