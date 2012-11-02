#include <QDebug>
#include <QApplication>

#include "mole.h"

// Global pointer to Mole singleton object
Mole *ptrMole;

/*
 * samples data callback handler
 * @param int mole_descriptor
 * @param uint8 first_addres
 * @param uint8 last_address
 * @param uint8 channel_count
 * @param uint8 bytes_in_channel
 * @param uint8 bytes_in_module
 * @param uint6 bytes_in_line
 * @param me_mole_module_datarate datarate
 * @param me_mole_module_gain gain
 * @param uin16 samples
 * @param uint8 seismic_data
 *
 */
void Mole::samplesDataCallbackHandler(int mole_descriptor,
                                       uint8 first_address, uint8 last_address,
                                       uint8 channel_count, uint8 bytes_in_channel,
                                       uint8 bytes_in_module, uint16 bytes_in_line,
                                       me_mole_module_datarate datarate,
                                       me_mole_module_gain gain,
                                       uint16 samples, uint8 *seismic_data) {
    qDebug() << "me_ts_seismic_data_callback_handler called";

    int ret = ME_NO_ERROR;

    me_test_suite_stage test_suite_stage = ME_TSS_IDLE;
    ret = me_ts_get_stage(mole_descriptor, &test_suite_stage);

    if (ret < 0) {
        qDebug("Can't me_ts_get_stage (ret = 0x%.2x)\n", -ret);
        return;
    }

    switch(test_suite_stage) {
    case ME_TSS_GAIN_COEFFICIENTS_1: {
        //file_name += "/01. gain-coefficients-001";
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_2: {
        //file_name += "/01. gain-coefficients-002";
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_4: {
        //file_name += "/01. gain-coefficients-004";
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_8: {
        //file_name += "/01. gain-coefficients-008";
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_16: {
        //file_name += "/01. gain-coefficients-016";
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_32: {
        //file_name += "/01. gain-coefficients-032";
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_64: {
        //file_name += "/01. gain-coefficients-064";
    } break;
    case ME_TSS_NOISE_FLOOR: {
        //file_name += "/02. noise-floor";
    } break;
    case ME_TSS_TOTAL_HARMONIC_DISTORTION: {
        //file_name += "/03. total-harmonic-distortion";
    } break;
    case ME_TSS_ZERO_SHIFT: {
        //file_name += "/04. zero-shift";
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_SIN: {
        //file_name += "/05.01. common-mode-rejection-sin";
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_IN_PHASE: {
        //file_name += "/05.02 common-mode-rejection-in-phase";
    } break;
    default: {
        qDebug("Internal erorr?\n");
        return;
    }
    }
}

void Mole::stageChangedCallbackHandler(int mole_descriptor, me_test_suite_stage test_suite_stage) {
    qDebug() << "me_ts_stage_changed_callback_handler called";

    switch (test_suite_stage) {
    case ME_TSS_IDLE: {
        ptrMole->emitStageChanged(ME_TSS_IDLE);
        qDebug("ME_TSS_IDLE");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS);
        qDebug("ME_TSS_GAIN_COEFFICIENTS");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_1: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_1);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_1");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_2: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_2);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_2");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_4: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_4);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_4");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_8: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_8);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_8");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_16: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_16);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_16");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_32: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_32);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_32");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_64: {
        ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_64);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_64");
    } break;
    case ME_TSS_NOISE_FLOOR: {
        ptrMole->emitStageChanged(ME_TSS_NOISE_FLOOR);
        qDebug("ME_TSS_NOISE_FLOOR");
    } break;
    case ME_TSS_TOTAL_HARMONIC_DISTORTION: {
        ptrMole->emitStageChanged(ME_TSS_TOTAL_HARMONIC_DISTORTION);
        qDebug("ME_TSS_TOTAL_HARMONIC_DISTORTION");
    } break;
    case ME_TSS_ZERO_SHIFT: {
        ptrMole->emitStageChanged(ME_TSS_ZERO_SHIFT);
        qDebug("ME_TSS_ZERO_SHIFT");
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_SIN: {
        ptrMole->emitStageChanged(ME_TSS_COMMON_MODE_REJECTION_SIN);
        qDebug("ME_TSS_COMMON_MODE_REJECTION_SIN");
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_IN_PHASE: {
        ptrMole->emitStageChanged(ME_TSS_COMMON_MODE_REJECTION_IN_PHASE);
        qDebug("ME_TSS_COMMON_MODE_REJECTION_IN_PHASE");
    } break;
    default:
        qDebug("BUG: ME_TSS_COUNT");
    }
}

void Mole::emitStageChanged(me_test_suite_stage stage) {
    emit stageChanged(stage);
}

/*
 * Mole get instance
 */
Mole *Mole::getInstance() {
    if (!instance)
        instance = new Mole();
    return instance;
}

/*
 * Mole init
 */
Mole::Mole(QObject *parent) :
    QObject(parent)
{
    ptrMole = this;

    qDebug() << "Library version (git sha1): "  << me_get_version_git_sha1();
    qDebug() << "Library version (uint32): "    << me_get_version();
    qDebug() << "Library version (string): "    << me_get_version_string();
    qDebug() << "Library build date: "          << me_get_version_build_date();
    qDebug() << "Library build time: "          << me_get_version_build_time();

    this->descriptor = -1;
    int ret = 0;

    ret = me_init();

    if (ret < 0)
        qDebug("[Error] Can't me_init (ret=0x%.2x)\n", ret);
    else
        qDebug("[Success] init successfull\n");

    qDebug("me_init (ret=0x%.2x)", ret);
    qDebug("me_get_default_retries = %u\n", me_get_default_retries());

    me_ts_set_samples_data_callback(&Mole::samplesDataCallbackHandler);
    me_ts_set_stage_changed_callback(&Mole::stageChangedCallbackHandler);
}

Mole::~Mole() {
    int ret = 0;
    ret = me_destroy();

    if (ret < 0) {
        qDebug("[Error] Can't me_destroy (ret = 0x%.2x)", -ret);
        //return(-1);
    }
    else
        qDebug() << "[Success] me_destroy successfull\n";
}

/*
 * Mole get descriptor
 * @return int descriptor
 */
int Mole::getDescriptor() {
    return this->descriptor;
}

/*
 * Get device id
 * @return uint16 device id
 */
uint16 Mole::getDeviceId() {
    return this->deviceId;
}

/*
 * Get minor
 * @return uin8 minor
 */
uint8 Mole::getMinor() {
    return this->minor;
}

/*
 * Get minor
 * @return uin8 minor
 */
uint8 Mole::getMajor() {
    return this->major;
}

/*
 * Get first address
 * @return uint8 first address
 */
uint8 Mole::getFirstAddress() {
    return this->firstAddress;
}

/*
 * Get last address
 * @return uint8 last address
 */
uint8 Mole::getLastAddress() {
    return this->lastAddress;
}

/*
 * Get channel count
 * @return uint8 channel count
 */
uint8 Mole::getChannelCount() {
    return this->channelCount;
}

/*
 * Get bytes in channel
 * @return uint8 bytes in channel
 */
uint8 Mole::getBytesInChannel() {
    return this->bytesInChannel;
}

/*
 * Get bytes in module
 * @return uint8 bytes in module
 */
uint8 Mole::getBytesInModule() {
    return this->bytesInModule;
}

/*
 * Get bytes in line
 * @return uint16 bytes in line
 */
uint16 Mole::getBytesInLine() {
    return this->bytesInLine;
}

/*
 * Get maximum samples
 * @return uint16 maximum samples
 */
uint16 Mole::getMaximumSamples() {
    return this->maximumSamples;
}

/*
 * Get actual last address
 * @return uint8 actual last address
 */
uint8 Mole::getLastAddressActual() {
    return this->lastAddressActual;
}

/*
 * Mole open
 * @param const char *portString
 */
int Mole::open(const char *portString) {
    this->descriptor = me_open_mole(portString);

    if (this->descriptor < 0)
        qDebug("[Error] Can't open mole (ret = 0x%.2x)", -this->descriptor);
    else
        qDebug("[Success] open successfull\n");

    qDebug("mole_descriptor = %d", this->descriptor);

    //emit stateChange(MOLE_OPEN);
    //emit stateChange(tr("Mole opened at %1").arg(portString));

    return this->descriptor;
}

/*
 * Mole close
 */
int Mole::close() {
    int ret = 0;
    ret = me_close_mole(this->getDescriptor());

    if (ret < 0)
        qDebug("[Error] Can't close mole (ret = 0x%.2x)", -ret);
    else
        qDebug("[Success] close successfull\n");

    //emit stateChange(MOLE_CLOSE);
    //emit stateChange(tr("Mole closed"));
    return 0;
}

/*
 * Get Mole host info
 */
void Mole::getHostInfo() {
    int ret;

    ret =  me_host_info(descriptor, &deviceId, &minor, &major);
    qDebug("me_get_retries = %d", me_get_retries(descriptor));

    qDebug("device_id = %u minor = %u major = %u", deviceId, minor, major);

    if (ret < 0)
        qDebug("[Error] Can't me_host_info (ret = 0x%.2x)", -ret);
    else
        qDebug("[Success] getHostInfo successfull\n");
}

/*
 * Mole host mount
 */
int Mole::hostMount() {
    int ret;

    ret =  me_host_mount_all(descriptor,
                             &lastAddress,
                             &channelCount,
                             &bytesInChannel,
                             &bytesInModule,
                             &bytesInLine,
                             &maximumSamples);
    qDebug("me_get_retries = %d", me_get_retries(descriptor));

    qDebug("first_address = %u\nlast_address = %u\nchannel_count = %u\nbytes_in_channel = %u\nbytes_in_module = %u\nbytes_in_line = %u\nmaximum_samples = %u\n",
           firstAddress, lastAddress,channelCount,bytesInChannel,bytesInModule,bytesInLine,maximumSamples);

    if (ret < 0)
        qDebug("[Error] Can't me_host_mount_all (ret = 0x%.2x)\n", -ret);
    else {
        qDebug("[Success] hostMountAll successfull\n");
    }

    return ret;
}

void Mole::hostUnmount() {
    int ret = me_host_unmount(descriptor);
    if (ret < 0)
        qDebug("[Error] Can't me_host_unmount (ret = 0x%.2x)\n", -ret);
    else
        qDebug("[Success] hostUnmount sucessfull\n");
}

/*
 * Mole test gain coefficients
 * @param bool isSync
 */
void Mole::testGainCoefficients(bool isSync) {
    int ret;

    me_ts_result_gain_channel_t *results = new me_ts_result_gain_channel_t[me_get_module_count(firstAddress, lastAddress) * channelCount];
    switch (isSync) {
    case true: {
        ret = me_ts_gain_coefficients(descriptor,
                                      firstAddress, lastAddress, channelCount,
                                      bytesInChannel, bytesInModule, bytesInLine,
                                      results, &lastAddressActual);

        if (ret < 0)
            qDebug("[Error] Can't me_ts_gain_coefficients (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
        else
            qDebug("[Success] me_ts_gain_coefficients");
            qDebug("first_addres=%d, last_address=%d, channel_count=%d, results=%d", firstAddress, lastAddress, channelCount, results);
    } break;
    case false: {
        ret = me_ts_gain_coefficients_async(descriptor,
                                            firstAddress, lastAddress, channelCount,
                                            bytesInChannel, bytesInModule, bytesInLine,
                                            results, &lastAddressActual);

        if (ret < 0)
            qDebug("[Error] Can't me_ts_gain_coefficients_async (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
        else
        {
            qDebug("[Success] me_ts_gain_coefficients_async");
            //if (wait_test_with_error_handler(mole_descriptor))
            //    print_me_ts_get_result_gain(first_address, last_address, channel_count, results);
        }
    } break;
    };
    delete[] results;
}

/*
 * Mole test noise floor
 * @param bool isSync
 */
void Mole::testNoiseFloor(bool isSync) {
    int ret;

    uint8 first_address = 0;
    uint8 last_address = 0;
    uint8 channel_count = 0;
    uint8 bytes_in_channel = 0;
    uint8 bytes_in_module = 0;
    uint16 bytes_in_line = 0;
    //uint16 maximum_samples = 0;
    uint8 last_address_actual = 0;

    me_ts_result_channel_t *results = new me_ts_result_channel_t[me_get_module_count(first_address,last_address) * channel_count];
    switch (isSync) {
    case true: {
        ret = me_ts_noise_floor(this->getDescriptor(),
                                first_address, last_address, channel_count,
                                bytes_in_channel, bytes_in_module, bytes_in_line,
                                results, &last_address_actual);

        if (ret < 0)
            qDebug("Can't me_ts_noise_floor (last_address_actual = %d) (ret = 0x%.2x)\n", last_address_actual, -ret);
        else {
            /*
            save_summary_table((std::string(default_tests_folder) + std::string("/") + folder_name_date).c_str(),
                       first_address,last_address,channel_count,
                       results,
                       NULL,
                       NULL,
                       NULL,
                       raw_time);

            print_me_ts_get_result(first_address,last_address,channel_count,
                           results);
                           */
        }

        qDebug("sync");
    } break;
    case false: {
        ret = me_ts_noise_floor_async(this->getDescriptor(),
                                      first_address, last_address, channel_count,
                                      bytes_in_channel, bytes_in_module, bytes_in_line,
                                      results, &last_address_actual);

        if (ret < 0)
            qDebug("Can't me_ts_noise_floor_async (last_address_actual = %d) (ret = 0x%.2x)\n", last_address_actual, -ret);
        else {
            /*
            if( wait_test_with_error_handler(mole_descriptor)  )
            {
                save_summary_table((std::string(default_tests_folder) + std::string("/") + folder_name_date).c_str(),
                           first_address,last_address,channel_count,
                           results,
                           NULL,
                           NULL,
                           NULL,
                           raw_time);

                print_me_ts_get_result(first_address,last_address,channel_count,
                               results);
            }
            */
        }
        qDebug("async");
    } break;
    };

    delete[] results;
}

Mole *Mole::instance = NULL;
