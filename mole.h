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
    void getHostInfo();
    uint16 getDeviceId();
    uint8 getMinor();
    uint8 getMajor();
    uint8 getFirstAddress();
    uint8 getLastAddress();
    uint8 getChannelCount();
    uint8 getBytesInChannel();
    uint8 getBytesInModule();
    uint16 getBytesInLine();
    uint16 getMaximumSamples();
    uint8 getLastAddressActual();

    int hostMount();
    void hostUnmount();
    void testGainCoefficients(bool isSync);
    void testNoiseFloor(bool isSync);

private:
    int descriptor;

    uint16 deviceId;
    uint8 minor;
    uint8 major;
    uint8 firstAddress;
    uint8 lastAddress;
    uint8 channelCount;
    uint8 bytesInChannel;
    uint8 bytesInModule;
    uint16 bytesInLine;
    uint16 maximumSamples;
    uint8 lastAddressActual;

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
