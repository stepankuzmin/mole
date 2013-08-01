#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QMessageBox>
#include "qwt_plot_grid.h"
#include "qextserialenumerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // List all available COM ports
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i = 0; i < ports.size(); i++)
        ui->COMPortsComboBox->addItem(ports.at(i).friendName,
                                      QVariant(ports.at(i).portName));

    // Modules modes
    ui->modulesModeComboBox->addItem("Seismic",         QVariant(ME_MMM_SEISMIC));
    ui->modulesModeComboBox->addItem("Inclinometer",    QVariant(ME_MMM_INCLINOMETER));
    ui->modulesModeComboBox->addItem("Sleep",           QVariant(ME_MMM_SLEEP));
    ui->modulesModeComboBox->addItem("Count",           QVariant(ME_MMM_COUNT));

    // Synchronization
    ui->synchronizationComboBox->addItem("Software",    QVariant(ME_MCS_SOFT));
    ui->synchronizationComboBox->addItem("External",    QVariant(ME_MCS_EXTERNAL));
    ui->synchronizationComboBox->addItem("Count",       QVariant(ME_MCS_COUNT));

    // Datarate items
    ui->datarateComboBox->addItem("250", QVariant(ME_MMD_250));
    ui->datarateComboBox->addItem("500", QVariant(ME_MMD_500));
    ui->datarateComboBox->addItem("1000", QVariant(ME_MMD_1000));
    ui->datarateComboBox->addItem("2000", QVariant(ME_MMD_2000));
    ui->datarateComboBox->addItem("4000", QVariant(ME_MMD_4000));
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
            plots[moduleIndex][channelIndex]->setPalette(Qt::white);
            plots[moduleIndex][channelIndex]->setAxisAutoScale(QwtPlot::xBottom, true);
            plots[moduleIndex][channelIndex]->setAxisAutoScale(QwtPlot::yLeft, true);
            plots[moduleIndex][channelIndex]->enableAxis(QwtPlot::xBottom, true);
            plots[moduleIndex][channelIndex]->enableAxis(QwtPlot::yLeft, true);
            plots[moduleIndex][channelIndex]->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating, true);
            (void) new QwtPlotPanner(plots[moduleIndex][channelIndex]->canvas());
            (void) new QwtPlotMagnifier(plots[moduleIndex][channelIndex]->canvas());
            //ui->plotsLayout->layout()->addWidget(plots[moduleIndex][channelIndex], moduleIndex, channelIndex)

            QwtPlotGrid *grid = new QwtPlotGrid;
            grid->enableXMin(true);
            grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
            grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
            grid->attach(plots[moduleIndex][channelIndex]);

            ui->plotsLayout->addWidget(plots[moduleIndex][channelIndex], moduleIndex, channelIndex);

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

void MainWindow::plotMData(MData mdata) {
    for (int moduleIndex = 0; moduleIndex < mdata.size(); ++moduleIndex) {
        for (int channelIndex = 0; channelIndex < mdata[moduleIndex].size(); ++channelIndex) {
            this->plots[moduleIndex][channelIndex]->detachItems();
            //this->plots[moduleIndex][channelIndex]->replot();

            curves[moduleIndex][channelIndex] = new QwtPlotCurve();
            curves[moduleIndex][channelIndex]->setPen(QPen(Qt::black));
            curves[moduleIndex][channelIndex]->setBrush(Qt::black);
            curves[moduleIndex][channelIndex]->setSamples(mdata[moduleIndex][channelIndex]);
            curves[moduleIndex][channelIndex]->attach(this->plots[moduleIndex][channelIndex]);

            QwtPlotGrid *grid = new QwtPlotGrid;
            grid->enableXMin(true);
            grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
            grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
            grid->attach(this->plots[moduleIndex][channelIndex]);

            this->plots[moduleIndex][channelIndex]->replot();
        }
    }
}

