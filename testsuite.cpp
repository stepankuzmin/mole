#include "testsuite.h"
#include "ui_testsuite.h"

TestSuite::TestSuite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestSuite)
{
    ui->setupUi(this);
}

TestSuite::~TestSuite()
{
    delete ui;
}

void TestSuite::on_runTestsPushButton_clicked()
{
    Mole *mole = Mole::getInstance();

    if (mole->isConnected()) {
        if (ui->testGainCoefficientsGroupBox->isChecked()) {
            if (ui->testGainCoefficientsSyncRadioButton->isChecked()) {
                qDebug() << "run gain coefficients synch";
            }

            if (ui->testGainCoefficientsAsyncRadioButton->isChecked()) {
                qDebug() << "run gain coefficients asynch";
            }
        }

        if (ui->testNoiseFloorGroupBox->isChecked()) {
            if (ui->testNoiseFloorSyncRadioButton->isChecked()) {
                qDebug() << "run noise floor synch";
            }

            if (ui->testNoiseFloorAsyncRadioButton->isChecked()) {
                qDebug() << "run noise floor asynch";
            }
        }
    }
    else {
        QMessageBox messageBox;
        QPushButton *settingsButton = messageBox.addButton(tr("Settings"), QMessageBox::ActionRole);
        messageBox.setStandardButtons(QMessageBox::Cancel);
        messageBox.setIcon(QMessageBox::Warning);
        messageBox.setText(tr("Not connected"));
        messageBox.setInformativeText(tr("Switch to settings?"));

        messageBox.exec();
        if (messageBox.clickedButton() == settingsButton) {
            this->close();
            emit showSettingsDialog();
        }
    }
}
