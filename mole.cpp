#include <QDebug>
#include "mole.h"

Mole *Mole::getInstance() {
    if (!instance)
        instance = new Mole();
    return instance;
}

Mole::Mole(QObject *parent) :
    QObject(parent)
{
    qDebug() << "me_get_version_git_sha1: " << me_get_version_git_sha1();
    qDebug() << "me_get_version: " << me_get_version();
    qDebug() << "me_get_version_string " << me_get_version_string();
    qDebug() << "me_get_versionbuild_date " << me_get_version_build_date();
    qDebug() << "me_get_version_build_time " << me_get_version_build_time();
}

int Mole::init() {
    int ret = 0;
    ret = me_init();

    return ret;
}

int Mole::open(const char *portString) {
    int moleDescriptor = -1;
    moleDescriptor = me_open_mole(portString);

    return moleDescriptor;
}

int Mole::close(int moleDescriptor) {
    int ret = 0;
    ret = me_close_mole(moleDescriptor);

    return ret;
}

int Mole::destroy() {
    int ret = 0;
    ret = me_destroy();

    return ret;
}

uint16 Mole::getDefaultRetries() {
    uint16 defaultRetries = 0;
    defaultRetries = me_get_default_retries();

    return defaultRetries;
}

Mole* Mole::instance=NULL;
