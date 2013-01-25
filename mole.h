#ifndef MOLE_H
#define MOLE_H

//#include <QList>
//#include <QVector>

#include <QDebug>
#include <QObject>
#include "3rdparty/mole-engine/include/mole-engine/mole-engine.h"
#include "3rdparty/mole-engine/include/mole-engine/mole-engine-test-suite.h"

enum me_mole_connection_status {
    ME_MCS_CONNECTED    = 0x1,
    ME_MCS_DISCONNECTED = 0x2
};

class Mole : public QObject
{
    Q_OBJECT
    static Mole *instance;

public:
    static Mole *getInstance();
    ~Mole();

protected:
    explicit Mole(QObject *parent = 0);

private:
    me_mole_connection_status connectionStatus;
    me_mole_conversion_synchronization conversionSynchronization;

    static void samplesDataCallbackHandler(int mole_descriptor,
                                           uint8 first_address, uint8 last_address,
                                           uint8 channel_count, uint8 bytes_in_channel,
                                           uint8 bytes_in_module, uint16 bytes_in_line,
                                           me_mole_module_datarate datarate,
                                           me_mole_module_gain gain,
                                           uint16 samples, uint8 *samples_data);

    static void stageChangedCallbackHandler(int mole_descriptor,
                                            me_test_suite_stage test_suite_stage);

signals:
    void connectionStatusChanged(me_mole_connection_status connectionStatus);
    void conversionSynchronizationChanged(me_mole_conversion_synchronization conversionSynchronization);
    
public slots:
    int open();
    int close();
    int setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization);
};

#endif // MOLE_H
