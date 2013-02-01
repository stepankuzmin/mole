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
                if (mole->testSuiteGainCoefficients(true) > 0)
                    qDebug() << "[Error] sync gain coefficients test failured";
                else
                    qDebug() << "[Success] sync gain coefficients succseed";
            }

            if (ui->testGainCoefficientsAsyncRadioButton->isChecked()) {
                qDebug() << "run gain coefficients asynch";
                if (mole->testSuiteGainCoefficients(false) > 0)
                    qDebug() << "[Error] async gain coefficients test failured";
                else
                    qDebug() << "[Success] async gain coefficients succseed";
            }
        }

        if (ui->testNoiseFloorGroupBox->isChecked()) {
            if (ui->testNoiseFloorSyncRadioButton->isChecked()) {
                qDebug() << "run noise floor synch";
                if (mole->testSuiteNoiseFloor(true) > 0)
                    qDebug() << "[Error] sync noise floor test failured";
                else
                    qDebug() << "[Success] sync noise floor succseed";
            }

            if (ui->testNoiseFloorAsyncRadioButton->isChecked()) {
                qDebug() << "run noise floor asynch";
                if (mole->testSuiteNoiseFloor(false) > 0)
                    qDebug() << "[Error] async noise floor test failured";
                else
                    qDebug() << "[Success] async noise floor succseed";
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
