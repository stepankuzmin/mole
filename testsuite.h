#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QDebug>
#include <QDialog>
#include <QMessageBox>

#include "mole.h"

namespace Ui {
class TestSuite;
}

class TestSuite : public QDialog
{
    Q_OBJECT
    
public:
    explicit TestSuite(QWidget *parent = 0);
    ~TestSuite();
    
private slots:
    void on_runTestsPushButton_clicked();

private:
    Ui::TestSuite *ui;

signals:
    void showSettingsDialog();
};

#endif // TESTSUITE_H
