#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->setMargin(0);

    ui->retranslateUi(this);

    QwtPlot *plot = new QwtPlot();
    plot->setTitle(tr("Demonstration"));

    (void) new QwtPlotPanner(plot->canvas());
    (void) new QwtPlotMagnifier(plot->canvas());
    QwtLegend *legend = new QwtLegend;
    plot->insertLegend(legend, QwtPlot::RightLegend);

    plot->setAutoFillBackground(true);
    plot->setPalette(QPalette(QColor(0, 0, 0)));

    QwtPlotCurve *curve = new QwtPlotCurve(QString("qSin"));
    QwtPlotCurve *curve2 = new QwtPlotCurve(QString("qCos"));
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setPen(QPen(Qt::red));
    curve2->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve2->setPen(QPen(Qt::green));

    int i;
    double j;
    const int Size = 100;
    double xval[Size];
    double yval[Size], yval2[Size];

    for(i=0, j=0; i<Size;i++)
    {
        xval[i] = j;
        yval[i] = qSin(j);
        yval2[i] = qCos(j);
        j+=0.1;
    }

    curve->setSamples(xval, yval, Size);
    curve2->setSamples(xval, yval2, Size);

    curve->attach(plot);
    curve2->attach(plot);
    plot->replot();

    ui->verticalLayout->addWidget(plot);
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
