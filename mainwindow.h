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
    void setStage(me_test_suite_stage stage);

    void plotData(uint8 moduleIndex, uint8 channelIndex,
                   uint16 size, QList<double> samples, QList<double> data);

private slots:
    void on_actionRegistration_triggered();
    void on_actionTestGainCoefficientsSync_triggered();
    void on_actionTestGainCoefficientsAsync_triggered();
    void on_actionTestNoiseFloorSync_triggered();
    void on_connectPushButton_toggled(bool checked);

    void on_startTestsPushButton_clicked();

    void on_actionClear_plots_triggered();

    void on_actionTestTotalHarmonicDistortionSync_triggered();

    void on_actionTestZeroShiftSync_triggered();

    void on_actionTestCommonModeRejectionSync_triggered();

private:
    Ui::MainWindow *ui;
    QwtPlot *plot[6][3]; // 6 геофонов по три канала
    QwtPlotCurve *curve[6][3];

    QVector< QVector<QwtPlot*> > *vplot;
};

#endif // MAINWINDOW_H
