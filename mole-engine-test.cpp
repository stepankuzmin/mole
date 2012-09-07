#include <QLibrary>
#include <QDebug>

//#include "test-mole-engine.h"
#include "mole-engine/mole-engine.h"
#include "mole-engine/mole-engine-test-suite.h"

void me_ts_seismic_data_callback_handler(int mole_descriptor,
                                         uint8 first_address, uint8 last_address,
                                         uint8 channel_count, uint8 bytes_in_channel,
                                         uint8 bytes_in_module, uint16 bytes_in_line,
                                         me_mole_module_datarate datarate,
                                         me_mole_module_gain gain,
                                         uint16 samples, uint8 *seismic_data) {
    qDebug() << "me_ts_seismic_data_callback_handler called";
}

void me_ts_stage_changed_callback_handler(int mole_descriptor,
                                          me_test_suite_stage test_suite_stage) {
    qDebug() << "me_ts_stage_changed_callback_handler called";
}

int mole_engine_test(void) {
    QLibrary me("mole-engine");

    typedef const char* (*me_get_version_git_sha1_prototype)();
    typedef const uint32_t (*me_get_version_prototype)();
    typedef const char* (*me_get_version_string_prototype)();
    typedef const char* (*me_get_version_build_date_prototype)();
    typedef const char* (*me_get_version_build_time_prototype)();
    typedef int (*me_init_prototype)();
    typedef int (*me_destroy_prototype)();
    typedef uint32_t (*me_get_default_retries_prototype)();
    typedef void (*me_ts_set_seismic_data_callback_prototype)(me_ts_seismic_data_callback_t callback);
    typedef int (*me_open_mole_prototype)(const char *port_string);

    me_get_version_git_sha1_prototype me_get_version_git_sha1 = (me_get_version_git_sha1_prototype) me.resolve("me_get_version_git_sha1");
    me_get_version_prototype me_get_version = (me_get_version_prototype) me.resolve("me_get_version");
    me_get_version_string_prototype me_get_version_string = (me_get_version_string_prototype) me.resolve("me_get_version_string");
    me_get_version_build_date_prototype me_get_version_build_date = (me_get_version_build_date_prototype) me.resolve("me_get_version_build_date");
    me_get_version_build_time_prototype me_get_version_build_time = (me_get_version_build_time_prototype) me.resolve("me_get_version_build_time");
    me_init_prototype me_init = (me_init_prototype) me.resolve("me_init");
    me_destroy_prototype me_destroy = (me_destroy_prototype) me.resolve("me_destroy");
    me_get_default_retries_prototype me_get_default_retries = (me_get_default_retries_prototype) me.resolve("me_get_default_retries");
    me_open_mole_prototype me_open_mole = (me_open_mole_prototype) me.resolve("me_open_mole");

    if (me_get_version_git_sha1)
        qDebug() << "me_get_version_git_sha1" << me_get_version_git_sha1();

    if (me_get_version)
        qDebug() << "me_get_version" << me_get_version();

    if (me_get_version_string)
        qDebug() << "me_get_version_string" << me_get_version_string();

    if (me_get_version_build_date)
        qDebug() << "me_get_version_build_date" << me_get_version_build_date();

    if (me_get_version_build_time)
        qDebug() << "me_get_version_build_time" << me_get_version_build_time();

    int mole_descriptor = -1;
    int ret = 0;

    if (me_init)
        ret = me_init(), qDebug() << "me_init" << ret;

    if (ret < 0)
        qDebug() << "Can't me_init(), ret=" << ret;

    if (me_get_default_retries)
        qDebug() << "me_get_default_retries" << me_get_default_retries();

    me_ts_set_seismic_data_callback(&me_ts_seismic_data_callback_handler);
    me_ts_set_stage_changed_callback(&me_ts_stage_changed_callback_handler);

    if (me_open_mole)
        mole_descriptor = me_open_mole("COM3");

    if (mole_descriptor < 0) {
        qDebug() << "Can't me_open_mole(), mole_descriptor=" << mole_descriptor;
        return(-1);
    }
    return 0;
}
