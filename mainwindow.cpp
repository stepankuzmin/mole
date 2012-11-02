#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "qextserialenumerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connection settings
    // List all avaliable COM ports
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    qDebug() << "List of avaliable ports:";
    for (int i=0; i<ports.size(); i++) {
        qDebug() << "port name: " << ports.at(i).portName;
        qDebug() << "friendly name: " << ports.at(i).friendName;
        qDebug() << "physical name: " << ports.at(i).physName;
        qDebug() << "enumerator name: " << ports.at(i).enumName << "\n";

        // Add port friendly name to COM Ports ComboBox
        this->ui->COMPortComboBox->addItem(ports.at(i).friendName, QVariant(ports.at(i).portName));
    }


    // Plots settings
    //ui->centralWidget->setAutoFillBackground(true);
    //ui->centralWidget->setPalette(Qt::black);
    ui->gridLayout->setMargin(0);

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

    (void) new QwtPlotPanner(plot1->canvas());
    (void) new QwtPlotMagnifier(plot1->canvas());

    //QwtLegend *legend = new QwtLegend;
    //plot->insertLegend(legend, QwtPlot::RightLegend);

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
        yval3[i] = qSin(j)+qCos(j);
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

void MainWindow::on_actionConnection_triggered()
{
    emit showConnectionDialog();
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
    qDebug() << "Connecting to: " << portString;

    Mole *mole = Mole::getInstance();
    if (checked) {
        if (mole->open(portString) < 0)
            QMessageBox::critical(0, "Error", "Can't open connection.");
        else {
            mole->getHostInfo();
            if (mole->hostMount() < 0)
                QMessageBox::critical(0, "Error", "Can't mount host.");
            else {
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
