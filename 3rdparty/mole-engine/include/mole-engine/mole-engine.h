#ifndef MOLE_ENGINE_H
#define MOLE_ENGINE_H

#include "3rdparty/mole-engine/include/shared/common.h"
#include "3rdparty/mole-engine/include/seg/Segy.h"

typedef int32 angle_data_t;

enum me_mole_errors
{
	ME_NO_ERROR				= 0,
	
									// Библиотека
	ME_LIBRARY_TOO_MANY_MOLE		= -0x01,		// "Нет свободных дескрипторов"
	ME_LIBRARY_BAD_MOLE_DESCRIPTOR		= -0x02,		// "Такой дескриптор не выдавался"
	ME_LIBRARY_CANT_OPEN_MOLE		= -0x03,		// "Не могу открыть крота"
	ME_LIBRARY_CANT_CLOSE_MOLE		= -0x04,		// "Не могу закрыть крота"
	ME_LIBRARY_CANT_SYNCHRONIZATION_IO	= -0x05,		// "Не могу синхронизировать обмен данными"
	ME_LIBRARY_CANT_SEND_PACKET		= -0x06,		// "Не могу отправить пакет"
	ME_LIBRARY_CANT_RECEIVE_PACKET		= -0x07,		// "Не могу получить пакет"
	ME_LIBRARY_BAD_PACKET_CRC		= -0x08,		// "Неправильная контрольная сумма у принятого пакета"
	ME_LIBRARY_WRONG_COMMAND_IN_RESPONSE	= -0x09,		// "Получен ответ на другую команду"
	ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE	= -0x0A,		// "Получен ответ с полями, значения которых отличаются от значений полей в запросе"
	ME_LIBRARY_CANT_INIT_MUTEX		= -0x0B,		// "Не могу проинициализировать mutex"
	ME_LIBRARY_CANT_DESTROY_MUTEX		= -0x0C,		// "Не могу уничтожить mutex"
	ME_LIBRARY_CANT_CREATE_THREAD		= -0x0D,		// "Не могу создать поток"
	
									// Тесты
	ME_TS_CANT_GET_ENOUGH_SAMPLES		= -0x10,		// "Не удалось зарегистрировать необходимое число отсчётов"
	ME_TS_MODULES_NOT_IN_SEISMIC		= -0x11,		// "При регистрации данных модули не в режиме ME_MMM_SEISMIC"
	
									// Железо
	ME_HARDWARE_MAX				= -0xF0,		// "Слишком длинный пакет"
	ME_HARDWARE_MIN				= -0xF1,		// "Пакет содержит менее 3-х байт"
	ME_HARDWARE_CRC				= -0xF2,		// "Ошибка контрольной суммы"
	ME_HARDWARE_LENGTH			= -0xF3,		// "Неправильная длина пакета"
	ME_HARDWARE_FORMAT			= -0xF4,		// "Ошибка в параметрах команды"
	ME_HARDWARE_EXECUTE			= -0xF5,		// "Ошибка исполнения команды" Смотри uint8 *last_address_actual.
	ME_HARDWARE_TIMEOUT			= -0xF6,		// "Истёк таймаут" Смотри uint8 *last_address_actual.
	ME_HARDWARE_UNEXPECT_CMD		= -0xF7,		// "Непредусмотренная команда"
	ME_HARDWARE_NOT_MOUNT			= -0xF8,		// "ЛИНИЯ не смонтирована"
	ME_HARDWARE_NOT_MODULE			= -0xF9,		// "Модуль с данным адресом отсутствует (0 или > 240)"
	ME_HARDWARE_INVALID_ADDR		= -0xFA,		// "Недопустимый адрес"
	ME_HARDWARE_MAX_SAMPLES			= -0xFB,		// "Недопустимое количество отсчетов"
	ME_HARDWARE_PLL_TIME			= -0xFC,		// "Не истек таймаут для PLL после монтирования ЛИНИИ"
	ME_HARDWARE_MODULE_MODE			= -0xFD,		// "Получена команда, недопустимая текущем режиме модулей"
};

enum me_mole_module_mode
{
	ME_MMM_SLEEP				= 0x00,			// "� ежим сохранения энергии"
	ME_MMM_SEISMIC				= 0x01,			// "� ежим измерения сейсмических параметров"
	ME_MMM_INCLINOMETER			= 0x02,			// "� ежим измерения углов"
	ME_MMM_COUNT				= 0x03,
};

