#ifndef MOLE_H
#define MOLE_H

#include <QObject>
#include "3rdparty/mole-engine/include/mole-engine/mole-engine.h"
#include "3rdparty/mole-engine/include/mole-engine/mole-engine-test-suite.h"

enum MoleState {
    MOLE_INIT       = 0x00,
    MOLE_OPEN       = 0x01,
    MOLE_CLOSE      = 0x02,
    MOLE_DESTROY    = 0x03
};

class Mole : public QObject
{
    Q_OBJECT
    static Mole *instance;

public:
    static Mole *getInstance();
    ~Mole();
    int getDescriptor();

    void testGainCoefficients(bool isSync);
    void testNoiseFloor(bool isSync);

private:
    int descriptor;

protected:
    explicit Mole(QObject *parent = 0);
    
signals:
    void stateChange(const QString&);
    void stateChange(MoleState state);
    
public slots:
    int open(const char *portString);
    int close();

};

#endif // MOLE_H
