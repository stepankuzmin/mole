#include <QDebug>
#include "mole.h"

Mole* Mole::getInstance() {
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

Mole* Mole::instance=NULL;
