#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();
    
public slots:
    void setConnectionPushButtonText(const QString &text);

private slots:
    void on_connectionPushButton_toggled(bool checked);

private:
    Ui::ConnectionDialog *ui;
};

#endif // CONNECTIONDIALOG_H
