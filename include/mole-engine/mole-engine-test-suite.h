#ifndef MOLE_ENGINE_TEST_SUITE_H
#define MOLE_ENGINE_TEST_SUITE_H

//#include "common.h"
#include "shared/common.h"
#include "mole-engine.h"

#pragma pack(push,1)

typedef struct 
{
	uint16 multiplier[ME_MMG_COUNT];
	double calculated_value[ME_MMG_COUNT];
	bool out_of_tolerance[ME_MMG_COUNT];
} me_ts_result_gain_channel_t;

typedef struct 
{
	double calculated_value;
	bool out_of_tolerance;
} me_ts_result_channel_t;

#pragma pack(pop)

/**
 * Не является заменой me_mole_library_state. Предлагается использовать только для реализации не молчаливого интерфейса.
 * НЕ ИСПОЛЬЗОВАТЬ для ожидания.
 * Не сбрасывается в ME_TSS_IDLE в случае неудачного завершения теста.
 */
enum me_test_suite_stage
{
	ME_TSS_IDLE				= 0x00,		// Бездействие
	ME_TSS_GAIN_COEFFICIENTS		= 0x01,		// Настройка крота
	ME_TSS_GAIN_COEFFICIENTS_1		= 0x02,		// � егистрация и обработка данных
	ME_TSS_GAIN_COEFFICIENTS_2		= 0x03,		// � егистрация и обработка данных
	ME_TSS_GAIN_COEFFICIENTS_4		= 0x04,		// � егистрация и обработка данных
	ME_TSS_GAIN_COEFFICIENTS_8		= 0x05,		// � егистрация и обработка данных
	ME_TSS_GAIN_COEFFICIENTS_16		= 0x06,		// � егистрация и обработка данных
	ME_TSS_GAIN_COEFFICIENTS_32		= 0x07,		// � егистрация и обработка данных
	ME_TSS_GAIN_COEFFICIENTS_64		= 0x08,		// � егистрация и обработка данных
	ME_TSS_NOISE_FLOOR			= 0x09,		// Настройка крота, регистрация и обработка данных
	ME_TSS_TOTAL_HARMONIC_DISTORTION	= 0x0A,		// Настройка крота, регистрация и обработка данных
	ME_TSS_ZERO_SHIFT			= 0x0B,		// Настройка крота, регистрация и обработка данных
	ME_TSS_COMMON_MODE_REJECTION_SIN	= 0x0C,		// Настройка крота, регистрация синуса и обработка данных
	ME_TSS_COMMON_MODE_REJECTION_IN_PHASE	= 0x0D,		// � егистрация синфазного сигнала и обработка данных
	ME_TSS_COUNT				= 0x0E,
};

/**
 * Прототип callback функции, которая вызывается после каждой регистрации данных для какого-либо из тестов.
 * При использовании асинхронных реализаций тестов вызывается из потока этого теста.
 * ВНИМАНИЕ. При использовании callback функций следует помнить про стандарты вызовов функций 
 * (не столько в разных платформах/компиляторах, сколько в языках).
 * https://en.wikipedia.org/wiki/X86_calling_conventions#List_of_x86_calling_conventions
 */
typedef void(*me_ts_seismic_data_callback_t)(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
					     uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
					     me_mole_module_datarate datarate,
					     me_mole_module_gain gain,
					     uint16 samples,
					     uint8 *seismic_data);

/**
 * Прототип callback функции, которая вызывается при смене стадии теста.
 * При использовании асинхронных реализаций тестов вызывается из потока этого теста.
 * Смотри me_test_suite_stage.
 * ВНИМАНИЕ. При использовании callback функций следует помнить про стандарты вызовов функций 
 * (не столько в разных платформах/компиляторах, сколько в языках).
 * https://en.wikipedia.org/wiki/X86_calling_conventions#List_of_x86_calling_conventions
 */
typedef void(*me_ts_stage_changed_callback_t)(int mole_descriptor,me_test_suite_stage test_suite_stage);

/**
 * Установить callback функцию.
 * Смотри me_ts_seismic_data_callback_t.
 * � азрешается установка NULL - не будет вызываться callback функция. По умолчанию NULL.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL void me_ts_set_seismic_data_callback(me_ts_seismic_data_callback_t callback);

/**
 * Взять установленную callback функцию.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL me_ts_seismic_data_callback_t me_ts_get_seismic_data_callback();

/**
 * Установить callback функцию.
 * Смотри me_ts_stage_changed_callback_t.
 * � азрешается установка NULL - не будет вызываться callback функция. По умолчанию NULL.
 * Является альтернатиной для me_ts_get_stage.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL void me_ts_set_stage_changed_callback(me_ts_stage_changed_callback_t callback);

/**
 * Взять установленную callback функцию.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL me_ts_stage_changed_callback_t me_ts_get_stage_changed_callback();

inline me_ts_result_gain_channel_t* me_ts_get_result_gain_channel(uint8 module_index,uint8 channel_index,uint8 channel_count,me_ts_result_gain_channel_t *results)
{
	return(&results[channel_count * module_index + channel_index]);
}

inline me_ts_result_channel_t* me_ts_get_result_channel(uint8 module_index,uint8 channel_index,uint8 channel_count,me_ts_result_channel_t *results)
{
	return(&results[channel_count * module_index + channel_index]);
}

/**
 * Тест: "Коэффициенты усиления"
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_gain_coefficients(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
									    uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
									    me_ts_result_gain_channel_t *results);

/**
 * Тест: "Коэффициенты усиления" (асинхронный вызов)
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_gain_coefficients_async(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
										  uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
										  me_ts_result_gain_channel_t *results);

/**
 * Тест: "Уровень собственных шумов, мкВ"
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_noise_floor(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
								      uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
								      me_ts_result_channel_t *results);

/**
 * Тест: "Уровень собственных шумов, мкВ" (асинхронный вызов)
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_noise_floor_async(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
									    uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
									    me_ts_result_channel_t *results);

/**
 * Тест: "Коэффициент нелинейных искажений, %"
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_total_harmonic_distortion(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
										    uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
										    me_ts_result_channel_t *results);

/**
 * Тест: "Коэффициент нелинейных искажений, %" (асинхронный вызов)
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_total_harmonic_distortion_async(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
											  uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
											  me_ts_result_channel_t *results);

/**
 * Тест: "Уровень смещения нуля, мкВ"
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_zero_shift(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
								     uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
								     me_ts_result_channel_t *results);

/**
 * Тест: "Уровень смещения нуля, мкВ" (асинхронный вызов)
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_zero_shift_async(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
									   uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
									   me_ts_result_channel_t *results);

/**
* Тест: "Подавление синфазного сигнала, дБ"
*/
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_common_mode_rejection(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
										uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
										me_ts_result_channel_t *results);

/**
* Тест: "Подавление синфазного сигнала, дБ" (асинхронный вызов)
*/
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_common_mode_rejection_async(int mole_descriptor,uint8 first_address,uint8 last_address,uint8 channel_count,
										      uint8 bytes_in_channel,uint8 bytes_in_module,uint16 bytes_in_line,
										      me_ts_result_channel_t *results);

/**
 * Получить информацию о том, какая стадия теста выполняется в данный момент над кротом.
 * Смотри me_test_suite_stage.
 * Является альтернативной для me_ts_set_stage_changed_callback.
 */
extern MOLE_ENGINE_EXPORT_TYPE MOLE_ENGINE_DECL int me_ts_get_stage(int mole_descriptor,me_test_suite_stage *test_suite_stage);

#endif // MOLE_ENGINE_TEST_SUITE_H
