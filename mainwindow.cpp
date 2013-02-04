#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // Destroy mole
    Mole *mole = Mole::getInstance();
    mole->~Mole();
}

///////////////////
// public slots //
///////////////////

void MainWindow::setConnectionState(bool isConnected) {
    Mole *mole = Mole::getInstance();

    if (isConnected) {
        // Create plots
        QVector< QVector<QwtPlot*> > plots(mole->getModuleCount(),
                                           QVector<QwtPlot*>(mole->getChannelCount()));
        // Create curves
        QVector< QVector<QwtPlotCurve*> > curves(mole->getModuleCount(),
                                                 QVector<QwtPlotCurve*>(mole->getChannelCount()));

        for (int i = 0; i < plots.size(); ++i) {
            for (int j = 0; j < plots.at(i).size(); ++j) {
                plots[i][j] = new QwtPlot();
                plots[i][j]->setAutoFillBackground(true);
                plots[i][j]->setPalette(Qt::black);
                //plots[i][j]->enableAxis(QwtPlot::yLeft, false);
                //plots[i][j]->enableAxis(QwtPlot::xBottom, false);
                plots[i][j]->setAxisAutoScale(QwtPlot::xBottom, true);
                plots[i][j]->setAxisAutoScale(QwtPlot::yLeft, true);
                (void) new QwtPlotPanner(plots[i][j]->canvas());
                (void) new QwtPlotMagnifier(plots[i][j]->canvas());
                ui->plotsLayout->addWidget(plots[i][j]);
            }
        }

        this->plots = plots;
        this->curves = curves;

        ui->connectionStateLabel->setText(tr("Connected"));
    }
    else {
        // Remove plots
        if (ui->plotsLayout->layout() != NULL) {
            QLayoutItem* item;
            while ((item = ui->plotsLayout->layout()->takeAt(0)) != NULL) {
                delete item->widget();
                delete item;
            }
        }

        plots.clear();
        curves.clear();

        ui->connectionStateLabel->setText(tr("Disconnected"));
    }
}

void MainWindow::setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization) {
    QString label;

    switch (conversionSynchronization) {
        case ME_MCS_COUNT:      label = tr("ME_MCS_COUNT"); break;
        case ME_MCS_SOFT:       label = tr("Software"); break;
        case ME_MCS_EXTERNAL:   label = tr("External"); break;
    }

    ui->conversionSynchronizationLabel->setText(label);
}

/*
 * Plot data
 * @param uint8 moduleIndex
 * @param uint8 channelIndex
 * @param uint16 size
 * @param QVector<double> samples
 * @param QVector<double> data
 */
void MainWindow::plotData(uint8 moduleIndex, uint8 channelIndex, uint16 size,
                          QVector<double> samples, QVector<double> data) {
    plots[moduleIndex][channelIndex]->detachItems();
    plots[moduleIndex][channelIndex]->replot();

    // Set data
    curves[moduleIndex][channelIndex] = new QwtPlotCurve();
    curves[moduleIndex][channelIndex]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curves[moduleIndex][channelIndex]->setPen(QPen(Qt::red));
    curves[moduleIndex][channelIndex]->setSamples(samples, data);
    curves[moduleIndex][channelIndex]->attach(plots[moduleIndex][channelIndex]);

    plots[moduleIndex][channelIndex]->replot();
}

///////////////////
// private slots //
///////////////////

void MainWindow::on_actionSettings_triggered()
{
    emit showSettingsDialog();
}

void MainWindow::on_actionTest_suite_triggered()
{
    emit showTestSuite();
}