enum me_mole_module_test_generator
{
	ME_MMTG_OFF				= 0x00,
	ME_MMTG_ON				= 0x01,
	ME_MMTG_COUNT				= 0x02,
};

enum me_mole_module_datarate
{
	ME_MMD_250				= 0x00,
	ME_MMD_500				= 0x01,
	ME_MMD_1000				= 0x02,
	ME_MMD_2000				= 0x03,
	ME_MMD_4000				= 0x04,
	ME_MMD_COUNT				= 0x05,
};

enum me_mole_module_gain
{
	ME_MMG_1				= 0x00,
	ME_MMG_2				= 0x01,
	ME_MMG_4				= 0x02,
	ME_MMG_8				= 0x03,
	ME_MMG_16				= 0x04,
	ME_MMG_32				= 0x05,
	ME_MMG_64				= 0x06,
	ME_MMG_COUNT				= 0x07,
};

enum me_mole_module_input
{
	ME_MMI_TERMINATOR			= 0x00,
	ME_MMI_GEOPHONE				= 0x01,
	ME_MMI_SIN				= 0x02,
	ME_MMI_IN_PHASE				= 0x03,
	ME_MMI_GEOPHONE_WITH_SIN		= 0x04,
	ME_MMI_COUNT				= 0x05,
};

enum me_mole_module_resolution
{
	ME_MMR_LOW_POWER_MODE			= 0x00,
	ME_MMR_HIGH_RESOLUTION_MODE		= 0x01,
	ME_MMR_COUNT				= 0x02,
};

enum me_mole_module_high_pass_filter
{
	ME_MMHPF_OFF				= 0x00,
	ME_MMHPF_RAW_VALUE_1			= 0x01,
	ME_MMHPF_RAW_VALUE_2			= 0x02,
	ME_MMHPF_RAW_VALUE_3			= 0x03,
	ME_MMHPF_RAW_VALUE_4			= 0x04,
	ME_MMHPF_RAW_VALUE_5			= 0x05,
	ME_MMHPF_RAW_VALUE_6			= 0x06,
	ME_MMHPF_RAW_VALUE_7			= 0x07,
	ME_MMHPF_RAW_VALUE_8			= 0x08,
	ME_MMHPF_RAW_VALUE_9			= 0x09,
	ME_MMHPF_RAW_VALUE_10			= 0x0A,
	ME_MMHPF_RAW_VALUE_11			= 0x0B,
	ME_MMHPF_RAW_VALUE_12			= 0x0C,
	ME_MMHPF_RAW_VALUE_13			= 0x0D,
	ME_MMHPF_RAW_VALUE_14			= 0x0E,
	ME_MMHPF_RAW_VALUE_15			= 0x0F,
	ME_MMHPF_RAW_VALUE_16			= 0x10,
	ME_MMHPF_RAW_VALUE_17			= 0x11,
	ME_MMHPF_RAW_VALUE_18			= 0x12,
	ME_MMHPF_RAW_VALUE_19			= 0x13,
	ME_MMHPF_RAW_VALUE_20			= 0x14,
	ME_MMHPF_COUNT				= 0x15,
	
};

enum me_mole_conversion_synchronization
{
	ME_MCS_SOFT				= 0x00,
	ME_MCS_EXTERNAL				= 0x01,
	ME_MCS_COUNT				= 0x02,
};

enum me_mole_host_state
{
	ME_MHS_IDLE				= 0x00,
	ME_MHS_CONFIGURE_MODULES		= 0x01,
	ME_MHS_CONVERSION			= 0x02,
	ME_MHS_TEST				= 0x03,
	ME_MHS_COUNT				= 0x04,
};

enum me_mole_library_state
{
	ME_MLS_IDLE				= 0x00,
	ME_MLS_HOST_GET_SAMPLES_DATA		= 0x01,
	ME_MLS_TS_GAIN_COEFFICIENTS		= 0x02,
	ME_MLS_TS_NOISE_FLOOR			= 0x03,
	ME_MLS_TS_TOTAL_HARMONIC_DISTORTION	= 0x04,
	ME_MLS_TS_ZERO_SHIFT			= 0x05,
	ME_MLS_TS_COMMON_MODE_REJECTION		= 0x06,
	ME_MLS_COUNT				= 0x07,
};

