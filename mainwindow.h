#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QCloseEvent>
#include <QMainWindow>
#include <QMdiSubWindow>

#include "workspace.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Workspace *activeWorkspace();
    QMdiSubWindow *findMdiChild(const QString &fileName);

private slots:
    void newFile();
    void open();
    void record();
    Workspace *createWorkspace();
};

#endif // MAINWINDOW_H
