#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mole.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

signals:
    void showSettingsDialog();
    void showTestSuite();

public slots:
    void setConnectionState(bool isConnected);
    void setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization);

private slots:
    void on_actionSettings_triggered();
    void on_actionTest_suite_triggered();
};

#endif // MAINWINDOW_H
