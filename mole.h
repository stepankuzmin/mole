#ifndef MOLE_H
#define MOLE_H

//#include <QList>
//#include <QVector>

#include "sd3.h"

#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include "3rdparty/mole-engine/include/mole-engine/mole-engine.h"
#include "3rdparty/mole-engine/include/mole-engine/mole-engine-test-suite.h"

class Mole : public QObject
{
    Q_OBJECT
    static Mole *instance;

public:
    static Mole *getInstance();
    ~Mole();

    bool isConnected();
    bool isConversing();

    int getModuleCount();
    int getChannelCount();

    // Test suite
    int testSuiteGainCoefficients(bool isSync = true);
    int testSuiteNoiseFloor(bool isSync = true);

protected:
    explicit Mole(QObject *parent = 0);

private:
    QTimer *timer;

    int descriptor;
    uint8 first_address;
    uint8 last_address;
    int module_count; // @TODO: int to uint8
    uint8 channel_count;
    uint8 bytes_in_channel;
    uint8 bytes_in_module;
    uint16 bytes_in_line;
    uint16 maximum_samples;
    uint8 last_address_actual;
    bool is_geophone_connected;

    bool is_connected;
    bool is_conversing;

    me_mole_module_mode modulesMode;
    me_mole_conversion_synchronization conversionSynchronization;

    uint16 samplesSize; // samples size (количество дискретов)

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

    void emitDataDump(uint8 moduleIndex, uint8 channelIndex,
                      QVector<double> samples, QVector<double> data);

signals:
    void connectionStateChanged(bool isConnected);
    void modulesModeChanged(me_mole_module_mode modulesMode);
    void conversionSynchronizationChanged(me_mole_conversion_synchronization conversionSynchronization);
    void samplesSizeChanged(uint16 samplesSize);
    void dataDump(uint8 moduleIndex, uint8 channelIndex,
                  QVector<double> samples, QVector<double> data);

public slots:
    int connect(const char *portString); // @TODO: set return value as bool (isConnected)
    bool disconnect();

    int setModulesMode(me_mole_module_mode modulesMode);
    int setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization);

    void setSamplesSize(uint16 samplesSize); // Set samples size

    bool startConversion();
    bool stopConversion();
    //bool getSeismicData(uint16 samples);

    sd3_file_t getData();

    void startTimer(int msec);
    void stopTimer();
};

#endif // MOLE_H