inline me_mole_module_datarate me_datarate_to_raw_value(uint16 datarate)
{
	switch(datarate)
	{
		case 250:
		{
			return(ME_MMD_250);
		}
		
		case 500:
		{
			return(ME_MMD_500);
		}
		
		case 1000:
		{
			return(ME_MMD_1000);
		}
		
		case 2000:
		{
			return(ME_MMD_2000);
		}
		
		case 4000:
		{
			return(ME_MMD_4000);
		}
		
		default:
			return(ME_MMD_COUNT);
	}
}

inline uint16 me_raw_value_to_datarate(me_mole_module_datarate datarate)
{
	switch(datarate)
	{
		case ME_MMD_250:
		{
			return(250);
		}
		
		case ME_MMD_500:
		{
			return(500);
		}
		
		case ME_MMD_1000:
		{
			return(1000);
		}
		
		case ME_MMD_2000:
		{
			return(2000);
		}
		
		case ME_MMD_4000:
		{
			return(4000);
		}
		
		default:
			return(0);
	}
}

inline me_mole_module_gain me_gain_multiplier_to_raw_value(uint16 multiplier)
{
	switch(multiplier)
	{
		// 1 multiplier --- 0 db
		case 1:
		{
			return(ME_MMG_1);
		}
		
		// 2 multiplier --- 6 db
		case 2:
		{
			return(ME_MMG_2);
		}
		
		// 4 multiplier --- 12 db
		case 4:
		{
			return(ME_MMG_4);
		}
		
		// 8 multiplier --- 18 db
		case 8:
		{
			return(ME_MMG_8);
		}
		
		// 16 multiplier --- 24 db
		case 16:
		{
			return(ME_MMG_16);
		}
		
		// 32 multiplier --- 30 db
		case 32:
		{
			return(ME_MMG_32);
		}
		
		// 64 multiplier --- 36 db
		case 64:
		{
			return(ME_MMG_64);
		}
		
		default:
			return(ME_MMG_COUNT);
	}
}

inline uint16 me_gain_raw_value_multiplier(me_mole_module_gain raw_value)
{
	switch(raw_value)
	{
		// 1 multiplier --- 0 db
		case ME_MMG_1:
		{
			return(1);
		}
		
		// 2 multiplier --- 6 db
		case ME_MMG_2:
		{
			return(2);
		}
		
		// 4 multiplier --- 12 db
		case ME_MMG_4:
		{
			return(4);
		}
		
		// 8 multiplier --- 18 db
		case ME_MMG_8:
		{
			return(8);
		}
		
		// 16 multiplier --- 24 db
		case ME_MMG_16:
		{
			return(16);
		}
		
		// 32 multiplier --- 30 db
		case ME_MMG_32:
		{
			return(32);
		}
		
		// 64 multiplier --- 36 db
		case ME_MMG_64:
		{
			return(64);
		}
		
		default:
			return(0);
	}
}

inline me_mole_module_gain me_gain_db_to_raw_value(uint16 gain)
{
	switch(gain)
	{
		// 1 multiplier --- 0 db
		case 0:
		{
			return(ME_MMG_1);
		}
		
		// 2 multiplier --- 6 db
		case 6:
		{
			return(ME_MMG_2);
		}
		
		// 4 multiplier --- 12 db
		case 12:
		{
			return(ME_MMG_4);
		}
		
		// 8 multiplier --- 18 db
		case 18:
		{
			return(ME_MMG_8);
		}
		
		// 16 multiplier --- 24 db
		case 24:
		{
			return(ME_MMG_16);
		}
		
		// 32 multiplier --- 30 db
		case 30:
		{
			return(ME_MMG_32);
		}
		
		// 64 multiplier --- 36 db
		case 36:
		{
			return(ME_MMG_64);
		}
		
		default:
			return(ME_MMG_COUNT);
	}
}

inline uint16 me_gain_raw_value_to_db(me_mole_module_gain raw_value)
{
	switch(raw_value)
	{
		// 1 multiplier --- 0 db
		case ME_MMG_1:
		{
			return(0);
		}
		
		// 2 multiplier --- 6 db
		case ME_MMG_2:
		{
			return(6);
		}
		
		// 4 multiplier --- 12 db
		case ME_MMG_4:
		{
			return(12);
		}
		
		// 8 multiplier --- 18 db
		case ME_MMG_8:
		{
			return(18);
		}
		
		// 16 multiplier --- 24 db
		case ME_MMG_16:
		{
			return(24);
		}
		
		// 32 multiplier --- 30 db
		case ME_MMG_32:
		{
			return(30);
		}
		
		// 64 multiplier --- 36 db
		case ME_MMG_64:
		{
			return(36);
		}
		
		default:
			return(-1);
	}
}

