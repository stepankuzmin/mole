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

/*
 * Enable plots
 */
void MainWindow::enablePlots(int moduleCount, int channelCount) {
    QVector< QVector<QwtPlot*> >            plots(moduleCount, QVector<QwtPlot*>(channelCount));

    QVector< QVector<QwtPlotCurve*> >       curves(moduleCount,
                                                   QVector<QwtPlotCurve*>(channelCount));
    QVector< QVector< QVector<double> > >   data(moduleCount,
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
            ui->plotsLayout->addWidget(plots[moduleIndex][channelIndex]);

            QVector<double> data[moduleIndex][channelIndex];
        }
    }

    this->data = data;
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
    /*
    this->continousData[moduleIndex][channelIndex] += data;

    int size = this->continousData[moduleIndex][channelIndex].size();
    QVector<double> continousSamples;
    for (int i=0; i<size; i++)
        continousSamples << i;
    */

    plots[moduleIndex][channelIndex]->detachItems();
    plots[moduleIndex][channelIndex]->replot();

    // Set data
    curves[moduleIndex][channelIndex] = new QwtPlotCurve();
    curves[moduleIndex][channelIndex]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curves[moduleIndex][channelIndex]->setPen(QPen(Qt::red));
    //curves[moduleIndex][channelIndex]->setSamples(continousSamples, this->continousData[moduleIndex][channelIndex]);
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
    mole->getData();
}

void MainWindow::on_actionOpen_triggered()
{
    if (this->isPlotsEnabled) {
        disablePlots();
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("SD3 (*.sd3)"));
    qDebug() << "Reading " << fileName;

    QVector< QVector< QVector<double> > > data;
    QVector< QVector< QVector<double> > > samples;

    FILE *file;
    file = fopen(fileName.toStdString().c_str(), "rb");

    // @TODO: private structure to store sd3 data
    int channelCount = 3;
    int version;
    int datarate;
    int samples_count;
    int mode;
    int address;
    int date;
    int time;
    int x_source;
    int y_source;
    int h_source;

    int x_state;
    int y_state;
    int z_state;
    int x_incl;
    int y_incl;
    int z_incl;
    int x;
    int y;
    int h;

    int size = sizeof(int);
    int sizeOfFloat = sizeof(float);

    fread(&version,         size, 1, file);
    fread(&datarate,        size, 1, file);
    fread(&samples_count,   size, 1, file);
    fread(&mode,            size, 1, file);
    fread(&address,         size, 1, file);
    fread(&date,            size, 1, file);
    fread(&time,            size, 1, file);
    fread(&x_source,        size, 1, file);
    fread(&y_source,        size, 1, file);
    fread(&h_source,        size, 1, file);

    qDebug() << "=== HEADER ===";
    qDebug() << "version: "  << version;
    qDebug() << "datarate: " << datarate;
    qDebug() << "samples: "  << samples_count;
    qDebug() << "mode: "     << mode;
    qDebug() << "address: "  << address;
    qDebug() << "date: "     << date;
    qDebug() << "time: "     << time;
    qDebug() << "x_source: " << x_source;
    qDebug() << "y_source: " << y_source;
    qDebug() << "h_source: " << h_source;

    float sample;
    float X[samples_count], Y[samples_count], Z[samples_count];

    int moduleIndex = 0;
    while (!feof(file)) {
      // Record
      fread(&x_state, size, 1, file);
      fread(&y_state, size, 1, file);
      fread(&z_state, size, 1, file);

      fread(&x_incl, size, 1, file);
      fread(&y_incl, size, 1, file);
      fread(&z_incl, size, 1, file);

      fread(&x, size, 1, file);
      fread(&y, size, 1, file);
      fread(&h, size, 1, file);

      fseek(file, size, SEEK_CUR); // Skip reserved field

      // Rad record
      QVector< QVector<double> > dataRecord(channelCount);
      QVector< QVector<double> > samplesRecord(channelCount);
      for (int channelIndex=0; channelIndex<channelCount; channelIndex++) {
          for (int i=0; i<samples_count; i++) {
              fread(&sample, sizeOfFloat, 1, file);
              dataRecord[channelIndex] << sample;
              samplesRecord[channelIndex] << i;
          }
      }
      data << dataRecord;
      samples << samplesRecord;
      moduleIndex++;
    }
    fclose(file);
    int moduleCount = moduleIndex;

    // Plot data
    enablePlots(moduleCount, channelCount);
    for (moduleIndex=0; moduleIndex<moduleCount; moduleIndex++)
        for (int channelIndex=0; channelIndex<channelCount; channelIndex++) {
            plotData(moduleIndex, channelIndex,
                     samples[moduleIndex][channelIndex], data[moduleIndex][channelIndex]);
        }
}
