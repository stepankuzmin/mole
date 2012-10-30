#include <QDebug>

#include "mole.h"
#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "qextserialenumerator.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    // List all avaliable COM ports
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    qDebug() << "List of avaliable ports:\n";
    for (int i=0; i<ports.size(); i++) {
        qDebug() << "port name: " << ports.at(i).portName;
        qDebug() << "friendly name: " << ports.at(i).friendName;
        qDebug() << "physical name: " << ports.at(i).physName;
        qDebug() << "enumerator name: " << ports.at(i).enumName << "\n";

        // Add port friendly name to COM Ports ComboBox
        this->ui->COMPortComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
    }
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::setConnectionPushButtonText(const QString &text) {
    ui->connectionPushButton->setText(text);
}

void ConnectionDialog::on_connectionPushButton_toggled(bool checked)
{
    Mole *mole = Mole::getInstance();
    if (checked) {
        mole->open("COM1");
        ui->connectionPushButton->setText(tr("Disconnect"));
    }
    else {
        mole->close();
        ui->connectionPushButton->setText(tr("Connect"));
    }
}
