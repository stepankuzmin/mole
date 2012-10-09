#ifndef MOLE_H
#define MOLE_H

#include <QObject>
#include <QLibrary>

#include "mole-engine/mole-engine.h"
#include "mole-engine/mole-engine-test-suite.h"

class Mole : public QObject
{
    Q_OBJECT
    static Mole* instance;
public:
    static Mole* getInstance();
protected:
    Mole(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MOLE_H
