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
                                       uint16 samples, uint8 *samples_data) {
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

    QList<double> samplesList;
    QList<double> dataList;
    //QList<uint16> samplesList;
    //QList<int32> dataList;

    for(uint8 moduleIndex = 0; moduleIndex < me_get_module_count(first_address, last_address); ++moduleIndex) {
        for(uint8 channelIndex = 0; channelIndex < channel_count; ++channelIndex) {
            for (uint16 sample = 0; sample < samples; ++sample) {
                trace_data_t data = me_get_seismic_sample_data(moduleIndex, sample, channelIndex,
                                           first_address, last_address,
                                           bytes_in_channel, bytes_in_module, bytes_in_line,
                                           samples_data);
                samplesList << sample;
                dataList << data;
            }
            ptrMole->emitDataDump(moduleIndex, channelIndex,
                                  samples, samplesList, dataList);
            samplesList.clear();
            dataList.clear();
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

void Mole::emitDataDump(uint8 moduleIndex, uint8 channelIndex,
                         uint16 size, QList<double> samples, QList<double> data) {
    emit dataDump(moduleIndex, channelIndex, size, samples, data);
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

    this->moduleDatarate = ME_MMD_COUNT;
    this->moduleGain = ME_MMG_COUNT;
    this->moduleMode = ME_MMM_COUNT;
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
 * Get module datarate
 * @param me_mole_module_datarate datarate
 */
me_mole_module_datarate Mole::getModuleDatarate() {
    return this->moduleDatarate;
}

/*
 * Mole get module gain
 * @return me_mole_module_gain module gain
 */
me_mole_module_gain Mole::getModuleGain() {
    return this->moduleGain;
}

/*
 * Get module mode
 * @return me_mole_module_mode module mode
 */
me_mole_module_mode Mole::getModuleMode() {
    return this->moduleMode;
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
 * Set module mode
 * @param me_mole_module_mode moduleMode
 *
 * @return int
 */
int Mole::setModuleMode(me_mole_module_mode moduleMode) {
    int ret = 0;
    ret =  me_module_set_mode(this->descriptor, moduleMode, this->lastAddress, &this->lastAddressActual);
    if (ret < 0)
        qDebug("[Error] Can't me_module_set_mode (last_address_actual = %d) (ret = 0x%.2x)\n", this->lastAddressActual, -ret);
    else {
        this->moduleMode = moduleMode;
        qDebug("[Success] Set module mode");
    }

    return ret;
}

/*
 * Mole set gain for all modules
 * @param me_mole_module_gain moduleGain
 *
 * @return int ret
 */
int Mole::setModuleGainAll(me_mole_module_gain moduleGain) {
    int ret;
    ret =  me_module_set_gain_all(descriptor, moduleGain, lastAddress, &lastAddressActual);
    if(ret < 0)
        qDebug("[Error] Can't me_module_set_gain_all (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
    else
        qDebug("[Success] me_module_set_gain_all");

    return ret;
}

/*
 * Mole set gain for X all modules
 * @param me_mole_module_gain moduleGain
 *
 * @return int ret
 */
int Mole::setModuleGainXAll(me_mole_module_gain moduleGain) {
    int ret;
    ret =  me_module_set_gain_x_all(descriptor, moduleGain, lastAddress, &lastAddressActual);
    if(ret < 0)
        qDebug("[Error] Can't me_module_set_gain_x_all (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
    else
        qDebug("[Success] me_module_set_gain_x_all");

    return ret;
}

/*
 * Mole set gain for Y all modules
 * @param me_mole_module_gain moduleGain
 *
 * @return int ret
 */
int Mole::setModuleGainYAll(me_mole_module_gain moduleGain) {
    int ret;
    ret =  me_module_set_gain_y_all(descriptor, moduleGain, lastAddress, &lastAddressActual);
    if(ret < 0)
        qDebug("[Error] Can't me_module_set_gain_y_all (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
    else
        qDebug("[Success] me_module_set_gain_y_all");

    return ret;
}

/*
 * Mole set gain for Z all modules
 * @param me_mole_module_gain moduleGain
 *
 * @return int ret
 */
int Mole::setModuleGainZAll(me_mole_module_gain moduleGain) {
    int ret;
    ret =  me_module_set_gain_z_all(descriptor, moduleGain, lastAddress, &lastAddressActual);
    if(ret < 0)
        qDebug("[Error] Can't me_module_set_gain_z_all (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
    else
        qDebug("[Success] me_module_set_gain_z_all");

    return ret;
}

/*
 * Mole set datarate
 * @param me_mole_module_datarate moduleDatarate
 *
 * @return int ret
 */
int Mole::setModuleDatarate(me_mole_module_datarate moduleDatarate) {
    int ret = 0;
    ret =  me_module_set_datarate(this->descriptor, moduleDatarate, this->lastAddress,&this->lastAddressActual);
    if (ret < 0)
        qDebug("Can't me_module_set_datarate (last_address_actual = %d) (ret = 0x%.2x)\n", this->lastAddressActual, -ret);
    else {
        this->moduleDatarate = moduleDatarate;
        qDebug("[Success] Set module datarate");
    }

    return ret;
}

/*
 * Mole set test generator for all modules
 * @param me_mole_module_test_generator testGenerator
 *
 * @return int ret
 */
int Mole::setModuleTestGeneratorAll(me_mole_module_test_generator testGenerator) {
    int ret;
    ret =  me_module_set_test_generator_all(descriptor, testGenerator, lastAddress, &lastAddressActual);
    if (ret < 0)
        qDebug("[Error] Can't me_module_set_test_generator_all (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
    else
        qDebug("[Success] me_module_set_test_generator_all");

    return ret;
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

    return ret;
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
           firstAddress, lastAddress, channelCount, bytesInChannel, bytesInModule, bytesInLine, maximumSamples);

    if (ret < 0)
        qDebug("[Error] Can't me_host_mount_all (ret = 0x%.2x)\n", -ret);
    else {
        qDebug("[Success] hostMountAll successfull\n");
    }

    return ret;
}

int Mole::hostUnmount() {
    int ret = me_host_unmount(descriptor);
    if (ret < 0)
        qDebug("[Error] Can't me_host_unmount (ret = 0x%.2x)\n", -ret);
    else
        qDebug("[Success] hostUnmount sucessfull\n");

    return ret;
}


void pr_gain(uint8 firstAddress, uint8 lastAddress, uint8 channelCount, me_ts_result_gain_channel_t *results) {
    qDebug("print results: ");
    for(uint8 i = 0; i < me_get_module_count(firstAddress, lastAddress); ++i) {
        for(uint8 j = 0; j < channelCount; ++j) {
            qDebug("---> module %3u channel %u <---", i, j);

            for(uint8 k = 0; k < ME_MMG_COUNT; ++k) {
                char out_of_tolerance_sign = 0;

                if (me_ts_get_result_gain_channel(i, j, channelCount, results)->out_of_tolerance[k] )
                    out_of_tolerance_sign = '*';
                else
                    out_of_tolerance_sign = ' ';

                    qDebug("%2u (%f) %c ", me_ts_get_result_gain_channel(i, j, channelCount, results)->multiplier[k],
                                   me_ts_get_result_gain_channel(i, j, channelCount, results)->calculated_value[k],
                                   out_of_tolerance_sign);
            }
        }
    }
}

/*
 * Mole test gain coefficients
 * @param bool isSync
 *
 * @return int ret
 */
int Mole::testGainCoefficients(bool isSync) {
    int ret;

    me_ts_result_gain_channel_t *results = new me_ts_result_gain_channel_t[me_get_module_count(firstAddress, lastAddress) * channelCount];
    switch (isSync) {
    case true: {
        qDebug() << "sync gain coefficients";
        ret = me_ts_gain_coefficients(descriptor,
                                      firstAddress, lastAddress, channelCount,
                                      bytesInChannel, bytesInModule, bytesInLine,
                                      results, &lastAddressActual);

        if (ret < 0)
            qDebug("[Error] Can't me_ts_gain_coefficients (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
        else {
            qDebug("[Success] me_ts_gain_coefficients");
            pr_gain(firstAddress, lastAddress, channelCount, results);
            qDebug("first_addres=%d, last_address=%d, channel_count=%d, results=%d", firstAddress, lastAddress, channelCount, results);
        }
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
            //pr_gain(firstAddress, lastAddress, channelCount, results);
            //if (wait_test_with_error_handler(mole_descriptor))
            //    print_me_ts_get_result_gain(first_address, last_address, channel_count, results);
        }
    } break;
    };
    delete[] results;

    return ret;
}

/*
 * Mole test noise floor
 * @param bool isSync
 *
 * @return int ret
 */
int Mole::testNoiseFloor(bool isSync) {
    int ret;
    me_ts_result_channel_t *results = new me_ts_result_channel_t[me_get_module_count(firstAddress, lastAddress) * channelCount];
    switch(isSync) {
        case true: {
            ret = me_ts_noise_floor(descriptor, firstAddress, lastAddress, channelCount,
                                    bytesInChannel, bytesInModule, bytesInLine,
                                    results, &lastAddressActual);

            if (ret < 0)
                qDebug("[Error] Can't me_ts_noise_floor (last_address_actual = %d) (ret = 0x%.2x)\n",lastAddressActual, -ret);
            else {
                qDebug("[Success] me_ts_noise_floor");
            }
        } break;
        case false: {
            ret = me_ts_noise_floor_async(descriptor, firstAddress, lastAddress, channelCount,
                                          bytesInChannel, bytesInModule, bytesInLine,
                                          results, &lastAddressActual);

            if (ret < 0)
                qDebug("Can't me_ts_noise_floor_async (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
            else {
                qDebug("testNoiseFloor async success");
                //if (wait_test_with_error_handler(descriptor)) {
                //}
            }
        } break;
    }
    delete[] results;
    return ret;
}

/*
 * Mole test total harmonic distortion
 * @param bool isSync
 *
 * @return int ret;
 */
int Mole::testTotalHarmonicDistortion(bool isSync) {
    int ret;
    qDebug("---> test: total harmonic distortion\n");
    me_ts_result_channel_t *results = new me_ts_result_channel_t[me_get_module_count(firstAddress, lastAddress) * channelCount];
    switch(isSync) {
        case true: {
            ret = me_ts_total_harmonic_distortion(descriptor, firstAddress, lastAddress, channelCount,
                                                  bytesInChannel, bytesInModule, bytesInLine,
                                                  results, &lastAddressActual);

            if (ret < 0)
                qDebug("Can't me_ts_total_harmonic_distortion (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
            else {
                qDebug("[Success] me_ts_total_harmonic_distortion");
            }
        } break;
        case false: {
            ret = me_ts_total_harmonic_distortion_async(descriptor, firstAddress, lastAddress, channelCount,
                                    bytesInChannel, bytesInModule,bytesInLine,
                                    results, &lastAddressActual);

            if (ret < 0)
                qDebug("Can't me_ts_total_harmonic_distortion_async (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
            else {
                qDebug("[Success] me_ts_total_harmonic_distortion_async");
            }
        } break;
    }
    delete[] results;
    return ret;
}

/*
 * Mole test zero shift
 * @param bool isSync
 *
 * @return int ret
 */
int Mole::testZeroShift(bool isSync) {
    int ret;
    me_ts_result_channel_t *results = new me_ts_result_channel_t[me_get_module_count(firstAddress, lastAddress) * channelCount];
    switch(isSync) {
        case true: {
            ret = me_ts_zero_shift(descriptor, firstAddress, lastAddress, channelCount,
                                   bytesInChannel, bytesInModule, bytesInLine,
                                   results, &lastAddressActual);
            if (ret < 0)
                qDebug("[Error] Can't me_ts_zero_shift (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual,-ret);
            else {
                qDebug("[Success] me_ts_zero_shift");
            }
        } break;
        case false: {
            ret = me_ts_zero_shift_async(descriptor, firstAddress, lastAddress, channelCount,
                                         bytesInChannel, bytesInModule, bytesInLine,
                                         results, &lastAddressActual);
            if (ret < 0)
                qDebug("[Error] Can't me_ts_zero_shift_async (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual,-ret);
            else {
                qDebug("[Success] me_ts_zero_shift_async");
            }
        } break;
    }
    delete[] results;
    return ret;
}

/*
 * Mole test common mode rejection
 * @param bool isSync
 *
 * @return int ret
 */
int Mole::testCommonModeRejection(bool isSync) {
    int ret;
    me_ts_result_channel_t *results = new me_ts_result_channel_t[me_get_module_count(firstAddress, lastAddress) * channelCount];
    switch(isSync) {
        case true: {
            ret = me_ts_common_mode_rejection(descriptor, firstAddress, lastAddress, channelCount,
                                              bytesInChannel, bytesInModule, bytesInLine,
                                              results, &lastAddressActual);
            if (ret < 0)
                qDebug("[Error] Can't me_ts_common_mode_rejection (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
            else {
                qDebug("[Success] me_ts_common_mode_rejection");
            }
        } break;
        case false: {
            ret = me_ts_common_mode_rejection_async(descriptor, firstAddress, lastAddress, channelCount,
                                                    bytesInChannel, bytesInModule, bytesInLine,
                                                    results, &lastAddressActual);
            if (ret < 0)
                qDebug("[Error] Can't me_ts_common_mode_rejection_async (last_address_actual = %d) (ret = 0x%.2x)\n", lastAddressActual, -ret);
            else {
                qDebug("[Success] me_ts_common_mode_rejection_async");
            }
        } break;
    }
    delete[] results;
    return ret;
}

Mole *Mole::instance = NULL;
