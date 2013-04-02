#include "workspace.h"
#include "ui_workspace.h"

Workspace::Workspace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Workspace)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

Workspace::~Workspace()
{
    delete ui;
}

void Workspace::newFile() {
    currentFileName = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + ".sd3";
    setWindowTitle(currentFileName + "[*]");

    //static int sequenceNumber = 1;

    //isUntitled = true;
    //curFile = tr("document%1.txt").arg(sequenceNumber++);
    //setWindowTitle(curFile + "[*]");

    //connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
}

void Workspace::record() {
    qDebug() << currentFileName;
}

bool Workspace::loadFile(const QString &fileName) {
    sd3_file_t sd3_file = readSD3(fileName); // if !sd3_file return false
    // plotSD3(sd3_file); // if !plotSD3() return false

    /*
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    */

    setCurrentFileName(fileName);

    /*
    connect(document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
    */

    return true;
}

sd3_file_t Workspace::readSD3(const QString fileName) {
    sd3_file_t sd3_file;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        /*
        QMessageBox::warning(this, tr("Workspace"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        */
        //return false;
    }

    QByteArray ba;
    ba = file.read(sizeof(int)); memcpy(&sd3_file.version, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.datarate, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.samples_count, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.mode, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.address, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.date, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.time, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.x_source, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.y_source, ba.constData(), sizeof(int));
    ba = file.read(sizeof(int)); memcpy(&sd3_file.h_source, ba.constData(), sizeof(int));

    qDebug() << "version:" << sd3_file.version;
    qDebug() << "datarate:" << sd3_file.datarate;
    qDebug() << "samples count:" << sd3_file.samples_count;
    qDebug() << "mode:" << sd3_file.mode;
    qDebug() << "address:" << sd3_file.address;
    qDebug() << "date:" << sd3_file.date;
    qDebug() << "time:" << sd3_file.time;
    qDebug() << "x source:" << sd3_file.x_source;
    qDebug() << "y source:" << sd3_file.y_source;
    qDebug() << "h source:" << sd3_file.h_source;

    while (!file.atEnd()) {

    }

    file.close();

    return sd3_file;
}

void Workspace::setCurrentFileName(const QString &fileName) {
    currentFileName = QFileInfo(fileName).canonicalFilePath();

    //isUntitled = false;
    //document()->setModified(false);

    setWindowModified(false);
    setWindowTitle(QFileInfo(currentFileName).fileName() + "[*]");
}
