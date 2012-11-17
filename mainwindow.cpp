#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QList>
#include <QVector>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QProgressBar>
#include "qextserialenumerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getConversationData()));

    assistant = new Assistant();

    ui->progressBar->setTextVisible(false);
    ui->progressBar->setRange(0, 5);

    // Connection settings
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i=0; i<ports.size(); i++) {
        this->ui->COMPortComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
    }

    /*
    int ik;
    double jk;
    const int Size = 1000;
    double xval[Size];
    double yval[Size];

    for(ik=0, jk=0; ik<Size; ik++)
    {
        xval[ik] = jk;
        yval[ik] = qSin(jk);
        jk+=0.1;
    }
    */

    int geophonesCount = 6;
    int channelsCount = 3;

    QLabel *plotLabel[geophonesCount];
    QWidget *plotWidget[geophonesCount];
    QVBoxLayout *plotLayout[geophonesCount];
    //QwtPlot *plot[geophonesCount][channelsCount];
    // QwtPlotCurve *curve[geophonesCount][channelsCount];

    for (int i=0; i<geophonesCount; i++) {
        // Initialize widgets
        plotLabel[i] = new QLabel();
        plotWidget[i] = new QWidget();
        //plotWidget[i] = new QWidget(this, Qt::Popup | Qt:: Dialog);
        plotLayout[i] = new QVBoxLayout();

        // Widget settings
        plotLabel[i]->setText(tr("Geophon #%1").arg(i+1));
        plotWidget[i]->setAutoFillBackground(true);
        plotWidget[i]->setPalette(Qt::black);
        //plotWidget[i]->setWindowModality(Qt::WindowModal);
        //plotWidget[i]->showMaximized();

        plotLayout[i]->addWidget(plotLabel[i]);

        // Add plots to widget
        for (int j=0; j<channelsCount; j++) {
            // Initialize plot
            this->plot[i][j] = new QwtPlot();

            // Plot settings
            this->plot[i][j]->setAutoFillBackground(true);
            this->plot[i][j]->setPalette(Qt::black);
            (void) new QwtPlotPanner(plot[i][j]->canvas());
            (void) new QwtPlotMagnifier(plot[i][j]->canvas());

            // Initialize curve
             //this->curve[i][j] = new QwtPlotCurve();

            // Curve settings
             //this->curve[i][j]->setRenderHint(QwtPlotItem::RenderAntialiased);
             //this->curve[i][j]->setPen(QPen(Qt::white));

            // Set data
             //this->curve[i][j]->setSamples(xval, yval, Size);
             //this->curve[i][j]->attach(this->plot[i][j]);

            //this->samplesVector[i][j] = new QVector();
            //this->dataVector[i][j] = new QVector();

             this->plot[i][j]->replot();

            // Add plot to widget
            plotLayout[i]->addWidget(this->plot[i][j]);
        }
        plotWidget[i]->setLayout(plotLayout[i]);
        if (i<3)
            ui->gridLayout->addWidget(plotWidget[i], 0, i);
        else
            ui->gridLayout->addWidget(plotWidget[i], 1, i-3);
    }
}

MainWindow::~MainWindow()
{
    if (ui->connectPushButton->isChecked())
        this->on_connectPushButton_toggled(false);
    delete ui;

    // Destroy mole
    Mole *mole = Mole::getInstance();
    mole->~Mole();
}

