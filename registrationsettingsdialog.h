#ifndef REGISTRATIONSETTINGSDIALOG_H
#define REGISTRATIONSETTINGSDIALOG_H

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
    
private:
    Ui::RegistrationSettingsDialog *ui;
};

#endif // REGISTRATIONSETTINGSDIALOG_H
