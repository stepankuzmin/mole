#include "mole.h"

// Global pointer to Mole singleton object
Mole *ptrMole;

/*
 * Mole get singleton instance
 */
Mole *Mole::getInstance() {
    if (!instance)
        instance = new Mole();
    return instance;
}

/*
 * Mole constructor
 */
Mole::Mole(QObject *parent) :
    QObject(parent)
{
    ptrMole = this;

    qDebug("Library version (git sha1): %s",me_get_version_git_sha1());
    qDebug("Library version (uint32): %u",me_get_version());
    qDebug("Library version (string): %s",me_get_version_string());
    qDebug("Library build date: %s",me_get_version_build_date());
    qDebug("Library build time: %s",me_get_version_build_time());

    int mole_descriptor = -1;
    int ret = 0;

    ret = me_init();

    if( ret < 0 ) {
        qDebug("Can't me_init (ret = 0x%.2x)", -ret);
    }
    qDebug("me_get_default_retries = %u", me_get_default_retries());

    me_ts_set_samples_data_callback(&Mole::samplesDataCallbackHandler);
    me_ts_set_stage_changed_callback(&Mole::stageChangedCallbackHandler);

    // Set default values
    this->conversionSynchronization = ME_MCS_COUNT;
    setConversionSynchronization(this->conversionSynchronization);
}

/*
 * Mole destructor
 */
Mole::~Mole() {
    int ret = me_destroy();

    if (ret < 0)
        qDebug("[Error] Can't me_destroy (ret = 0x%.2x)", -ret);
    else
        qDebug("[Success] me_destroy successfull\n");
}

/////////////
// Private //
////////////

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
}

void Mole::stageChangedCallbackHandler(int mole_descriptor, me_test_suite_stage test_suite_stage) {
    qDebug() << "me_ts_stage_changed_callback_handler called";

    switch (test_suite_stage) {
    case ME_TSS_IDLE: {
        //ptrMole->emitStageChanged(ME_TSS_IDLE);
        qDebug("ME_TSS_IDLE");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS);
        qDebug("ME_TSS_GAIN_COEFFICIENTS");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_1: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_1);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_1");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_2: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_2);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_2");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_4: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_4);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_4");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_8: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_8);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_8");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_16: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_16);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_16");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_32: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_32);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_32");
    } break;
    case ME_TSS_GAIN_COEFFICIENTS_64: {
        //ptrMole->emitStageChanged(ME_TSS_GAIN_COEFFICIENTS_64);
        qDebug("ME_TSS_GAIN_COEFFICIENTS_64");
    } break;
    case ME_TSS_NOISE_FLOOR: {
        //ptrMole->emitStageChanged(ME_TSS_NOISE_FLOOR);
        qDebug("ME_TSS_NOISE_FLOOR");
    } break;
    case ME_TSS_TOTAL_HARMONIC_DISTORTION: {
        //ptrMole->emitStageChanged(ME_TSS_TOTAL_HARMONIC_DISTORTION);
        qDebug("ME_TSS_TOTAL_HARMONIC_DISTORTION");
    } break;
    case ME_TSS_ZERO_SHIFT: {
        //ptrMole->emitStageChanged(ME_TSS_ZERO_SHIFT);
        qDebug("ME_TSS_ZERO_SHIFT");
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_SIN: {
        //ptrMole->emitStageChanged(ME_TSS_COMMON_MODE_REJECTION_SIN);
        qDebug("ME_TSS_COMMON_MODE_REJECTION_SIN");
    } break;
    case ME_TSS_COMMON_MODE_REJECTION_IN_PHASE: {
        //ptrMole->emitStageChanged(ME_TSS_COMMON_MODE_REJECTION_IN_PHASE);
        qDebug("ME_TSS_COMMON_MODE_REJECTION_IN_PHASE");
    } break;
    default:
        qDebug("BUG: ME_TSS_COUNT");
    }
}

//////////////////
// Public slots //
//////////////////

/*
 * Set conversion synchronization
 */
int Mole::setConversionSynchronization(me_mole_conversion_synchronization conversionSynchronization) {
    switch (conversionSynchronization) {
        case ME_MCS_COUNT:      qDebug() << "Conversion synchronization changed to ME_MCS_COUNT"; break;
        case ME_MCS_SOFT:       qDebug() << "Conversion synchronization changed to ME_MCS_SOFT"; break;
        case ME_MCS_EXTERNAL:   qDebug() << "Conversion synchronization changed to ME_MCS_EXTERNAL"; break;
    }

    this->conversionSynchronization = conversionSynchronization;
    emit conversionSynchronizationChanged(conversionSynchronization);

    return 0;
}

Mole *Mole::instance = NULL;
