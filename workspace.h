#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QFile>
#include <QDialog>
#include <QString>
#include <QDateTime>
#include <QFileInfo>
#include <QMessageBox>

#include <QDebug>

struct sd3_record_t {
    int x_state;
    int y_state;
    int z_state;
    int x_inclinometer;
    int y_inclinometer;
    int z_inclinometer;
    int x_receiver;
    int y_receiver;
    int h_receiver;
    QVector< QVector<double> > data;
    QVector<double> *x; // pointer to data[0]
    QVector<double> *y; // pointer to data[1]
    QVector<double> *z; // pointer to data[2]
};
struct sd3_file_t {
    const char *fileName;
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
    QVector<sd3_record_t> records;
};

namespace Ui {
class Workspace;
}

class Workspace : public QDialog
{
    Q_OBJECT
    
public:
    explicit Workspace(QWidget *parent = 0);
    ~Workspace();

    void newFile();
    void record();
    bool loadFile(const QString &fileName);
    static sd3_file_t readSD3(const QString fileName);
    static bool writeSD3(const QString fileName, sd3_file_t sd3_file);
    QString getCurrentFileName() { return currentFileName; }
    
private:
    Ui::Workspace *ui;

    QString currentFileName;
    void setCurrentFileName(const QString &fileName);
};

#endif // WORKSPACE_H
