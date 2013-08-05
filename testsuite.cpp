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
    bool isSync = true;

    if (mole->isConnected()) {
        if (ui->testGainCoefficientsCheckBox->isChecked()) {
            if (mole->testSuiteGainCoefficients(isSync) > 0) {
                ui->testGainCoefficientsLabel->setText("<font color=\"Red\">Failed</font>");
                qDebug() << "[Error] Gain coefficients test failed";
            }
            else {
                ui->testGainCoefficientsLabel->setText("<font color=\"Green\">Succeed</font>");
                qDebug() << "[Success] Gain coefficients test succeed";
            }
        }
        if (ui->testNoiseFloorCheckBox->isChecked()) {
            if (mole->testSuiteGainCoefficients(isSync) > 0) {
                ui->testNoiseFloorLabel->setText("<font color=\"Red\">Failed</font>");
                qDebug() << "[Error] Noise floor test failed";
            }
            else {
                ui->testNoiseFloorLabel->setText("<font color=\"Green\">Succeed</font>");
                qDebug() << "[Success] Noise floor test succeed";
            }
        }
    }
    else {
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setStandardButtons(QMessageBox::Ok);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setText(tr("Mole is not connected"));
        messageBox->setInformativeText(tr("Please connect first"));

        if (messageBox->exec() == QMessageBox::Ok) {
            this->close();
        }
    }
}
