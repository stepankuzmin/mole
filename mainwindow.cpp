#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QProgressBar>
#include "qextserialenumerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    // Connection settings
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i=0; i<ports.size(); i++) {
        this->ui->COMPortComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
    }

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

    int geophonesCount = 6;
    int channelsCount = 3;

    QLabel *plotLabel[geophonesCount];
    QWidget *plotWidget[geophonesCount];
    QVBoxLayout *plotLayout[geophonesCount];
    QwtPlot *plot[geophonesCount][channelsCount];
    QwtPlotCurve *curve[geophonesCount][channelsCount];
    for (int i=0; i<geophonesCount; i++) {
        // Initialize widgets
        plotLabel[i] = new QLabel();
        //plotLabel[i] = new QLabel();
        plotWidget[i] = new QWidget();
        plotLayout[i] = new QVBoxLayout();

        // Widget settings
        plotLabel[i]->setText(tr("Geophon #%1").arg(i+1));
        plotWidget[i]->setAutoFillBackground(true);
        plotWidget[i]->setPalette(Qt::black);
        plotLayout[i]->addWidget(plotLabel[i]);

        // Add plots to widget
        for (int j=0; j<channelsCount; j++) {
            // Initialize plot
            plot[i][j] = new QwtPlot();

            // Plot settings
            plot[i][j]->setAutoFillBackground(true);
            plot[i][j]->setPalette(Qt::black);

            // Initialize curve
            curve[i][j] = new QwtPlotCurve();

            // Curve settings
            curve[i][j]->setRenderHint(QwtPlotItem::RenderAntialiased);
            curve[i][j]->setPen(QPen(Qt::white));

            // Set data
            curve[i][j]->setSamples(xval, yval, Size);
            curve[i][j]->attach(plot[i][j]);

            plot[i][j]->replot();

            // Add plot to widget
            plotLayout[i]->addWidget(plot[i][j]);
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

void MainWindow::on_actionRegistration_triggered()
{
    emit showRegistrationSettingsDialog();
}

void MainWindow::on_actionTestGainCoefficientsSync_triggered()
{
    int ret = 0;
    Mole *mole = Mole::getInstance();
    ret = mole->testGainCoefficients(true);

    if (ret < 0)
        QMessageBox::critical(0, "Error", "Gain coefficients test failed.");
    else
        QMessageBox::information(0, "Information", "Gain coefficients test succeed.");
}

void MainWindow::on_actionTestGainCoefficientsAsync_triggered()
{
    Mole *mole = Mole::getInstance();
    mole->testGainCoefficients(false);
}

void MainWindow::on_actionTestNoiseFloorSync_triggered()
{
    Mole *mole = Mole::getInstance();
    mole->testNoiseFloor(true);
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
                ui->connectPushButton->setText(tr("Disconnect"));
            }
        }
    }
    else {
        if (mole->hostUnmount() < 0)
            qDebug() << "[Error] Can't unmount host";
        else {
            qDebug() << "[Success] Host unmounted";
            if (mole->close() < 0)
                qDebug() << "[Error] Can't close connection";
            else {
                qDebug() << "[Success] Connection closed";
                ui->connectPushButton->setText(tr("Connect"));
            }
        }
    }
}
