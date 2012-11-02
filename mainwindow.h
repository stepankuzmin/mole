#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mole.h"
#include <QMainWindow>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
signals:
    void showConnectionDialog();
    void showRegistrationSettingsDialog();

public slots:
    void setStatusBarText(const QString text);

private slots:
    void on_actionConnection_triggered();
    void on_actionRegistration_triggered();

    void on_actionTestGainCoefficientsSync_triggered();

    void on_actionTestGainCoefficientsAsync_triggered();

    void on_actionTestNoiseFloorSync_triggered();

    void on_connectPushButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QwtPlot *plot;
};

#endif // MAINWINDOW_H