inline uint16 me_gain_db_to_multiplier(uint16 gain)
{
	switch(gain)
	{
		// 1 multiplier --- 0 db
		case 0:
		{
			return(1);
		}
		
		// 2 multiplier --- 6 db
		case 6:
		{
			return(2);
		}
		
		// 4 multiplier --- 12 db
		case 12:
		{
			return(4);
		}
		
		// 8 multiplier --- 18 db
		case 18:
		{
			return(8);
		}
		
		// 16 multiplier --- 24 db
		case 24:
		{
			return(16);
		}
		
		// 32 multiplier --- 30 db
		case 30:
		{
			return(32);
		}
		
		// 64 multiplier --- 36 db
		case 36:
		{
			return(64);
		}
		
		default:
			return(1);
	}
}

inline uint8 me_get_module_count(uint8 first_address,uint8 last_address)
{
	return(last_address - first_address + 1);
}

/**
 * Возвращает заданный отсчёт сейсмических данных выбранного канала указанного модуля.
 * 
 * channel_index:
 * 
 * 0 - X
 * 1 - Y
 * 2 - Z
 * 
 * Смотри me_host_get_samples_data.
 */
inline trace_data_t me_get_seismic_sample_data(uint8 module_index,uint16 sample,uint8 channel_index,
					       uint8 first_address,uint8 last_address,
					       uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
					       const uint8 *samples_data)
{
	return(*(trace_data_t*)&samples_data[bytes_in_line * sample +
					     bytes_in_module * (me_get_module_count(first_address,last_address) - module_index - 1) +
					     bytes_in_channel * channel_index]);
}

/**
 * Возвращает заданный отсчёт данных инклинометра выбранного канала указанного модуля.
 * 
 * channel_index:
 * 
 * 0 - α
 * 1 - β
 * 2 - γ
 * 
 * β - всегда 0, так как нет реализации в модулях.
 * 
 * Смотри me_host_get_samples_data.
 */
inline angle_data_t me_get_inclinometer_sample_data(uint8 module_index,uint8 channel_index,
					       uint8 first_address,uint8 last_address,
					       uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
					       const uint8 *inclinometer_data)
{
	return(*(angle_data_t*)&inclinometer_data[bytes_in_line * 0 +
						  bytes_in_module * (me_get_module_count(first_address,last_address) - module_index - 1) +
						  bytes_in_channel * channel_index]);
}

