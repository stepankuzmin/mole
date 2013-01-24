#ifndef REGISTRATIONSETTINGSDIALOG_H
#define REGISTRATIONSETTINGSDIALOG_H

#include "mole.h"
#include <QDialog>

namespace Ui {
class RegistrationSettingsDialog;
}

class RegistrationSettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegistrationSettingsDialog(QWidget *parent = 0);
    ~RegistrationSettingsDialog();
    
private slots:
    void on_buttonBox_accepted();

    void on_setModuleModePushButton_clicked();

    void on_setDataratePushButton_clicked();

    void on_setTestGeneratorModePushButton_clicked();

    void on_setInputModePushButton_clicked();

private:
    Ui::RegistrationSettingsDialog *ui;

signals:
    void registrationModeChanged(QString registrationMode);
    void moduleDatarateChanged(int moduleDatarate);
};

#endif // REGISTRATIONSETTINGSDIALOG_H
