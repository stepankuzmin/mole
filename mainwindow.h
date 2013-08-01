#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>

#include <QPointF>

#include <QMainWindow>
#include <QMultiMap>
#include <QList>
#include <QVector>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QScrollArea>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_scale_engine.h"
#include <qwt_plot_canvas.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>

#include "sd3.h"
#include "mole.h"

typedef QVector< QVector<QwtPlot*> >        MPlot;
typedef QVector< QVector<QwtPlotCurve*> >   MCurve;

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
    sd3_file_t sd3_file;
    Ui::MainWindow *ui;

    QVector< QVector< QVector<double> > > data;
    QVector< QVector< QVector<double> > > samples;

    QVector< QVector<QwtPlot*> > plots;
    QVector< QVector<QwtPlotCurve*> > curves;

    bool isPlotsEnabled;

signals:
    void showSettingsDialog();
    void showTestSuite();

public slots:
    void enablePlots(int moduleCount, int channelCount);
    void disablePlots();
    void setConnectionState(bool isConnected);
    void setModulesMode(me_mole_module_mode modulesMode);
    void setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization);
    void setSamplesSize(uint16 samplesSize);
    void setDatarate(me_mole_module_datarate datarate);
    void plotMData(MData mdata);

    void plotSD3();
    void plotSD3(sd3_file_t sd3_file);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionDisablePlots_triggered();
    void on_connectionPushButton_toggled(bool checked);
    void on_startPushButton_clicked();
    void on_actionTest_suite_triggered();
};

#endif // MAINWINDOW_H
