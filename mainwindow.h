#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultiMap>
#include <QList>
#include <QVector>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_scale_engine.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>

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
    QVector< QVector<QwtPlot*> > plots;
    QVector< QVector<QwtPlotCurve*> > curves;

signals:
    void showSettingsDialog();
    void showTestSuite();

public slots:
    void setConnectionState(bool isConnected);
    void setModulesMode(me_mole_module_mode modulesMode);
    void setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization);
    void plotData(uint8 moduleIndex, uint8 channelIndex, uint16 size,
                  QVector<double> samples, QVector<double> data);

private slots:
    void on_actionSettings_triggered();
    void on_actionTest_suite_triggered();
    void on_getDataPushButton_clicked();
};

#endif // MAINWINDOW_H