/**
 * Получить хэш sha1 ревизии git'а из которой собрана библиотека.
 * Однозначно определяет из каких исходников была собрана библиотека.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL const char *me_get_version_git_sha1();

/**
 * Получить uint32 версию библиотеки. Пример: 100
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL const uint32 me_get_version();

/**
 * Получить версию библиотеки в виде строки. Пример: 1.0.0
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL const char *me_get_version_string();

/**
 * Получить дату сборки библиотеки в виде строки. Пример: Jul 16 2012
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL const char *me_get_version_build_date();

/**
 * Получить время сборки библиотеки в виде строки. Пример: 10:19:46
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL const char *me_get_version_build_time();


/**
 * Произвести внутреннюю инициализацию библиотеки.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_init();

/**
 * Произвести внутреннюю деинициализацию библиотеки.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_destroy();


/**
 * Установить число повторов для функций, которое они будут повторяться, перед тем как вернуть ошибку.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL void me_set_default_retries(uint16 retries);

/**
 * Получить установленное число повторов.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL uint16 me_get_default_retries();

/**
 * Получить число повторов выполненной функции.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_get_retries(int mole_descriptor);


/**
 * Открыть крота.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_open_mole(const char *port_string);

/**
 * Закрыть крота.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_close_mole(int mole_descriptor);


/**
 * Получить информацию о прошивке крота.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_info(int mole_descriptor,uint16 *device_id,uint8 *minor,uint8 *major);


/**
 * Примонтировать линию с заданным количеством модулей.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_mount(int mole_descriptor,uint8 first_address,uint8 *last_address,uint8 *channel_count,
								  uint8 *bytes_in_channel,uint8 *bytes_in_module,uint16 *bytes_in_line,uint16 *maximum_samples);

/**
 * Примонтировать линию со всеми модулями.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_mount_all(int mole_descriptor,uint8 *last_address,uint8 *channel_count,
								      uint8 *bytes_in_channel,uint8 *bytes_in_module,uint16 *bytes_in_line,uint16 *maximum_samples);

/**
 * Отмонтировать линию.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_unmount(int mole_descriptor);


/**
 * Получить информацию о прошивке модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_info(int mole_descriptor,uint8 module_address,uint16 *device_id,uint8 *minor,uint8 *major);


/**
 * Установить режим работы модулей. Смотри me_mole_module_mode.
 * 
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_mode(int mole_descriptor,me_mole_module_mode module_mode,uint8 last_address,uint8 *last_address_actual);


/**
 * Установить режим работы тестового генератора для модуля. Смотри me_mole_module_test_generator.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_test_generator(int mole_descriptor,uint8 module_address,me_mole_module_test_generator test_generator,uint8 *last_address_actual);

/**
 * Установить режим работы тестового генератора для всех модулей. Смотри me_mole_module_test_generator.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_test_generator_all(int mole_descriptor,me_mole_module_test_generator test_generator,uint8 last_address,uint8 *last_address_actual);


/**
 * Установить частоту дискретизации. Смотри me_mole_module_datarate.
 * 
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_datarate(int mole_descriptor,me_mole_module_datarate datarate,uint8 last_address,uint8 *last_address_actual);


/**
 * Установить коэффициент усиления для модуля. Смотри me_mole_module_gain.
 * 
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_gain(int mole_descriptor,uint8 module_address,me_mole_module_gain gain,uint8 *last_address_actual);

/**
 * Установить коэффициент усиления для всех модулей. Смотри me_mole_module_gain.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_gain_all(int mole_descriptor,me_mole_module_gain gain,uint8 last_address,uint8 *last_address_actual);

/**
 * Установить коэффициент усиления для X канала (X компоненты) всех модулей. Смотри me_mole_module_gain.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_gain_x_all(int mole_descriptor,me_mole_module_gain gain,uint8 last_address,uint8 *last_address_actual);

/**
 * Установить коэффициент усиления для Y канала (Y компоненты) всех модулей. Смотри me_mole_module_gain.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_gain_y_all(int mole_descriptor,me_mole_module_gain gain,uint8 last_address,uint8 *last_address_actual);

/**
 * Установить коэффициент усиления для Z канала (Z компоненты) всех модулей. Смотри me_mole_module_gain.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_gain_z_all(int mole_descriptor,me_mole_module_gain gain,uint8 last_address,uint8 *last_address_actual);


/**
 * Установить тип входного сигнала для модуля. Смотри me_mole_module_input.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_input(int mole_descriptor,uint8 module_address,me_mole_module_input input,uint8 *last_address_actual);

/**
 * Установить тип входного сигнала для всех модулей. Смотри me_mole_module_input.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_input_all(int mole_descriptor,me_mole_module_input input,uint8 last_address,uint8 *last_address_actual);


/**
 * Установить разрешение АЦП для всех модулей. Смотри me_mole_module_resolution.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_resolution_all(int mole_descriptor,me_mole_module_resolution resolution,uint8 last_address,uint8 *last_address_actual);


/**
 * Установить частоту среза ФВЧ для всех модулей. Смотри me_mole_module_high_pass_filter.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_set_high_pass_filter_all(int mole_descriptor,me_mole_module_high_pass_filter high_pass_filter,uint8 last_address,uint8 *last_address_actual);


/**
 * Произвести калибровку оффсетов для всех модулей.
 *  
 * last_address_actual - содержит адрес модуля в линии к которому последним было произведено обращение. При ошибках ME_HARDWARE_EXECUTE и
 * ME_HARDWARE_TIMEOUT будет означать адрес модуля с которым произошла данная ошибка. При ошибке ME_LIBRARY_WRONG_SOMETHING_IN_RESPONCE
 * может принимать неопределённое значение. В остальных случаях  равно адресу (last_address) последнего смонтированного модуля.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_module_do_offset_calibration_all(int mole_descriptor,uint8 last_address,uint8 *last_address_actual);


/**
 * Начать регистрацию данных.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_start_conversion(int mole_descriptor,uint16 samples,me_mole_conversion_synchronization conversion_synchronization);

/**
 * Дострочно остановить регистрацию данных.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_stop_conversion(int mole_descriptor);


/**
 * Получить информацию о состоянии крота: состоние крота, режим работы модулей, количество отсчётов, зарегистрированных кротом на текущий момент.
 * Смотри me_mole_host_state и me_mole_module_mode.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_state(int mole_descriptor,me_mole_host_state *host_state,me_mole_module_mode *modules_mode,uint16 *samples_in_buffer);

/**
 * Прочитать заданное число отсчётов из крота (блокирующее чтение - вернёт управление программе только после вычитывания заданного числа отсчётов).
 * 
 * � асположение сейсмических данных в буфере:
 * 
 * <отсчёт 0 <последний модуль <X> <Y> <Z>> <последний модуль - 1 <X> <Y> <Z>> ... <первый модуль <X> <Y> <Z>>>
 * <отсчёт 1 <последний модуль <X> <Y> <Z>> <последний модуль - 1 <X> <Y> <Z>> ... <первый модуль <X> <Y> <Z>>> 
 * ...
 * <отсчёт N <последний модуль <X> <Y> <Z>> <последний модуль - 1 <X> <Y> <Z>> ... <первый модуль <X> <Y> <Z>>>
 * 
 * � асположение данных с инклинометров в буфере:
 * 
 * Для того чтобы получить данные с инклинометров, необходимо прочитать только один отсчёт, т.е. samples = 1
 * 
 * <отсчёт 0 <последний модуль <α> <β> <γ>> <последний модуль - 1 <α> <β> <γ>> ... <первый модуль <α> <β> <γ>>>
 * 
 * β - всегда 0, так как нет реализации в модулях.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_get_samples_data(int mole_descriptor,uint16 samples,uint8 *samples_data);

/**
 * Прочитать заданное число отсчётов из крота (асинхронное чтение - вернёт управление программе управление сразу).
 * 
 * � асположение сейсмических данных в буфере:
 * 
 * <отсчёт 0 <последний модуль <X> <Y> <Z>> <последний модуль - 1 <X> <Y> <Z>> ... <первый модуль <X> <Y> <Z>>>
 * <отсчёт 1 <последний модуль <X> <Y> <Z>> <последний модуль - 1 <X> <Y> <Z>> ... <первый модуль <X> <Y> <Z>>> 
 * ...
 * <отсчёт N <последний модуль <X> <Y> <Z>> <последний модуль - 1 <X> <Y> <Z>> ... <первый модуль <X> <Y> <Z>>>
 * 
 * � асположение данных с инклинометров в буфере:
 * 
 * Для того чтобы получить данные с инклинометров, необходимо прочитать только один отсчёт, т.е. samples = 1
 * 
 * <отсчёт 0 <последний модуль <α> <β> <γ>> <последний модуль - 1 <α> <β> <γ>> ... <первый модуль <α> <β> <γ>>>
 * 
 * β - всегда 0, так как нет реализации в модулях.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_host_get_samples_data_async(int mole_descriptor,uint16 samples,uint8 *samples_data);

/**
 * Получить число отсчётов, прочитанных функцией me_host_get_samples_data из крота на текущий момент.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_get_read_samples(int mole_descriptor,uint16 *samples);


/**
 * Получить опорное напряжение АЦП в вольтах
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL double me_get_adc_reference_voltage();

/**
 * Получить разрядность АЦП в битах
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL uint8 me_get_adc_resolution();

/**
 * Получить вес одного разряда АЦП в микровольтах
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL double me_get_adc_lsb_weight();

/**
 * Получить вес одного разряда инклинометра в градусах
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL double me_get_inclinometer_lsb_weight();

/**
 * Получить амплитуду тестового сигнала в микровольтах
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL double me_get_test_signal_amplitude();

/**
 * Получить информацию о том, какая асинхронная операция выполняется в данный момент над кротом.
 * Смотри me_mole_library_state.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_get_library_state(int mole_descriptor,me_mole_library_state *library_state);

/**
 * Получить ошибку, которую вернула не асинхронная функция при использовании асинхронной обёртки данной функции.
 * Например: сделан вызов me_host_get_samples_data_async. Чтобы получить информацию
 * об ошибке для me_host_get_samples_data необходимо использовать me_get_last_error.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_get_last_error(int mole_descriptor,int *mole_error);

#endif // MOLE_ENGINE_H
