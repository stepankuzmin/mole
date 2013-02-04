#ifndef MOLE_H
#define MOLE_H

//#include <QList>
//#include <QVector>

#include <QDebug>
#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include "3rdparty/mole-engine/include/mole-engine/mole-engine.h"
#include "3rdparty/mole-engine/include/mole-engine/mole-engine-test-suite.h"
//#include "3rdparty/mole-engine/include/mole-engine/test-mole-engine.cpp"

/*
enum me_mole_connection_status {
    ME_MCS_CONNECTED    = 0x1,
    ME_MCS_DISCONNECTED = 0x2
};
*/

/*
typedef struct
{
    uint16 serial_number;
    uint8 year;
    uint8 month;

    uint16 device_id;
    uint8 minor;
    uint8 major;
} serial_and_firmware_t;

serial_and_firmware_t *_serial_and_firmware = NULL;
*/

class Mole : public QObject
{
    Q_OBJECT
    static Mole *instance;

public:
    static Mole *getInstance();
    ~Mole();

    bool isConnected();

    int getModuleCount();
    int getChannelCount();

    // Test suite
    int testSuiteGainCoefficients(bool isSync = true);
    int testSuiteNoiseFloor(bool isSync = true);

protected:
    explicit Mole(QObject *parent = 0);

private:
    int descriptor;
    uint8 first_address;
    uint8 last_address;
    uint8 channel_count;
    uint8 bytes_in_channel;
    uint8 bytes_in_module;
    uint16 bytes_in_line;
    uint16 maximum_samples;
    uint8 last_address_actual;
    bool is_geophone_connected;

    bool is_connected;
    int module_count;
    me_mole_conversion_synchronization conversionSynchronization;

    void sleep(int ms);
    int _wait_test();
    bool wait_test_with_error_handler();

    static void samplesDataCallbackHandler(int mole_descriptor,
                                           uint8 first_address, uint8 last_address,
                                           uint8 channel_count, uint8 bytes_in_channel,
                                           uint8 bytes_in_module, uint16 bytes_in_line,
                                           me_mole_module_datarate datarate,
                                           me_mole_module_gain gain,
                                           uint16 samples, uint8 *samples_data);

    static void stageChangedCallbackHandler(int mole_descriptor,
                                            me_test_suite_stage test_suite_stage);

    void emitDataDump(uint8 moduleIndex, uint8 channelIndex, uint16 size,
                      QVector<double> samples, QVector<double> data);

signals:
    void connectionStateChanged(bool isConnected);
    void conversionSynchronizationChanged(me_mole_conversion_synchronization conversionSynchronization);
    void dataDump(uint8 moduleIndex, uint8 channelIndex, uint16 size,
                  QVector<double> samples, QVector<double> data);

public slots:
    int connect(const char *portString);
    int disconnect();
    int setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization);
};

#endif // MOLE_H
