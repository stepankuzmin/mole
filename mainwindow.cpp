#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QProgressBar>
#include "qextserialenumerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QProgressBar *progressBar = new QProgressBar();
    ui->statusBar->addWidget(progressBar);

    // Connection settings
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    for (int i=0; i<ports.size(); i++) {
        this->ui->COMPortComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
    }

    // Plots settings
    ui->retranslateUi(this);

    QwtPlot *plot1 = new QwtPlot();
    QwtPlot *plot2 = new QwtPlot();
    QwtPlot *plot3 = new QwtPlot();
    QwtPlot *plot4 = new QwtPlot();
    QwtPlot *plot5 = new QwtPlot();
    QwtPlot *plot6 = new QwtPlot();

    plot1->setTitle(tr("#1"));
    plot2->setTitle(tr("#2"));
    plot3->setTitle(tr("#3"));
    plot4->setTitle(tr("#4"));
    plot5->setTitle(tr("#5"));
    plot6->setTitle(tr("#6"));

    plot1->setAutoFillBackground(true);
    plot1->setPalette(Qt::black);
    plot2->setAutoFillBackground(true);
    plot2->setPalette(Qt::black);
    plot3->setAutoFillBackground(true);
    plot3->setPalette(Qt::black);
    plot4->setAutoFillBackground(true);
    plot4->setPalette(Qt::black);
    plot5->setAutoFillBackground(true);
    plot5->setPalette(Qt::black);
    plot6->setAutoFillBackground(true);
    plot6->setPalette(Qt::black);

    QwtPlotCurve *curve11 = new QwtPlotCurve();
    QwtPlotCurve *curve12 = new QwtPlotCurve();
    QwtPlotCurve *curve13 = new QwtPlotCurve();

    QwtPlotCurve *curve2 = new QwtPlotCurve();
    QwtPlotCurve *curve3 = new QwtPlotCurve();
    QwtPlotCurve *curve4 = new QwtPlotCurve();
    QwtPlotCurve *curve5 = new QwtPlotCurve();
    QwtPlotCurve *curve6 = new QwtPlotCurve();

    curve11->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve12->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve13->setRenderHint(QwtPlotItem::RenderAntialiased);

    curve11->setPen(QPen(Qt::white));
    curve12->setPen(QPen(Qt::gray));
    curve13->setPen(QPen(Qt::lightGray));

    curve2->setPen(QPen(Qt::white));
    curve3->setPen(QPen(Qt::white));
    curve4->setPen(QPen(Qt::white));
    curve5->setPen(QPen(Qt::white));
    curve6->setPen(QPen(Qt::white));

    int i;
    double j;
    const int Size = 1000;
    double xval[Size];
    double yval[Size], yval2[Size], yval3[Size];

    for(i=0, j=0; i<Size;i++)
    {
        xval[i] = j;
        yval[i] = qSin(j);
        yval2[i] = qCos(j);
        yval3[i] = qSin(j)+2;
        j+=0.1;
    }

    curve11->setSamples(xval, yval, Size);
    curve12->setSamples(xval, yval2, Size);
    curve13->setSamples(xval, yval3, Size);

    curve2->setSamples(xval, yval2, Size);
    curve3->setSamples(xval, yval, Size);
    curve4->setSamples(xval, yval2, Size);
    curve5->setSamples(xval, yval, Size);
    curve6->setSamples(xval, yval2, Size);

    curve11->attach(plot1);
    curve12->attach(plot1);
    curve13->attach(plot1);

    curve2->attach(plot2);
    curve3->attach(plot3);
    curve4->attach(plot4);
    curve5->attach(plot5);
    curve6->attach(plot6);

    plot1->replot();
    plot2->replot();
    plot3->replot();
    plot4->replot();
    plot5->replot();
    plot6->replot();

    ui->gridLayout->addWidget(plot1, 0, 0);
    ui->gridLayout->addWidget(plot2, 0, 1);
    ui->gridLayout->addWidget(plot3, 1, 0);
    ui->gridLayout->addWidget(plot4, 1, 1);
    ui->gridLayout->addWidget(plot5, 2, 0);
    ui->gridLayout->addWidget(plot6, 2, 1);
}

MainWindow::~MainWindow()
{
    delete ui;

    // Destroy mole
    Mole *mole = Mole::getInstance();
    mole->~Mole();
}

void MainWindow::setStatusBarText(const QString text) {
    ui->statusBar->showMessage(tr("State: %1").arg(text));
}