void MainWindow::setStage(me_test_suite_stage stage) {
    switch (stage) {
    case ME_TSS_IDLE: {
        ui->statusBar->showMessage(tr("[Stage] IDLE"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_1: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_1"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_2: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_2"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_4: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_4"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_8: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_8"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_16: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_16"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_32: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_32"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_64: {
        ui->statusBar->showMessage(tr("[Stage] GAIN_COEFFICIENTS_64"));
    } break;
    case ME_TSS_NOISE_FLOOR: {
        ui->statusBar->showMessage(tr("[Stage] NOISE FLOOR"));
    } break;
    case ME_TSS_TOTAL_HARMONIC_DISTORTION: {
        ui->statusBar->showMessage(tr("[Stage] TOTAL HARMONIC DISTORTION"));
    } break;
    case ME_TSS_ZERO_SHIFT: {
        ui->statusBar->showMessage(tr("[Stage:] ZERO SHIFT"));
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_SIN: {
        ui->statusBar->showMessage(tr("[Stage] COMMON MODE REJECTION SIN"));
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_IN_PHASE: {
        ui->statusBar->showMessage(tr("[Stage] COMMON MODE REJECTION IN PHASE"));
    } break;
    default:
        qDebug("[Bug] ME_TSS_COUNT");
    }
}

void MainWindow::plotData(uint8 moduleIndex, uint8 channelIndex, uint16 size, QList<double> samples, QList<double> data) {
    if (moduleIndex == 0)
        return;

    int module = moduleIndex - 1;
    int channel = channelIndex;

    // Remove previous curves
    this->plot[module][channel]->detachItems();
    this->plot[module][channel]->replot();

    // Set data
    this->curve[module][channel] = new QwtPlotCurve();
    this->curve[module][channel]->setRenderHint(QwtPlotItem::RenderAntialiased);
    this->curve[module][channel]->setPen(QPen(Qt::white));
    this->curve[module][channel]->setSamples(samples.toVector(), data.toVector());
    this->curve[module][channel]->attach(this->plot[module][channel]);

    this->plot[module][channel]->replot();
}

void MainWindow::plotData2(uint8 moduleIndex, uint8 channelIndex, uint16 size,
                           QVector<double> samples, QVector<double> data) {
    if (moduleIndex == 0)
        return;

    int module = moduleIndex - 1;
    int channel = channelIndex;

    //this->samplesVector[module][channel] << samples;
    //this->dataVector[module][channel] += data;

    // Remove previous curves
    this->plot[module][channel]->detachItems();
    this->plot[module][channel]->replot();

    // Set data
    this->curve[module][channel] = new QwtPlotCurve();
    this->curve[module][channel]->setRenderHint(QwtPlotItem::RenderAntialiased);
    this->curve[module][channel]->setPen(QPen(Qt::red));
    this->curve[module][channel]->setSamples(samples, data);
    this->curve[module][channel]->attach(this->plot[module][channel]);

    this->plot[module][channel]->replot();
}

void MainWindow::on_actionRegistration_triggered()
{
    emit showRegistrationSettingsDialog();
}

void MainWindow::on_actionTestGainCoefficientsSync_triggered()
{
    int ret = 0;
    Mole *mole = Mole::getInstance();
    ret = mole->testGainCoefficients(true);

    if (ret < 0) {
        ui->gainCoefficientsStatusLabel->setText(tr("<font color='red'>Failed</font"));
    }
    else {
        ui->gainCoefficientsStatusLabel->setText(tr("<font color='green'>Succeed</font"));
    }
}

void MainWindow::on_actionTestGainCoefficientsAsync_triggered()
{
    Mole *mole = Mole::getInstance();
    mole->testGainCoefficients(false);
}

void MainWindow::on_actionTestNoiseFloorSync_triggered()
{
    int ret;
    Mole *mole = Mole::getInstance();
    ret = mole->testNoiseFloor(true);

    if (ret < 0) {
        ui->noiseFloorStatusLabel->setText(tr("<font color='red'>Failed</font"));
    }
    else {
        ui->noiseFloorStatusLabel->setText(tr("<font color='green'>Succeed</font"));
    }
}

void MainWindow::on_actionTestTotalHarmonicDistortionSync_triggered()
{
    int ret;
    Mole *mole = Mole::getInstance();
    ret = mole->testTotalHarmonicDistortion(true);

    if (ret < 0) {
        ui->totalHarmonicDistortionStatusLabel->setText(tr("<font color='red'>Failed</font"));
    }
    else {
        ui->totalHarmonicDistortionStatusLabel->setText(tr("<font color='green'>Succeed</font"));
    }
}

void MainWindow::on_actionTestZeroShiftSync_triggered()
{
    int ret;
    Mole *mole = Mole::getInstance();
    ret = mole->testZeroShift(true);

    if (ret < 0) {
        ui->zeroShiftStatusLabel->setText(tr("<font color='red'>Failed</font"));
    }
    else {
        ui->zeroShiftStatusLabel->setText(tr("<font color='green'>Succeed</font"));
    }
}

void MainWindow::on_actionTestCommonModeRejectionSync_triggered()
{
    int ret;
    Mole *mole = Mole::getInstance();
    ret = mole->testCommonModeRejection(true);

    if (ret < 0) {
        ui->commonModeRejectionStatusLabel->setText(tr("<font color='red'>Failed</font"));
    }
    else {
        ui->commonModeRejectionStatusLabel->setText(tr("<font color='green'>Succeed</font"));
    }
}

void MainWindow::on_connectPushButton_toggled(bool checked)
{
    QString portName = this->ui->COMPortComboBox->itemData(this->ui->COMPortComboBox->currentIndex()).toString();
    std::string str = portName.toStdString();
    const char *portString = str.c_str();

    Mole *mole = Mole::getInstance();
    if (checked) {
        if (mole->open(portString) < 0) {
            ui->connectPushButton->setChecked(false);
            qDebug() << "[Error] Can't open connection at " << portString;
            QMessageBox::critical(0, "Error", "Can't open connection.");
        }
        else {
            mole->getHostInfo();
            qDebug() << "[Success] Connection opened at " << portString;
            if (mole->hostMount() < 0) {
                ui->connectPushButton->setChecked(false);
                qDebug() << "[Error] Can't mount host";
                QMessageBox::critical(0, "Error", "Can't mount host.");
            }
            else {
                qDebug() << "[Success] Host mounted";
                ui->actionRegistration->setEnabled(true);
                ui->menuTests->setEnabled(true);
                ui->connectPushButton->setText(tr("Disconnect"));
                ui->startConversionPushButton->setEnabled(true);
                ui->testsGroupBox->setEnabled(true);
                ui->statusBar->showMessage(tr("Status: host mounted"));
            }
        }
    }
    else {
        // Stop conversion
        if (ui->startConversionPushButton->isChecked()) {
            on_startConversionPushButton_toggled(false);
        }
        if (mole->hostUnmount() < 0)
            qDebug() << "[Error] Can't unmount host";
        else {
            qDebug() << "[Success] Host unmounted";
            if (mole->close() < 0)
                qDebug() << "[Error] Can't close connection";
            else {
                qDebug() << "[Success] Connection closed";
                ui->actionRegistration->setEnabled(false);
                ui->menuTests->setEnabled(false);
                ui->connectPushButton->setText(tr("Connect"));
                ui->startConversionPushButton->setEnabled(false);
                ui->testsGroupBox->setEnabled(false);
                ui->statusBar->showMessage(tr("Status: host unmounted"));
            }
        }
    }
}

void MainWindow::on_startTestsPushButton_clicked() {
    ui->startTestsPushButton->setText(tr("Stop"));
    ui->startTestsPushButton->setEnabled(false);
    if (ui->gainCoefficientsTestCheckBox->isChecked()) {
        ui->gainCoefficientsStatusLabel->setText(tr("In progress"));
        on_actionTestGainCoefficientsSync_triggered();
    }
    ui->progressBar->setValue(1);

    if (ui->noiseFloorTestCheckBox->isChecked()) {
        ui->noiseFloorStatusLabel->setText(tr("In progress"));
        on_actionTestNoiseFloorSync_triggered();
    }
    ui->progressBar->setValue(2);

    if (ui->totalHarmonicDistortionTestCheckBox->isChecked()) {
        ui->totalHarmonicDistortionStatusLabel->setText(tr("In progress"));
        on_actionTestTotalHarmonicDistortionSync_triggered();
    }
    ui->progressBar->setValue(3);

    if (ui->zeroShiftCheckBox->isChecked()) {
        ui->zeroShiftStatusLabel->setText(tr("In progress"));
        on_actionTestZeroShiftSync_triggered();
    }
    ui->progressBar->setValue(4);

    if (ui->commonModeRejectionCheckBox->isChecked()) {
        ui->commonModeRejectionStatusLabel->setText(tr("In progress"));
        on_actionTestCommonModeRejectionSync_triggered();
    }
    ui->progressBar->setValue(5);
    ui->startTestsPushButton->setText(tr("Start"));
    ui->startTestsPushButton->setEnabled(true);
}

/*
 * Clear all plots action
 */
void MainWindow::on_actionClear_plots_triggered() {
    for (int i=0; i<6; i++)
        for (int j=0; j<3; j++) {
            plot[i][j]->detachItems();
            plot[i][j]->replot();
        }
}

void MainWindow::on_actionHelp_triggered()
{
    assistant->showDocumentation("index.html");
}

void MainWindow::on_startConversionPushButton_toggled(bool checked)
{
    Mole *mole = Mole::getInstance();
    if (checked) {
        if (mole->startConversion(1000, ME_MCS_EXTERNAL) < 0)
            qDebug("[Error] me_host_start_conversion");
        else {
            qDebug("[Success] me_host_start_conversion");
            ui->startConversionPushButton->setText(tr("Stop conversion"));
            ui->statusBar->showMessage(tr("[Status] Conversation started"));
            timer->start(5000);
        }
    }
    else {
        timer->stop();
        if (mole->stopConversion() < 0)
            qDebug("[Error] me_host_stop_conversion");
        else {
            qDebug("[Success] me_host_stop_conversion");
            ui->startConversionPushButton->setText(tr("Start conversion"));
            ui->statusBar->showMessage(tr("[Status] Conversation stopped"));
        }
    }
}

void MainWindow::getConversationData() {
    Mole *mole = Mole::getInstance();

    uint8 firstAddress = mole->getFirstAddress();
    uint8 lastAddress = mole->getLastAddress();
    uint8 channelCount = mole->getChannelCount();
    int size = me_get_module_count(firstAddress, lastAddress) * channelCount * 10000;
    uint8 *samplesData = new uint8[size];

    mole->getSamplesData(1000, samplesData);
}
