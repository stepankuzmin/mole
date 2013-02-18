#include "sd3.h"

SD3::SD3(QObject *parent) :
    QObject(parent)
{
}

sd3_file_t SD3::read(const char *fileName) {
    FILE *file;
    sd3_file_t sd3_file;
    file = fopen(fileName, "rb");

    int sizeOfInt = sizeof(int);
    int sizeOfFloat = sizeof(float);

    fread(&sd3_file.version, sizeOfInt, 1, file);
    fread(&sd3_file.datarate, sizeOfInt, 1, file);
    fread(&sd3_file.samples_count, sizeOfInt, 1, file);
    fread(&sd3_file.mode, sizeOfInt, 1, file);
    fread(&sd3_file.address, sizeOfInt, 1, file);
    fread(&sd3_file.date, sizeOfInt, 1, file);
    fread(&sd3_file.time, sizeOfInt, 1, file);
    fread(&sd3_file.x_source, sizeOfInt, 1, file);
    fread(&sd3_file.y_source, sizeOfInt, 1, file);
    fread(&sd3_file.h_source, sizeOfInt, 1, file);

    float sample;
    int recordIndex=0;
    while (!feof(file)) {
        sd3_record_t record;
        fread(&record.x_state, sizeOfInt, 1, file);
        fread(&record.y_state, sizeOfInt, 1, file);
        fread(&record.z_state, sizeOfInt, 1, file);
        fread(&record.x_inclinometer, sizeOfInt, 1, file);
        fread(&record.y_inclinometer, sizeOfInt, 1, file);
        fread(&record.z_inclinometer, sizeOfInt, 1, file);
        fread(&record.x_receiver, sizeOfInt, 1, file);
        fread(&record.y_receiver, sizeOfInt, 1, file);
        fread(&record.h_receiver, sizeOfInt, 1, file);
        fseek(file, sizeOfInt, SEEK_CUR); // Skip reserved field

        for (int i=0; i<sd3_file.samples_count; i++) {
            fread(&sample, sizeOfFloat, 1, file);
            record.x << sample;
        }

        for (int i=0; i<sd3_file.samples_count; i++) {
            fread(&sample, sizeOfFloat, 1, file);
            record.y << sample;
        }

        for (int i=0; i<sd3_file.samples_count; i++) {
            fread(&sample, sizeOfFloat, 1, file);
            record.z << sample;
        }

        sd3_file.records << record;
        qDebug("Reading record #%d", recordIndex);
        recordIndex++;
    }
    fclose(file);
    qDebug() << "read sd3_file.records.size()" << sd3_file.records.size();

    return sd3_file;
}

bool SD3::write(const char *fileName, sd3_file_t sd3_file) {
    FILE *file;
    file = fopen(fileName, "wb");

    fwrite(&sd3_file.version,         sizeof(int), 1, file);
    fwrite(&sd3_file.datarate,        sizeof(int), 1, file);
    fwrite(&sd3_file.samples_count,   sizeof(int), 1, file);
    fwrite(&sd3_file.mode,            sizeof(int), 1, file);
    fwrite(&sd3_file.address,         sizeof(int), 1, file);
    fwrite(&sd3_file.date,            sizeof(int), 1, file);
    fwrite(&sd3_file.time,            sizeof(int), 1, file);
    fwrite(&sd3_file.x_source,        sizeof(int), 1, file);
    fwrite(&sd3_file.y_source,        sizeof(int), 1, file);
    fwrite(&sd3_file.h_source,        sizeof(int), 1, file);

    float sample;
    qDebug() << "write sd3_file.records.size()" << sd3_file.records.size();
    for (int recordIndex = 0; recordIndex < sd3_file.records.size(); ++recordIndex) {
        qDebug("Writing record #%d", recordIndex);
        sd3_record_t record = sd3_file.records.at(recordIndex);

        fwrite(&record.x_state, sizeof(int), 1, file);
        fwrite(&record.y_state, sizeof(int), 1, file);
        fwrite(&record.z_state, sizeof(int), 1, file);
        fwrite(&record.x_inclinometer, sizeof(int), 1, file);
        fwrite(&record.y_inclinometer, sizeof(int), 1, file);
        fwrite(&record.z_inclinometer, sizeof(int), 1, file);
        fwrite(&record.x_receiver, sizeof(int), 1, file);
        fwrite(&record.y_receiver, sizeof(int), 1, file);
        fwrite(&record.h_receiver, sizeof(int), 1, file);

        fseek(file, sizeof(int), SEEK_CUR);

        for (int xIndex=0; xIndex < record.x.size(); xIndex++) {
            sample = record.x.at(xIndex);
            fwrite(&sample, sizeof(float), 1, file);
        }
        for (int yIndex=0; yIndex < record.y.size(); yIndex++) {
            sample = record.y.at(yIndex);
            fwrite(&sample, sizeof(float), 1, file);
        }
        for (int zIndex=0; zIndex < record.z.size(); zIndex++) {
            sample = record.z.at(zIndex);
            fwrite(&sample, sizeof(float), 1, file);
        }
    }

    fclose(file);

    read(fileName);
}
