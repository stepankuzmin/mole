#ifndef MOLE_H
#define MOLE_H

#include <QList>
#include <QObject>
#include "3rdparty/mole-engine/include/mole-engine/mole-engine.h"
#include "3rdparty/mole-engine/include/mole-engine/mole-engine-test-suite.h"

class Mole : public QObject
{
    Q_OBJECT
    static Mole *instance;

public:
    static Mole *getInstance();
    ~Mole();

    int getDescriptor();
    void getHostInfo();

    me_mole_module_mode getModuleMode();
    me_mole_module_gain getModuleGain();
    me_mole_module_datarate getModuleDatarate();
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

    int setModuleMode(me_mole_module_mode moduleMode);
    int setModuleGainAll(me_mole_module_gain moduleGain);
    int setModuleGainXAll(me_mole_module_gain moduleGain);
    int setModuleGainYAll(me_mole_module_gain moduleGain);
    int setModuleGainZAll(me_mole_module_gain moduleGain);
    int setModuleDatarate(me_mole_module_datarate moduleDatarate);
    int setModuleTestGeneratorAll(me_mole_module_test_generator testGenerator = ME_MMTG_COUNT);

    int hostMount();
    int hostUnmount();
    int testGainCoefficients(bool isSync);
    int testNoiseFloor(bool isSync);
    int testTotalHarmonicDistortion(bool isSync);
    int testZeroShift(bool isSync);
    int testCommonModeRejection(bool isSync);

private:
    int descriptor;

    me_mole_module_datarate moduleDatarate;
    me_mole_module_gain moduleGain;
    me_mole_module_mode moduleMode;
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

    static void samplesDataCallbackHandler(int mole_descriptor,
                                     uint8 first_address, uint8 last_address,
                                     uint8 channel_count, uint8 bytes_in_channel,
                                     uint8 bytes_in_module, uint16 bytes_in_line,
                                     me_mole_module_datarate datarate,
                                     me_mole_module_gain gain,
                                     uint16 samples, uint8 *samples_data);

    void emitStageChanged(me_test_suite_stage stage);

    void emitDataDump(uint8 moduleIndex, uint8 channelIndex,
                       uint16 size, QList<double> samples, QList<double> data);

    static void stageChangedCallbackHandler(int mole_descriptor,
                                            me_test_suite_stage test_suite_stage);

protected:
    explicit Mole(QObject *parent = 0);
    
signals:
    void stageChanged(me_test_suite_stage stage);

    void dataDump(uint8 moduleIndex, uint8 channelIndex,
                   uint16 size, QList<double> samples, QList<double> data);

    //void stateChange(const QString&);
    //void stateChange(MoleState state);
    
public slots:
    int open(const char *portString);
    int close();

private slots:

};

#endif // MOLE_H
