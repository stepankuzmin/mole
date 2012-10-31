#include <QDebug>
#include "mole.h"

void samplesDataCallbackHandler(int mole_descriptor,
                                uint8 first_address, uint8 last_address,
                                uint8 channel_count, uint8 bytes_in_channel,
                                uint8 bytes_in_module, uint16 bytes_in_line,
                                me_mole_module_datarate datarate,
                                me_mole_module_gain gain,
                                uint16 samples, uint8 *seismic_data);
void stageChangedCallbackHandler(int mole_descriptor, me_test_suite_stage test_suite_stage);

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
void samplesDataCallbackHandler(int mole_descriptor,
                                      uint8 first_address, uint8 last_address,
                                      uint8 channel_count, uint8 bytes_in_channel,
                                      uint8 bytes_in_module, uint16 bytes_in_line,
                                      me_mole_module_datarate datarate,
                                      me_mole_module_gain gain,
                                      uint16 samples, uint8 *seismic_data) {
    qDebug() << "me_ts_seismic_data_callback_handler called";

    int ret = ME_NO_ERROR;

    me_test_suite_stage test_suite_stage = ME_TSS_IDLE;
    Mole *mole = Mole::getInstance();
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

void stageChangedCallbackHandler(int mole_descriptor, me_test_suite_stage test_suite_stage) {
    qDebug() << "me_ts_stage_changed_callback_handler called";

    switch (test_suite_stage) {
    case ME_TSS_IDLE: {
        qDebug("ME_TSS_IDLE");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_1: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_1");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_2: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_2");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_4: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_4");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_8: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_8");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_16: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_16");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_32: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_32");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_64: {
        qDebug("ME_TSS_GAIN_COEFFICIENTS_64");
    } break;
    case ME_TSS_NOISE_FLOOR: {
        qDebug("ME_TSS_NOISE_FLOOR");
    } break;
    case ME_TSS_TOTAL_HARMONIC_DISTORTION: {
        qDebug("ME_TSS_TOTAL_HARMONIC_DISTORTION");
    } break;
    case ME_TSS_ZERO_SHIFT: {
        qDebug("ME_TSS_ZERO_SHIFT");
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_SIN: {
        qDebug("ME_TSS_COMMON_MODE_REJECTION_SIN");
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_IN_PHASE: {
        qDebug("ME_TSS_COMMON_MODE_REJECTION_IN_PHASE");
    } break;
    default:
        qDebug("BUG: ME_TSS_COUNT");
    }
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
    // @TODO: me_destroy on destructor

    qDebug() << "Library version (git sha1): "  << me_get_version_git_sha1();
    qDebug() << "Library version (uint32): "    << me_get_version();
    qDebug() << "Library version (string): "    << me_get_version_string();
    qDebug() << "Library build date: "          << me_get_version_build_date();
    qDebug() << "Library build time: "          << me_get_version_build_time();

    this->descriptor = -1;
    int ret = 0;

    ret = me_init();

    if (ret < 0)
        qDebug("Can't me_init (ret=0x%.2x)\n", ret);
    qDebug("me_init (ret=0x%.2x)", ret);
    qDebug("me_get_default_retries = %u\n", me_get_default_retries());

    me_ts_set_samples_data_callback(&samplesDataCallbackHandler);
    me_ts_set_stage_changed_callback(&stageChangedCallbackHandler);
}

Mole::~Mole() {
    qDebug("mole destructed");
}

/*
 * Mole get descriptor
 * @return int descriptor
 */
int Mole::getDescriptor() {
    return this->descriptor;
}

/*
 * Mole open
 * @param const char *portString
 */
int Mole::open(const char *portString) {
    this->descriptor = me_open_mole(portString);

    if (this->descriptor < 0)
        qDebug("Can't open mole (ret = 0x%.2x)", -this->descriptor);

    qDebug("mole_descriptor = %d\n", this->descriptor);

    emit stateChange(MOLE_OPEN);
    emit stateChange(tr("Mole opened at %1").arg(portString));
    return 0;
}

/*
 * Mole close
 */
int Mole::close() {
    emit stateChange(MOLE_CLOSE);
    emit stateChange(tr("Mole closed"));
    return 0;
}


/*
 * Mole test gain coefficients
 * @param bool isSync
 */
void Mole::testGainCoefficients(bool isSync) {
    int ret;

    uint8 first_address = 0;
    uint8 last_address = 0;
    uint8 channel_count = 0;
    uint8 bytes_in_channel = 0;
    uint8 bytes_in_module = 0;
    uint16 bytes_in_line = 0;
    //uint16 maximum_samples = 0;
    uint8 last_address_actual = 0;

    me_ts_result_gain_channel_t *results = new me_ts_result_gain_channel_t[me_get_module_count(first_address,last_address) * channel_count];
    switch (isSync) {
    case true: {
        ret = me_ts_gain_coefficients(this->getDescriptor(),
                                      first_address, last_address, channel_count,
                                      bytes_in_channel, bytes_in_module, bytes_in_line,
                                      results, &last_address_actual);

        if (ret < 0)
            qDebug("Can't me_ts_gain_coefficients (last_address_actual = %d) (ret = 0x%.2x)\n", last_address_actual, -ret);
        else
            qDebug("ret > 0");
            //qDebug("%d, %d, %d, %d", first_address, last_address, channel_count, results);

        qDebug("sync");
        break;
    }
    case false: {
        ret = me_ts_gain_coefficients_async(this->getDescriptor(),
                                            first_address, last_address, channel_count,
                                            bytes_in_channel,bytes_in_module,bytes_in_line,
                                            results, &last_address_actual);

        if (ret < 0)
            qDebug("Can't me_ts_gain_coefficients_async (last_address_actual = %d) (ret = 0x%.2x)\n", last_address_actual, -ret);
        else
        {
            qDebug("ret > 0");
            //if (wait_test_with_error_handler(mole_descriptor))
            //    print_me_ts_get_result_gain(first_address, last_address, channel_count, results);
        }
        qDebug("async");
        break;
    }
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
