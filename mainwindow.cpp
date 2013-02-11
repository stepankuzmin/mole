#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    SD3 *file = new SD3(this);

    qDebug() << "version: " << file->getVersion();
    qDebug() << "datarate: " << file->getDatarate();
    qDebug() << "samples count:" << file->getSamplesCount();
    */
}

MainWindow::~MainWindow()
{
    // Destroy mole
    Mole *mole = Mole::getInstance();
    mole->~Mole();

    delete ui;
}

///////////////////
// public slots  //
///////////////////

void MainWindow::setConnectionState(bool isConnected) {
    Mole *mole = Mole::getInstance();
    int moduleCount = mole->getModuleCount();
    int channelCount = mole->getChannelCount();

    if (isConnected) {
        // Create plots
        QVector< QVector<QwtPlot*> > plots(moduleCount, QVector<QwtPlot*>(channelCount));

        // Create curves
        QVector< QVector<QwtPlotCurve*> > curves(moduleCount, QVector<QwtPlotCurve*>(channelCount));

        // Initialize continous data vectors
        QVector< QVector< QVector<double> > > continousData(moduleCount, QVector< QVector<double> >(channelCount));

        // @TODO: change i and j to moduleIndex and channelIndex
        for (int i = 0; i < plots.size(); ++i) {
            for (int j = 0; j < plots.at(i).size(); ++j) {
                plots[i][j] = new QwtPlot();
                plots[i][j]->setAutoFillBackground(true);
                plots[i][j]->setPalette(Qt::black);
                plots[i][j]->setAxisAutoScale(QwtPlot::xBottom, true);
                plots[i][j]->setAxisAutoScale(QwtPlot::yLeft, true);
                plots[i][j]->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating, true);
                (void) new QwtPlotPanner(plots[i][j]->canvas());
                (void) new QwtPlotMagnifier(plots[i][j]->canvas());
                ui->plotsLayout->addWidget(plots[i][j]);

                QVector<double> continousData[i][j];
            }
        }

        this->plots = plots;
        this->curves = curves;
        this->continousData = continousData;

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

void MainWindow::setModulesMode(me_mole_module_mode modulesMode) {
    QString text;

    switch (modulesMode) {
        case ME_MMM_COUNT:          text = tr("ME_MMM_COUNT"); break;
        case ME_MMM_SLEEP:          text = tr("Sleep"); break;
        case ME_MMM_SEISMIC:        text = tr("Seismic"); break;
        case ME_MMM_INCLINOMETER:   text = tr("Inclinometer"); break;
    }

    ui->modulesModeLabel->setText(text);
}

void MainWindow::setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization) {
    QString text;

    switch (conversionSynchronization) {
        case ME_MCS_COUNT:      text = tr("ME_MCS_COUNT"); break;
        case ME_MCS_SOFT:       text = tr("Software"); break;
        case ME_MCS_EXTERNAL:   text = tr("External"); break;
    }

    ui->conversionSynchronizationLabel->setText(text);
}

/*
 * Plot data
 * @param uint8 moduleIndex
 * @param uint8 channelIndex
 * @param uint16 size
 * @param QVector<double> samples
 * @param QVector<double> data
 */
void MainWindow::plotData(uint8 moduleIndex, uint8 channelIndex,
                          QVector<double> samples, QVector<double> data) {
    this->continousData[moduleIndex][channelIndex] += data;

    int size = this->continousData[moduleIndex][channelIndex].size();
    QVector<double> continousSamples;
    for (int i=0; i<size; i++)
        continousSamples << i;

    plots[moduleIndex][channelIndex]->detachItems();
    plots[moduleIndex][channelIndex]->replot();

    // Set data
    curves[moduleIndex][channelIndex] = new QwtPlotCurve();
    curves[moduleIndex][channelIndex]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curves[moduleIndex][channelIndex]->setPen(QPen(Qt::red));
    curves[moduleIndex][channelIndex]->setSamples(continousSamples, this->continousData[moduleIndex][channelIndex]);
    //curves[moduleIndex][channelIndex]->setSamples(samples, data);
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

void MainWindow::on_getDataPushButton_clicked()
{
    /*
    Mole *mole = Mole::getInstance();

    uint16 samples;
    samples = ui->lineEdit->text().toInt();

    if (mole->startConversion()) {
        mole->getSeismicData(samples);
        mole->stopConversion();
    }
    */
}

void MainWindow::on_toggleTimerPushButton_toggled(bool checked)
{
    // @TODO: move timer to mole!
    /*
    if (checked) {
        this->timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(on_getDataPushButton_clicked()));
        timer->start(1000);
    }
    else {
        this->timer->stop();
    }
    */

    Mole *mole = Mole::getInstance();
    if (checked) {
        uint16 samplesSize = ui->lineEdit->text().toInt();
        mole->setSamplesSize(samplesSize);
        mole->startTimer(1000);
    }
    else {
        mole->stopTimer();
    }
}
