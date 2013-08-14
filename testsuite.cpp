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
        if (ui->testGainCoefficientsCheckBox->isChecked()) {
            ui->testGainCoefficientsLabel->setText(tr("In progress..."));
            if (mole->testSuiteGainCoefficients() > 0) {
                ui->testGainCoefficientsLabel->setText("<font color=\"Red\">Failed</font>");
                qDebug() << "[Error] Gain coefficients test failed";
            }
            else {
                ui->testGainCoefficientsLabel->setText("<font color=\"Green\">Succeed</font>");
                qDebug() << "[Success] Gain coefficients test succeed";
            }
        }
        if (ui->testNoiseFloorCheckBox->isChecked()) {
            ui->testNoiseFloorLabel->setText(tr("In progress..."));
            if (mole->testSuiteGainCoefficients() > 0) {
                ui->testNoiseFloorLabel->setText("<font color=\"Red\">Failed</font>");
                qDebug() << "[Error] Noise floor test failed";
            }
            else {
                ui->testNoiseFloorLabel->setText("<font color=\"Green\">Succeed</font>");
                qDebug() << "[Success] Noise floor test succeed";
            }
        }
        if (ui->testTotalHarmonicDistortionCheckBox->isChecked()) {
            ui->testTotalHarmonicDistortionLabel->setText(tr("In progress..."));
            if (mole->testTotalHarmonicDistortion() > 0) {
                ui->testTotalHarmonicDistortionLabel->setText("<font color=\"Red\">Failed</font>");
                qDebug() << "[Error] Total harmonic distortion test failed";
            }
            else {
                ui->testTotalHarmonicDistortionLabel->setText("<font color=\"Green\">Succeed</font>");
                qDebug() << "[Success] Total harmonic distortion test succeed";
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
