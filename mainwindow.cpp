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
    // Destroy mole
    Mole *mole = Mole::getInstance();
    mole->~Mole();

    delete ui;
}

///////////////////
// public slots  //
///////////////////

/*
 * Enable plots
 */
void MainWindow::enablePlots(int moduleCount, int channelCount) {
    QVector< QVector<QwtPlot*> >            plots(moduleCount, QVector<QwtPlot*>(channelCount));
    QVector< QVector<QwtPlotCurve*> >       curves(moduleCount, QVector<QwtPlotCurve*>(channelCount));
    QVector< QVector< QVector<double> > >   data(moduleCount,
                                                 QVector< QVector<double> >(channelCount));
    QVector< QVector< QVector<double> > >   samples(moduleCount,
                                                 QVector< QVector<double> >(channelCount));

    for (int moduleIndex = 0; moduleIndex < plots.size(); ++moduleIndex) {
        for (int channelIndex = 0; channelIndex < plots.at(moduleIndex).size(); ++channelIndex) {
            plots[moduleIndex][channelIndex] = new QwtPlot();
            plots[moduleIndex][channelIndex]->setAutoFillBackground(true);
            plots[moduleIndex][channelIndex]->setPalette(Qt::black);
            plots[moduleIndex][channelIndex]->setAxisAutoScale(QwtPlot::xBottom, true);
            plots[moduleIndex][channelIndex]->setAxisAutoScale(QwtPlot::yLeft, true);
            plots[moduleIndex][channelIndex]->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating, true);
            //(void) new QwtPlotPanner(plots[moduleIndex][channelIndex]->canvas());
            //(void) new QwtPlotMagnifier(plots[moduleIndex][channelIndex]->canvas());
            ui->plotsLayout->layout()->addWidget(plots[moduleIndex][channelIndex]);

            QVector<double> data[moduleIndex][channelIndex];
            QVector<double> samples[moduleIndex][channelIndex];
        }
    }

    this->data = data;
    this->samples = samples;
    this->plots = plots;
    this->curves = curves;
    this->isPlotsEnabled = true;
}

/*
 * Disable plots
 */
void MainWindow::disablePlots() {
    if (ui->plotsLayout->layout() != NULL) {
        QLayoutItem* item;
        while ((item = ui->plotsLayout->layout()->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
    }
    this->data.clear();
    this->samples.clear();
    this->plots.clear();
    this->curves.clear();
    this->isPlotsEnabled = false;
}

void MainWindow::setConnectionState(bool isConnected) {
    Mole *mole = Mole::getInstance();
    int moduleCount = mole->getModuleCount();
    int channelCount = mole->getChannelCount();

    if (isConnected) {
        disablePlots();
        enablePlots(moduleCount, channelCount);
        ui->connectionStateLabel->setText(tr("Connection: Connected"));
    }
    else {
        disablePlots();
        ui->connectionStateLabel->setText(tr("Connection: Disconnected"));
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

    ui->modulesModeLabel->setText(tr("Modules mode: %1").arg(text));
}

void MainWindow::setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization) {
    QString text;

    switch (conversionSynchronization) {
        case ME_MCS_COUNT:      text = tr("ME_MCS_COUNT"); break;
        case ME_MCS_SOFT:       text = tr("Software"); break;
        case ME_MCS_EXTERNAL:   text = tr("External"); break;
    }

    ui->conversionSynchronizationLabel->setText(tr("Conversion synchronization: %1").arg(text));
}
void MainWindow::setSamplesSize(uint16 samplesSize) {
    QString text;

    ui->samplesSizeLabel->setText(tr("Samples size: %1").arg(samplesSize));
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

    this->samples[moduleIndex][channelIndex] = samples;
    this->data[moduleIndex][channelIndex] = data;

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

void MainWindow::plotSD3() {
    plotSD3(this->sd3_file);
}

void MainWindow::plotSD3(sd3_file_t sd3_file) {
    int channelCount = 3;
    int moduleCount = sd3_file.records.size();
    QVector<double> samples;
    for (int i=0; i<sd3_file.samples_count; i++) {
        samples << i;
    }

    disablePlots();
    enablePlots(moduleCount, channelCount);

    for (int moduleIndex=0; moduleIndex<moduleCount; ++moduleIndex) {
        plotData(moduleIndex, 0, samples, sd3_file.records.at(moduleIndex).x);
        plotData(moduleIndex, 1, samples, sd3_file.records.at(moduleIndex).y);
        plotData(moduleIndex, 2, samples, sd3_file.records.at(moduleIndex).z);
    }
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

void MainWindow::on_toggleTimerPushButton_toggled(bool checked)
{
    Mole *mole = Mole::getInstance();
    if (checked) {
        mole->startTimer(1000); // How do I choose time interval?
    }
    else {
        mole->stopTimer();
    }
}

void MainWindow::on_getDataPushButton_clicked()
{
    Mole *mole = Mole::getInstance();
    this->sd3_file = mole->getData(); // PlotData;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("SD3 (*.sd3)"));
    sd3_file_t sd3_file = SD3::read(fileName.toStdString().c_str());
    this->sd3_file = sd3_file;
    qDebug("open, size=%d", sd3_file.records.size());
    plotSD3(sd3_file);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "", tr("SD3 (*.sd3)"));
    qDebug("save, size=%d", this->sd3_file.records.size());
    SD3::write(fileName.toStdString().c_str(), this->sd3_file); // @TODO: is success?
}

void MainWindow::on_actionDisablePlots_triggered()
{
    disablePlots();
}