void MainWindow::setConnectionState(bool isConnected) {
    Mole *mole = Mole::getInstance();
    int moduleCount = mole->getModuleCount();
    int channelCount = mole->getChannelCount();

    if (isConnected) {
        disablePlots();
        enablePlots(moduleCount, channelCount);
        //ui->connectionStateLabel->setText(tr("Connection: Connected"));
    }
    else {
        //disablePlots();
        //ui->connectionStateLabel->setText(tr("Connection: Disconnected"));
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

    //ui->modulesModeLabel->setText(tr("Modules mode: %1").arg(text));
}

void MainWindow::setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization) {
    QString text;

    switch (conversionSynchronization) {
        case ME_MCS_COUNT:      text = tr("ME_MCS_COUNT"); break;
        case ME_MCS_SOFT:       text = tr("Software"); break;
        case ME_MCS_EXTERNAL:   text = tr("External"); break;
    }

    //ui->conversionSynchronizationLabel->setText(tr("Conversion synchronization: %1").arg(text));
}
void MainWindow::setSamplesSize(uint16 samplesSize) {
    QString text;

    //ui->samplesSizeLabel->setText(tr("Samples size: %1").arg(samplesSize));
}

void MainWindow::setDatarate(me_mole_module_datarate datarate) {
    QString text;
    switch (datarate) {
        case ME_MMD_250: text = "250 ms"; break;
        case ME_MMD_500: text = "500 ms"; break;
        case ME_MMD_1000: text = "1000 ms"; break;
        case ME_MMD_2000: text = "2000 ms"; break;
        case ME_MMD_4000: text = "4000 ms"; break;
    }

    //ui->datarateLabel->setText(tr("Datarate: %1").arg(text));
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

    double *s = samples.data();
    for (int i = 0; i < samples.size(); ++i) {
        s[i] = (s[i]*250)/1000000;
    }

    this->samples[moduleIndex][channelIndex] = samples;
    this->data[moduleIndex][channelIndex] = data;

    this->plots[moduleIndex][channelIndex]->detachItems();
    this->plots[moduleIndex][channelIndex]->replot();

    // Set data
    curves[moduleIndex][channelIndex] = new QwtPlotCurve();
    //curves[moduleIndex][channelIndex]->setRenderHint(QwtPlotItem::RenderAntialiased);
    curves[moduleIndex][channelIndex]->setPen(QPen(Qt::black));
    curves[moduleIndex][channelIndex]->setBrush(Qt::black);
    curves[moduleIndex][channelIndex]->setSamples(samples, data);
    curves[moduleIndex][channelIndex]->attach(this->plots[moduleIndex][channelIndex]);

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->attach(this->plots[moduleIndex][channelIndex]);

    this->plots[moduleIndex][channelIndex]->replot();
}

void MainWindow::plotSD3() {
    plotSD3(this->sd3_file);
}

void MainWindow::plotSD3(sd3_file_t sd3_file) {
    int channelCount = 3;
    int moduleCount = sd3_file.records.size()-1; // @TODO: temporary solution to remove last void record
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

/*
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
*/

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("SD3 (*.sd3)"));
    sd3_file_t sd3_file = SD3::read(fileName.toStdString().c_str());
    this->sd3_file = sd3_file;
    qDebug("open, size=%d", sd3_file.records.size());
    plotSD3(sd3_file);

    // Display SD3 information
    /*
    ui->plainTextEdit->clear();
    ui->plainTextEdit->textCursor().insertText(tr("Version: %1\n").arg(this->sd3_file.version));
    ui->plainTextEdit->textCursor().insertText(tr("Datarate: %1\n").arg(this->sd3_file.datarate));
    ui->plainTextEdit->textCursor().insertText(tr("Samples count: %1\n").arg(this->sd3_file.samples_count));
    ui->plainTextEdit->textCursor().insertText(tr("Mode: %1\n").arg(this->sd3_file.mode));
    ui->plainTextEdit->textCursor().insertText(tr("Address: %1\n").arg(this->sd3_file.address));
    ui->plainTextEdit->textCursor().insertText(tr("Date: %1\n").arg(this->sd3_file.date));
    ui->plainTextEdit->textCursor().insertText(tr("Time: %1\n").arg(this->sd3_file.time));
    ui->plainTextEdit->textCursor().insertText(tr("X source: %1\n").arg(this->sd3_file.x_source));
    ui->plainTextEdit->textCursor().insertText(tr("Y source: %1\n").arg(this->sd3_file.y_source));

    int moduleCount = this->sd3_file.records.size();
    for (int i=0; i<this->sd3_file.records.size(); i++) {
        ui->plainTextEdit->textCursor().insertText(tr("=== Module #%1===\n").arg(i));
        ui->plainTextEdit->textCursor().insertText(tr("X state: %1\n").arg(this->sd3_file.records.at(i).x_state));
        ui->plainTextEdit->textCursor().insertText(tr("Y state: %1\n").arg(this->sd3_file.records.at(i).y_state));
        ui->plainTextEdit->textCursor().insertText(tr("Z state: %1\n").arg(this->sd3_file.records.at(i).z_state));
        ui->plainTextEdit->textCursor().insertText(tr("X inclinometer: %1\n").arg(this->sd3_file.records.at(i).x_inclinometer));
        ui->plainTextEdit->textCursor().insertText(tr("Y inclinometer: %1\n").arg(this->sd3_file.records.at(i).y_inclinometer));
        ui->plainTextEdit->textCursor().insertText(tr("Z inclinometer: %1\n").arg(this->sd3_file.records.at(i).z_inclinometer));
        ui->plainTextEdit->textCursor().insertText(tr("X receiver: %1\n").arg(this->sd3_file.records.at(i).x_receiver));
        ui->plainTextEdit->textCursor().insertText(tr("Y receiver: %1\n").arg(this->sd3_file.records.at(i).y_receiver));
        ui->plainTextEdit->textCursor().insertText(tr("H receiver: %1\n").arg(this->sd3_file.records.at(i).h_receiver));
    }
    */
}

