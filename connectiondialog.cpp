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
    QString portName = this->ui->COMPortComboBox->itemData(this->ui->COMPortComboBox->currentIndex()).toString();
    std::string str = portName.toStdString();
    const char *portString = str.c_str();
    qDebug() << "connect to: " << portString;

    Mole *mole = Mole::getInstance();
    if (checked) {
        mole->open(portString);
        mole->getHostInfo();
        mole->hostMountAll();
        ui->connectionPushButton->setText(tr("Disconnect"));
    }
    else {
        mole->hostUnmount();
        mole->close();
        ui->connectionPushButton->setText(tr("Connect"));
    }
}
