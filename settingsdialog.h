#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QMessageBox>
#include <QDialog>
#include "mole.h"
#include "qextserialenumerator.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
private:
    Ui::SettingsDialog *ui;

signals:

private slots:
    void on_buttonBox_accepted();
    void on_softwareSynchronizationRadioButton_clicked();
    void on_ExternalSynchronizationRadioButton_clicked();
    void on_toggleConnectionPushButton_toggled(bool checked);
};

#endif // SETTINGSDIALOG_H