void MainWindow::setStage(me_test_suite_stage stage) {
    switch (stage) {
    case ME_TSS_IDLE: {
        ui->statusBar->showMessage(tr("Stage: IDLE"));
        ui->logTextEdit->insertPlainText(tr("[Stage] IDLE.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_1: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_1"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_1.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_2: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_2"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_2.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_4: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_4"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_4.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_8: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_8"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_8.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_16: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_16"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_16.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_32: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_32"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_32.\n"));
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_64: {
        ui->statusBar->showMessage(tr("Stage: GAIN_COEFFICIENTS_64"));
        ui->logTextEdit->insertPlainText(tr("[Stage] GAIN_COEFFICIENTS_64.\n"));
    } break;
    case ME_TSS_NOISE_FLOOR: {
        ui->statusBar->showMessage(tr("Stage: NOISE FLOOR"));
        ui->logTextEdit->insertPlainText(tr("[Stage] NOISE FLOOR.\n"));
    } break;
    case ME_TSS_TOTAL_HARMONIC_DISTORTION: {
        ui->statusBar->showMessage(tr("Stage: TOTAL HARMONIC DISTORTION"));
        ui->logTextEdit->insertPlainText(tr("[Stage] TOTAL HARMONIC DISTORTION.\n"));
    } break;
    case ME_TSS_ZERO_SHIFT: {
        ui->statusBar->showMessage(tr("Stage: ZERO SHIFT"));
        ui->logTextEdit->insertPlainText(tr("[Stage] ZERO SHIFT.\n"));
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_SIN: {
        ui->statusBar->showMessage(tr("Stage: COMMON MODE REJECTION SIN"));
        ui->logTextEdit->insertPlainText(tr("[Stage] COMMON MODE REJECTION SIN.\n"));
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_IN_PHASE: {
        ui->statusBar->showMessage(tr("Stage: COMMON MODE REJECTION IN PHASE"));
        ui->logTextEdit->insertPlainText(tr("[Stage] COMMON MODE REJECTION IN PHASE.\n"));
    } break;
    default:
        qDebug("BUG: ME_TSS_COUNT");
    }
}

void MainWindow::on_actionRegistration_triggered()
{
    emit showRegistrationSettingsDialog();
}

void MainWindow::on_actionTestGainCoefficientsSync_triggered()
{
    Mole *mole = Mole::getInstance();
    mole->testGainCoefficients(true);
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
            ui->logTextEdit->insertPlainText(tr("[Error] Can't open connection at %1.\n").arg(portString));
            QMessageBox::critical(0, "Error", "Can't open connection.");
        }
        else {
            mole->getHostInfo();
            ui->logTextEdit->insertPlainText(tr("Host info:\n"
                                                "\t[*] Device id = %1\n"
                                                "\t[*] Minor = %2\n"
                                                "\t[*] Major = %3\n")
                                                .arg(mole->getDeviceId())
                                                .arg(mole->getMinor())
                                                .arg(mole->getMajor()));
            if (mole->hostMount() < 0) {
                ui->connectPushButton->setChecked(false);
                ui->logTextEdit->insertPlainText(tr("[Error] Can't mount host.\n"));
                QMessageBox::critical(0, "Error", "Can't mount host.");
            }
            else {
                ui->logTextEdit->insertPlainText(tr("Host mounted:\n"
                                                    "\t[*] First address = %1\n"
                                                    "\t[*] Last address = %2\n"
                                                    "\t[*] Channel count = %3\n"
                                                    "\t[*] Bytes in channel = %4\n"
                                                    "\t[*] Bytes in module = %5\n"
                                                    "\t[*] Bytes in line = %6\n"
                                                    "\t[*] Maximum samples = %7\n")
                                                    .arg(mole->getFirstAddress())
                                                    .arg(mole->getLastAddress())
                                                    .arg(mole->getChannelCount())
                                                    .arg(mole->getBytesInChannel())
                                                    .arg(mole->getBytesInModule())
                                                    .arg(mole->getBytesInLine())
                                                    .arg(mole->getMaximumSamples()));
                ui->logTextEdit->insertPlainText(tr("[Success] Connection opened at %1.\n").arg(portString));
                ui->connectPushButton->setText(tr("Disconnect"));
            }
        }
    }
    else {
        mole->hostUnmount();
        mole->close();
        ui->connectPushButton->setText(tr("Connect"));
    }
}