void MainWindow::on_actionSave_triggered()
{
    QString preferredFileName = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + ".sd3";
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save file"),
                                                    preferredFileName,
                                                    tr("SD3 (*.sd3)"));
    qDebug("save, size=%d", this->sd3_file.records.size());
    SD3::write(fileName.toStdString().c_str(), this->sd3_file); // @TODO: is success?
}

void MainWindow::on_actionDisablePlots_triggered()
{
    disablePlots();
}

void MainWindow::on_connectionPushButton_toggled(bool checked)
{
    Mole *mole = Mole::getInstance();
    if (checked) {
        QString portName = ui->COMPortsComboBox->itemData(
                    ui->COMPortsComboBox->currentIndex()).toString();
        std::string str = portName.toStdString();
        const char *portString = str.c_str();
        if (mole->connect(portString) < 0) {
            ui->connectionPushButton->setChecked(false);
            QMessageBox::critical(0, "Error", "Can't open connection.");
        }
        else { // Connected successfully
            ui->connectionPushButton->setText(tr("Disconnect"));
        }
    }
    else {
        if (mole->disconnect()) {
            ui->connectionPushButton->setText(tr("Connect"));
        }
    }
}

void MainWindow::on_startPushButton_clicked()
{
    Mole *mole = Mole::getInstance();

    int modulesMode = ui->modulesModeComboBox->itemData(
                ui->modulesModeComboBox->currentIndex()).toInt();
    switch (modulesMode) {
        case ME_MMM_SEISMIC: {
            mole->setModulesMode(ME_MMM_SEISMIC);
        } break;
        case ME_MMM_INCLINOMETER: {
            mole->setModulesMode(ME_MMM_INCLINOMETER);
        } break;
        case ME_MMM_SLEEP: {
            mole->setModulesMode(ME_MMM_SLEEP);
        } break;
        case ME_MMM_COUNT: {
            mole->setModulesMode(ME_MMM_COUNT);
        } break;
    }

    int synchronization = ui->synchronizationComboBox->itemData(
                ui->synchronizationComboBox->currentIndex()).toInt();
    switch (synchronization) {
        case ME_MCS_SOFT: {
            mole->setConversionSynchronization(ME_MCS_SOFT);
        } break;
        case ME_MCS_EXTERNAL: {
            mole->setConversionSynchronization(ME_MCS_EXTERNAL);
        } break;
        case ME_MCS_COUNT: {
            mole->setConversionSynchronization(ME_MCS_COUNT);
        } break;
    }

    uint16 samplesSize = ui->samplesComboBox->currentText().toInt();
    mole->setSamplesSize(samplesSize);

    int datarate = ui->datarateComboBox->itemData(
                ui->datarateComboBox->currentIndex()).toInt();
    switch (datarate) {
        case ME_MMD_250: {
            mole->setDatarate(ME_MMD_250);
        } break;
        case ME_MMD_500: {
            mole->setDatarate(ME_MMD_500);
        } break;
        case ME_MMD_1000: {
            mole->setDatarate(ME_MMD_1000);
        } break;
        case ME_MMD_2000: {
            mole->setDatarate(ME_MMD_2000);
        } break;
        case ME_MMD_4000: {
            mole->setDatarate(ME_MMD_4000);
        } break;
    }
    mole->getMData();
}
