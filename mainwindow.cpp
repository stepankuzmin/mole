#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);

    connect(ui->actionNewFile, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionRecord, SIGNAL(triggered()), this, SLOT(record()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    ui->mdiArea->closeAllSubWindows();
    if (ui->mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::newFile() {
    Workspace *workspace = createWorkspace();
    workspace->newFile();
    workspace->show();
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("SD3 (*.sd3)"));
    if (!fileName.isEmpty()) {
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        Workspace *workspace = createWorkspace();
        if (workspace->loadFile(fileName)) {
            ui->statusBar->showMessage(tr("File %1 loaded").arg(fileName), 2000);
            workspace->show();
        } else {
            workspace->close();
        }
    }
}

void MainWindow::record() {
    if (activeWorkspace()) {
        activeWorkspace()->record();
    }
    else {
        newFile();
        record();
    }
}

Workspace *MainWindow::createWorkspace() {
    Workspace *workspace = new Workspace;
    ui->mdiArea->addSubWindow(workspace);

    return workspace;
}

Workspace *MainWindow::activeWorkspace() {
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<Workspace *>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName) {
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        Workspace *workspace = qobject_cast<Workspace *>(window->widget());
        if (workspace->getCurrentFileName() == canonicalFilePath)
            return window;
    }
    return 0;
}
