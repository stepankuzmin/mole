#ifndef SD3_H
#define SD3_H

#include <fstream>
#include <QDebug>
#include <QObject>
#include <QVector>

// SD3 record type
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
    QVector<double> x;
    QVector<double> y;
    QVector<double> z;
};

// SD3 file type
struct sd3_file_t {
    const char *fileName; // ?
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

class SD3 : public QObject
{
    Q_OBJECT
public:
    explicit SD3(QObject *parent = 0);
    static sd3_file_t read(const char *fileName);
    static bool write(const char *fileName, sd3_file_t sd3_file);

private:

signals:
    
public slots:
    
};

#endif // SD3_H
