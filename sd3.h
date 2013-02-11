#ifndef SD3_H
#define SD3_H

#include <fstream>
#include <QDebug>
#include <QObject>

class SD3 : public QObject
{
    Q_OBJECT
public:
    explicit SD3(QObject *parent = 0);
    int getVersion();
    int getDatarate();
    int getSamplesCount();
    int getMode();
    int getAddress();
    int getDate();
    int getTime();

private:
    FILE *file;

    // File headers
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

signals:
    
public slots:
    
};

#endif // SD3_H
