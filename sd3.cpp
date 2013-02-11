#include "sd3.h"

SD3::SD3(QObject *parent) :
    QObject(parent)
{

    this->file = fopen("121128-073403.sd3", "rb");
    int size = sizeof(int);

    fread(&this->version,         size, 1, this->file);
    fread(&this->datarate,        size, 1, this->file);
    fread(&this->samples_count,   size, 1, this->file);
    fread(&this->mode,            size, 1, this->file);
    fread(&this->address,         size, 1, this->file);
    fread(&this->date,            size, 1, this->file);
    fread(&this->time,            size, 1, this->file);
    fread(&this->x_source,        size, 1, this->file);
    fread(&this->y_source,        size, 1, this->file);
    fread(&this->h_source,        size, 1, this->file);

    fclose(this->file);
}

/////////////
// private //
/////////////

int SD3::getVersion() {
    return this->version;
}

int SD3::getDatarate() {
    return this->datarate;
}

int SD3::getSamplesCount() {
    return this->samples_count;
}

int SD3::getMode() {
    return this->mode;
}

int SD3::getAddress() {
    return this->address;
}

int SD3::getDate() {
    return this->date;
}

int SD3::getTime() {
    return this->time;
}
