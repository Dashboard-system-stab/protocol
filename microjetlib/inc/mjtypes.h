#ifndef MICROJET_BRO30_TYPES_H
#define MICROJET_BRO30_TYPES_H

#include "microjet.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 *  Состояние исполнения комманды
 */
typedef enum command_state
{
    /** Принято */
    COMMAND_STATE_ACCEPT = 0,
    /** Исполняется */
    COMMAND_STATE_INPROGRESS = 1,
    /** Исполненно */
    COMMAND_STATE_DONE = 2,
    /** Неизвестная комманда */
    COMMAND_STATE_UNKNOW = 3,
    /** Исполнение запрещено */
    COMMAND_STATE_FORBITTEN = 4,
    /** Не реализовано */
    COMMAND_STATE_NOT_IMPLEMENTED = -4,
    /** Произошла ошибка при исполненни комманды */
    COMMAND_STATE_ERROR = -5,
    /** Stub */
    COMMAND_STATE_SIZE_STUB = INT32_MIN
} command_state_k;

/**
 *  Типы комманд для исполнения устрйоством
 */
typedef enum command_type
{
    /** Программная перезагрузка */
    COMMAND_TYPE_SWRESET = 0,
    /** Сохранить параметры в ПЗУ */
    COMMAND_TYPE_SAVEPRM = 1,
    /** Установить текущее положение привода как нулевое */
    COMMAND_TYPE_SET_HOME_POSITION = 2,
    /** Установить текущее положение привода как верхний предел перемещения */
    COMMAND_TYPE_SET_UP_LIMIT = 3,
    /** Установить текущее положение привода как нижний предел перемещения */
    COMMAND_TYPE_SET_DOWN_LIMIT = 4,
    /** Установить нулевое положение ротора */
    COMMAND_TYPE_SET_EL_ZERO = 5,
    /** Сброс времени наработки */
    COMMAND_TYPE_OPERATION_TIME_RESET = 6,
    /** Сброс значения интегратора */
    COMMAND_TYPE_INTEGRATOR_RESET = 7,
    /** Перейти в режим обновления прикладного ПО */
    COMMAND_TYPE_FIRMWARE_UPGRADE = 8,
    /** Подтвердить успешное обновление прикладного ПО */
    COMMAND_TYPE_FIRMWARE_VERIFY = 9,
    /** Выполнить калибровку датчиков тока */
    COMMAND_TYPE_CURRENT_SENSOR_CALIB = 10,
    /** Stub */
    COMMAND_TYPE_SIZE_STUB = INT32_MIN
} command_type_k;

/**
 *  Состояние модуля управления приводами
 */
typedef enum dcu_status
{
    /** Неизвестно */
    DCU_STATUS_UNKNOWN = 0,
    /** Выключен */
    DCU_STATUS_OFF = 1,
    /** Подготовка к работе */
    DCU_STATUS_PREPARE = 2,
    /** Калибровка датчиков тока */
    DCU_STATUS_CUR_CALIB = 3,
    /** Привода обесточены */
    DCU_STATUS_DISARM = 4,
    /** Осуществляется наведение приводов */
    DCU_STATUS_ARM = 5,
    /** Отказ */
    DCU_STATUS_FAULT = -1,
    /** Stub */
    DCU_STATUS_SIZE_STUB = INT32_MIN
} dcu_status_k;

/**
 *  Ошибка смены способа управления
 */
typedef enum drv_ctrl_error
{
    /** Неизвестная ошибка */
    DRV_CTRL_ERROR_UNKNOWN = 0,
    /** Ошибки отсутствуют */
    DRV_CTRL_ERROR_NONE = 1,
    /** Вращение заблокировано */
    DRV_CTRL_ERROR_BLOCK = 2,
    /** Отсутствует сигнал включения */
    DRV_CTRL_ERROR_OFF = 3,
    /** Нет питания */
    DRV_CTRL_ERROR_POWER = 4,
    /** Отсутствуют сигналы управления */
    DRV_CTRL_ERROR_CTRL = 5,
    /** Перегрузка */
    DRV_CTRL_ERROR_OLP = 6,
    /** Превышение максимального тока привода */
    DRV_CTRL_ERROR_OCP = 7,
    /** Защита от низкого напряжение */
    DRV_CTRL_ERROR_UVP = 8,
    /** Защита от короткого замыкания */
    DRV_CTRL_ERROR_SCP = 9,
    /** Неподдерживаемый режим */
    DRV_CTRL_ERROR_MODE = 10,
    /** Защита инвертора */
    DRV_CTRL_ERROR_INV = 11,
    /** Нет связи с датчиком угла нагрузки */
    DRV_CTRL_ERROR_LANG = 12,
    /** Нет связи с датчиком угла ротора */
    DRV_CTRL_ERROR_RANG = 13,
    /** Защита от перегрева */
    DRV_CTRL_ERROR_OHP = 14,
    /** Отказ тормоза */
    DRV_CTRL_ERROR_BRAKE = 15,
    /** Отказ датчика положения ротора */
    DRV_CTRL_ERROR_ROTOR_SENS = 16,
    /** Ошибка подключения мотора */
    DRV_CTRL_ERROR_MCON = 17,
    /** Сервисный режим работы */
    DRV_CTRL_ERROR_SERVICE = 18,
    /** Stub */
    DRV_CTRL_ERROR_SIZE_STUB = INT32_MIN
} drv_ctrl_error_k;

/**
 *  Способ управленяи приводом
 */
typedef enum drv_ctrl_mode
{
    /** Неизвестно */
    DRV_CTRL_MODE_UNKNOWN = 0,
    /** Управление не осуществляется, привод обесточен */
    DRV_CTRL_MODE_OFF = 1,
    /** Свободное вращение без управления приводами */
    DRV_CTRL_MODE_FREEMOVE = 2,
    /** Застопорено */
    DRV_CTRL_MODE_HOLD = 3,
    /** Приведение на заданный угол */
    DRV_CTRL_MODE_ANGLE = 4,
    /** Перемещение с заданной скоростью */
    DRV_CTRL_MODE_SPEED = 5,
    /** Вращение ротора с заданной скоростью */
    DRV_CTRL_MODE_RSPEED = 6,
    /** Прямое управление напряжением привода */
    DRV_CTRL_MODE_VOLTAGE = 7,
    /** Синхронный режим */
    DRV_CTRL_MODE_SYNCHRO = 8,
    /** Прямое управление током привода */
    DRV_CTRL_MODE_CURRENT = 9,
    /** Прямое управление напряжением фазы A */
    DRV_CTRL_MODE_VOLTAGE_A = 10,
    /** Прямое управление напряжением фазы B */
    DRV_CTRL_MODE_VOLTAGE_B = 11,
    /** Прямое управление напряжением фазы C */
    DRV_CTRL_MODE_VOLTAGE_C = 12,
    /** Stub */
    DRV_CTRL_MODE_SIZE_STUB = INT32_MIN
} drv_ctrl_mode_k;

/**
 *  Режим работы инвертора
 */
typedef enum inverter_mode
{
    /** Неизвестно */
    INVERTER_MODE_UNKNOW = 0,
    /** Выключен */
    INVERTER_MODE_OFF = 1,
    /** Включен, готов к работе */
    INVERTER_MODE_OK = 2,
    /** Подготовка к включению */
    INVERTER_MODE_ENABLING = 3,
    /** Подготовка к выключению */
    INVERTER_MODE_DISABLING = 4,
    /** Отказ */
    INVERTER_MODE_FAULT = 5,
    /** Калибровка датчиков тока */
    INVERTER_MODE_CALIBRATION = 6,
    /** Проверка подключения фаз */
    INVERTER_MODE_CONNECTION_CHECK = 7,
    /** Stub */
    INVERTER_MODE_SIZE_STUB = INT32_MIN
} inverter_mode_k;

/**
 *  Состояние датчика угла нагрузки
 */
typedef enum load_ang_sens_status
{
    /** Состояние неизвестно */
    LOAD_ANG_SENS_STATUS_UNKNOW = 0,
    /** Подготовка */
    LOAD_ANG_SENS_STATUS_PREPARE = 1,
    /** Отсутствует */
    LOAD_ANG_SENS_STATUS_UNCONNECTED = 2,
    /** Штатное функционирование */
    LOAD_ANG_SENS_STATUS_NORMAL = 3,
    /** Ограничено исправен */
    LOAD_ANG_SENS_STATUS_WARNING = 4,
    /** Неисправен */
    LOAD_ANG_SENS_STATUS_FAULT = -1,
    /** Stub */
    LOAD_ANG_SENS_STATUS_SIZE_STUB = INT32_MIN
} load_ang_sens_status_k;

/**
 *  Состояние ограничения перемещения приводов
 */
typedef enum move_limit_state
{
    /** Состояние неизвестно */
    MOVE_LIMIT_STATE_UNKNOW = 0,
    /** Ограничение отсутствует - наведение в пределах ограничений */
    MOVE_LIMIT_STATE_NONE = 1,
    /** Достигнут верхний предел сектора наведения */
    MOVE_LIMIT_STATE_LIMIT_UP = 2,
    /** Достигнут нижний предел сектора наведения */
    MOVE_LIMIT_STATE_LIMIT_DOWN = 3,
    /** Stub */
    MOVE_LIMIT_STATE_SIZE_STUB = INT32_MIN
} move_limit_state_k;

/**
 *  Состояние обработки запроса на отправку сообщения
 */
typedef enum msg_state
{
    /** Запрос принят */
    MSG_STATE_CONFIRMED = 0,
    /** Сообщение отправлено */
    MSG_STATE_SEND = 1,
    /** Неподдерживаемый ID сообщения */
    MSG_STATE_WRONGCODE = -1,
    /** Невозможно отправить переодическое сообщение */
    MSG_STATE_ISPERIODIC = -2,
    /** Отправка невозможна */
    MSG_STATE_IMPOSSIBLE = -3,
    /** Stub */
    MSG_STATE_SIZE_STUB = INT32_MIN
} msg_state_k;

/**
 *  Тип запроса параметра
 */
typedef enum parameter_request_type
{
    /** Чтение */
    PARAMETER_REQUEST_TYPE_READ = 0,
    /** Запись */
    PARAMETER_REQUEST_TYPE_WRITE = 1,
    /** Stub */
    PARAMETER_REQUEST_TYPE_SIZE_STUB = INT32_MIN
} parameter_request_type_k;

/**
 *  Результат обработки запроса на чтение или запись параметра устрйоства
 */
typedef enum parameter_status
{
    /** Параметр отправлен или записан успешно */
    PARAMETER_STATUS_OK = 0,
    /** Неизвестный параметр */
    PARAMETER_STATUS_UNKNOWPRM = -1,
    /** Запись параметра не удалась */
    PARAMETER_STATUS_WRITE_FAILED = -4,
    /** Параметр доступен только для чтения */
    PARAMETER_STATUS_READ_ONLY = -5,
    /** Параметр не реализован */
    PARAMETER_STATUS_NOT_SUPPORTED = -6,
    /** Stub */
    PARAMETER_STATUS_SIZE_STUB = INT32_MIN
} parameter_status_k;

/**
 *  Состояние релейного сигнала
 */
typedef enum relay_signal_state
{
    /** Неизвестно */
    RELAY_SIGNAL_STATE_UNKNOWN = 0,
    /** ВКЛ */
    RELAY_SIGNAL_STATE_HIGH = 5,
    /** ВЫКЛ */
    RELAY_SIGNAL_STATE_LOW = 1,
    /** Разрыв */
    RELAY_SIGNAL_STATE_GAP = 3,
    /** Защита по току */
    RELAY_SIGNAL_STATE_OCP = -1,
    /** Отказ */
    RELAY_SIGNAL_STATE_FAIL = -2,
    /** Stub */
    RELAY_SIGNAL_STATE_SIZE_STUB = INT32_MIN
} relay_signal_state_k;

/**
 *  Состояние датчика угла ротора
 */
typedef enum rotor_ang_sens_status
{
    /** Состояние неизвестно */
    ROTOR_ANG_SENS_STATUS_UNKNOW = 0,
    /** Подготовка */
    ROTOR_ANG_SENS_STATUS_PREPARE = 1,
    /** Отсутствует */
    ROTOR_ANG_SENS_STATUS_UNCONNECTED = 2,
    /** Штатное функционирование */
    ROTOR_ANG_SENS_STATUS_NORMAL = 3,
    /** Ограничено исправен */
    ROTOR_ANG_SENS_STATUS_WARNING = 4,
    /** Неисправен */
    ROTOR_ANG_SENS_STATUS_FAULT = -1,
    /** Stub */
    ROTOR_ANG_SENS_STATUS_SIZE_STUB = INT32_MIN
} rotor_ang_sens_status_k;

/**
 *  Состояние тормоза
 */
typedef enum rotor_brake_state
{
    /** Неизвестно */
    ROTOR_BRAKE_STATE_UNKNOWN = 0,
    /** Застопорен */
    ROTOR_BRAKE_STATE_CLOSE = 1,
    /** Расстопорен */
    ROTOR_BRAKE_STATE_RELEASE = 2,
    /** Ошибка */
    ROTOR_BRAKE_STATE_FAIL = 3,
    /** Stub */
    ROTOR_BRAKE_STATE_SIZE_STUB = INT32_MIN
} rotor_brake_state_k;

/**
 *  Состояние синхронизации
 */
typedef enum sync_state
{
    /** Ошибка */
    SYNC_STATE_FAILED = -1,
    /** Синхронизация не производится */
    SYNC_STATE_FREERUN = 0,
    /** В процессе синхронизации */
    SYNC_STATE_UNSYNC = 1,
    /** Синхронизировано */
    SYNC_STATE_SYNC = 2,
    /** Stub */
    SYNC_STATE_SIZE_STUB = INT32_MIN
} sync_state_k;

/**
 *  Состояние переходного процесса
 */
typedef enum transit_proc_status
{
    /** Состояние неизвестно */
    TRANSIT_PROC_STATUS_UNKNOW = 0,
    /** Переходной процесс отсутствует */
    TRANSIT_PROC_STATUS_NONE = 1,
    /** Переходной процесс не завершен */
    TRANSIT_PROC_STATUS_INPROGRESS = 2,
    /** Переходной процесс завершен */
    TRANSIT_PROC_STATUS_DONE = 3,
    /** Stub */
    TRANSIT_PROC_STATUS_SIZE_STUB = INT32_MIN
} transit_proc_status_k;


/**
 *  Запрос параметра устройства
 */
typedef struct parameter_request
{
    /** Тип запроса. */
    parameter_request_type_k type;
    /** ID запрашиваемого параметра. */
    /** alias: PRM_ID_FROM_SPEC_t */
    uint32_t id;
    /** Новое значение параметра. */
    char val[32];
} parameter_request_t;

/**
 *  Ответ на запрос параметра устройства
 */
typedef struct parameter_answer
{
    /** ID запрошенного параметра. */
    /** alias: PRM_ID_FROM_SPEC_t */
    uint32_t id;
    /** Результат выполнения запроса. */
    parameter_status_k ans;
    /** Значение параметра. */
    char val[32];
} parameter_answer_t;

/**
 *  Запрос комманды на исполнение
 */
typedef struct command_request
{
    /**  */
    command_type_k type;
} command_request_t;

/**
 *  Отчет о ходе выполнения комманды
 */
typedef struct command_answer
{
    /** Запрошенная комманда. */
    command_type_k command;
    /** Код состояния исполнения комманды. */
    command_state_k state;
    /** Счетчик запроса комманды, на которое отправлен ответ. */
    uint32_t cnt;
    /** Дополнительная информация о выполнении комманды. Формат определяется разработчиком СЧ Кодировка CP866. */
    char info[32];
} command_answer_t;

/**
 *  Запрос сообщения
 */
typedef struct msg_request
{
    /** ID запрашиваемого сообщения. */
    /** alias: MSG_ID_FROM_SPEC_t */
    uint16_t id;
} msg_request_t;

/**
 *  Ответ на запрос отправки сообщения
 */
typedef struct msg_answer
{
    /** ID запрошенного сообщения. */
    /** alias: MSG_ID_FROM_SPEC_t */
    uint16_t id;
    /** Счетчик запроса сообщения, на которое отправлен ответ. */
    uint32_t cnt;
    /** Код состояния отправки. */
    msg_state_k state;
} msg_answer_t;

/**
 *  Произвольные отладочные сигналы без спецификации
 */
typedef struct dbg_data
{
    /**  */
    float fval[5];
} dbg_data_t;

/**
 *  Данные от датчика углового положения ротора
 */
typedef struct rotor_ang_sens_state
{
    /** Угол [-pi..pi], рад. */
    float angle;
    /** Состояние датчика. */
    rotor_ang_sens_status_k status;
} rotor_ang_sens_state_t;

/**
 *  Данные от датчика углового положения нагрузки
 */
typedef struct load_ang_sens_state
{
    /** Угол [-pi..pi], рад. */
    float angle;
    /** Состояние датчика. */
    load_ang_sens_status_k status;
} load_ang_sens_state_t;

/**
 * 
 */
typedef struct three_phase_val
{
    /**  */
    float a;
    /**  */
    float b;
    /**  */
    float c;
} three_phase_val_t;

/**
 *  Статус трехфазного инвертора
 */
typedef struct inverter_status
{
    /** Режим работы. */
    inverter_mode_k mode;
    /** Перегрузка по току или перегрев преобразователя. Активный уровень - low. */
    relay_signal_state_k nOCTW;
    /** Отказ. Активный уровень - low. */
    relay_signal_state_k nFAULT;
    /** Включение драйвера затворов. */
    relay_signal_state_k EN_GATE;
    /** Ток, A. */
    three_phase_val_t current;
    /** Коэффициент заполнения ШИМ. */
    three_phase_val_t pwm;
    /** Напряжение питания, В. */
    float vdc;
} inverter_status_t;

/**
 * 
 */
typedef struct park_vec
{
    /**  */
    float d;
    /**  */
    float q;
} park_vec_t;

/**
 *  Состояние ПИД регулятора
 */
typedef struct pid_state
{
    /** Ошибка. */
    float err;
    /** Откорректированная ошибка. */
    float cor_err;
    /** Вклад Feed-forward. */
    float feed_forward;
    /** Вклад Tracking. */
    float track;
    /** Anti-Windup back calculation. */
    float back;
    /** Интегральная составляющая. */
    float int_val;
    /** Выход. */
    float out;
} pid_state_t;

/**
 *  Состояние датчиков Холла
 */
typedef struct hall_sensor
{
    /** Логический уровень датчика Холла A. */
    bool a;
    /** Логический уровень датчика Холла B. */
    bool b;
    /** Логический уровень датчика Холла C. */
    bool c;
} hall_sensor_t;

/**
 *  Теелеметрия модуля управления приводом БУП
 */
typedef struct dcu_telemetry
{
    /** Способ управления приводом. */
    /** alias: drv_ctrl_mode_t */
    int8_t mode;
    /** Состояние. */
    /** alias: dcu_status_t */
    int8_t status;
    /** Код ошибки смены способа управления. */
    /** alias: drv_ctrl_error_t */
    int8_t err;
    /** Состояние датчика углового положения нагрузки. */
    /** alias: load_ang_sens_status_t */
    int8_t load_sens_state;
    /** Данные от датчика углового положения нагрузки, рад +-pi. */
    float load_sens_angle;
    /** Угловая скорость датчика положения нагрузки, рад/с. */
    float load_sens_speed;
    /** Напряжение питания силовых цепей, В. */
    float power_vdc;
    /** Трехфазный ток, A. */
    three_phase_val_t current;
    /** Коэффициент заполнения ШИМ. */
    three_phase_val_t pwm;
    /** Напряжение на фазах в СК Парка-Горева, В. */
    park_vec_t park_voltage;
    /** Ток фаз в СК Парка-Горева, A. */
    park_vec_t park_current;
    /** Ток тормоза. */
    float ibrk;
    /** Температра статора, C. */
    float stator_temp;
    /** Состояние тормоза. */
    /** alias: rotor_brake_state_t */
    int8_t brake_state;
    /** Напряжение питания модуля, В. */
    float power_voltage;
    /** Мощность, положителная - потребляем, отрицательная - генерируем в сеть, ВА. */
    float electrical_power;
    /** Состояние ПИД регулятора угла. */
    pid_state_t ang_pid_state;
    /** Состояние ПИД регулятора скорости ротора. */
    pid_state_t rotor_spd_pid_state;
    /** Состояние ПИД регулятора скорости нагрузки. */
    pid_state_t load_spd_pid_state;
    /** Состояние ПИД регулятора тока q. */
    pid_state_t curr_q_pid_state;
    /** Состояние ПИД регулятора тока d. */
    pid_state_t curr_d_pid_state;
    /** Состояние датчика углового положения ротора. */
    /** alias: rotor_ang_sens_status_t */
    int8_t rotor_sens_state;
    /** Данные от датчика углового положения ротора, рад +-pi. */
    float rotor_sens_angle;
    /** Угловая скорость датчика положения ротора, рад/с. */
    float rotor_sens_speed;
    /** Состояние дискретного сигнала ON. */
    /** alias: relay_signal_state_t */
    int8_t on;
    /** Состояние дискретного сигнала MANUAL. */
    /** alias: relay_signal_state_t */
    int8_t manual;
    /** Состояние дискретного сигнала BLOCK. */
    /** alias: relay_signal_state_t */
    int8_t block;
    /** Состояние дискретного сигнала SYNC. */
    /** alias: relay_signal_state_t */
    int8_t sync;
    /** Перегрузка по току или перегрев преобразователя. Активный уровень - low. */
    /** alias: relay_signal_state_t */
    int8_t inv_octw;
    /** Отказ. Активный уровень - low. */
    /** alias: relay_signal_state_t */
    int8_t inv_fault;
    /** Включение драйвера затворов. */
    /** alias: relay_signal_state_t */
    int8_t en_gate;
    /** Логические уровни датчиков Холла. */
    hall_sensor_t hall;
} dcu_telemetry_t;

/**
 *  Состояние привода наведения БУП
 */
typedef struct bup_drv_state
{
    /** Способ управления приводом. */
    /** alias: drv_ctrl_mode_t */
    int8_t mode;
    /** Код ошибки смены способа управления. */
    /** alias: drv_ctrl_error_t */
    int8_t error;
    /** Состояние. */
    /** alias: dcu_status_t */
    int8_t status;
    /** Признак ограничения наведения. */
    /** alias: move_limit_state_t */
    int8_t limit;
    /** Угловое положение в локальной СК, рад. От -pi до pi. */
    float angle;
    /** Угловая скорость в локальной СК, рад/с. */
    float speed;
    /** Температра статора, C. */
    float stator_temp;
    /** Состояние тормоза. */
    /** alias: rotor_brake_state_t */
    int8_t brake_state;
    /** Напряжение питания модуля, В. */
    float power_voltage;
    /** Ток id, А. */
    float id;
    /** Ток iq, А. */
    float iq;
    /** Мощность, положителная - потребляемая, отрицательная - генерируемая в сеть, Вт. */
    float electrical_power;
    /** Состояние датчика углового положения нагрузки. */
    /** alias: load_ang_sens_status_t */
    int8_t load_sens_state;
    /** Данные от датчика углового положения нагрузки, рад +-pi. */
    float load_sens_angle;
    /** Угловая скорость датчика положения нагрузки, рад/с. */
    float load_sens_speed;
    /** Состояние датчика углового положения ротора. */
    /** alias: rotor_ang_sens_status_t */
    int8_t rotor_sens_state;
    /** Данные от датчика углового положения ротора, рад +-512pi. */
    float rotor_sens_angle;
    /** Угловая скорость датчика положения ротора, рад/с. */
    float rotor_sens_speed;
} bup_drv_state_t;

/**
 *  Обратная связь от подчиненного привода
 */
typedef struct drive_slave_fb
{
    /**  */
    float rotor_speed;
} drive_slave_fb_t;

/**
 *  Управление подчиненным приводом от мастера
 */
typedef struct drive_master_ctrl
{
    /**  */
    float current;
} drive_master_ctrl_t;

/**
 *  Сигналы управления приводом
 */
typedef struct drv_ctrl_sp
{
    /** Режим управления приводом. */
    drv_ctrl_mode_k mode;
    /** Целевое значение углового положения привода, СК зависит от режима управления, рад. */
    float angle;
    /** Целевое значение угловой скорости привода, СК зависит от режима управления, рад/с. */
    float speed;
    /** Целевое значение напряжения, точка формирования зависит от режима управления, В. */
    float voltage;
    /** Целевое значение тока, точка формирования зависит от режима управления, А. */
    float current;
} drv_ctrl_sp_t;

/**
 *  Управление приводами БУП
 */
typedef struct bup_drv_control
{
    /** Управленние приводом. */
    drv_ctrl_sp_t dr;
} bup_drv_control_t;

/**
 *  Управление приводами БУП
 */
typedef struct bup_drv_multi_control
{
    /** Управленние левым передним тяговым приводом. */
    drv_ctrl_sp_t lfd;
    /** Управленние левым задним тяговым приводом. */
    drv_ctrl_sp_t lrd;
    /** Управленние левым рулевым приводом. */
    drv_ctrl_sp_t lst;
    /** Управленние правым передним тяговым приводом. */
    drv_ctrl_sp_t rfd;
    /** Управленние правым задним тяговым приводом. */
    drv_ctrl_sp_t rrd;
    /** Управленние правым рулевым приводом. */
    drv_ctrl_sp_t rst;
} bup_drv_multi_control_t;

/**
 *  Управление электроприводами имитатора BRO 3.0
 */
typedef struct im_bro_drive_ctrl
{
    /** Напряжения, прикладываемые к якорю привода, В. */
    float voltage[3];
    /** Признак включения источника напряжения. */
    bool connected;
} im_bro_drive_ctrl_t;

/**
 *  Показания датчиков модели приводов
 */
typedef struct drivers_sens
{
    /** Ток, А. */
    float currents_gn[3];
    /** Угол ротора, рад. */
    float rotor_angle_gn;
    /** Номинальное напряжение привода, В. */
    float v_nom;
} drivers_sens_t;

/**
 *  Состояние синхронизации
 */
typedef struct ptp_info
{
    /**  */
    bool is_master;
    /**  */
    int32_t path_delay;
    /**  */
    int32_t offset_ns;
    /**  */
    int32_t mean_offset_ns;
    /**  */
    sync_state_k state;
} ptp_info_t;

/**
 *  Электронный формуляр изделия
 */
typedef struct formular_info
{
    /** Обозначение СЧ. Формат обозначения определяет разработчик СЧ. Рекомендуемый формат обозначения: ХХХХ.123456.123-12. Обозначение СЧ представляется в строковом виде в кодировке CP866. */
    char description[32];
    /** Заводской номер СЧ. Заводской номер представляется в строковом виде в кодировке CP866. */
    char factory_number[32];
    /** Дата изготовления СЧ. Задается в формате HH : MM dd.mm.yyyy. */
    char factory_date[32];
    /** Версия ПО СЧ. Формат номера версии ПО определяется разработчиком СЧ Версия ПО представляется в строковом виде в кодировке CP866. */
    char software_version[32];
    /** Версия реализованного протокола. Формат номера версии протокола определяется разработчиком СЧ Версия реализованного протокола представляется в строковом виде в кодировке CP866. */
    char protocol_version[32];
    /** Глобально уникальный идентификационый номер устройства. Формат определяется разработчиком СЧ Представляется в строковом виде в шестнадцатеричном формате пример: 0D01020A0BFF. */
    char GUID[32];
    /** Текущая наработка СЧ с момента первого включения, секунды. */
    int32_t operation_time;
    /** Контрольная сумма ПО. Формат: HEX. */
    char software_checksum[64];
    /** Код блока. */
    uint8_t code;
} formular_info_t;



typedef struct bup_drv_control_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Управленние приводом. */
    drv_ctrl_sp_t dr;
} bup_drv_control_msg_t;
typedef struct bup_drv_multi_control_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Управленние левым передним тяговым приводом. */
    drv_ctrl_sp_t lfd;
    /** Управленние левым задним тяговым приводом. */
    drv_ctrl_sp_t lrd;
    /** Управленние левым рулевым приводом. */
    drv_ctrl_sp_t lst;
    /** Управленние правым передним тяговым приводом. */
    drv_ctrl_sp_t rfd;
    /** Управленние правым задним тяговым приводом. */
    drv_ctrl_sp_t rrd;
    /** Управленние правым рулевым приводом. */
    drv_ctrl_sp_t rst;
} bup_drv_multi_control_msg_t;
typedef struct bup_drv_state_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Способ управления приводом.*/
    /** alias: drv_ctrl_mode_t */
    int8_t mode;
    /** Код ошибки смены способа управления.*/
    /** alias: drv_ctrl_error_t */
    int8_t error;
    /** Состояние.*/
    /** alias: dcu_status_t */
    int8_t status;
    /** Признак ограничения наведения.*/
    /** alias: move_limit_state_t */
    int8_t limit;
    /** Угловое положение в локальной СК, рад. От -pi до pi.*/
    float angle;
    /** Угловая скорость в локальной СК, рад/с.*/
    float speed;
    /** Температра статора, C.*/
    float stator_temp;
    /** Состояние тормоза.*/
    /** alias: rotor_brake_state_t */
    int8_t brake_state;
    /** Напряжение питания модуля, В.*/
    float power_voltage;
    /** Ток id, А.*/
    float id;
    /** Ток iq, А.*/
    float iq;
    /** Мощность, положителная - потребляемая, отрицательная - генерируемая в сеть, Вт.*/
    float electrical_power;
    /** Состояние датчика углового положения нагрузки.*/
    /** alias: load_ang_sens_status_t */
    int8_t load_sens_state;
    /** Данные от датчика углового положения нагрузки, рад +-pi.*/
    float load_sens_angle;
    /** Угловая скорость датчика положения нагрузки, рад/с.*/
    float load_sens_speed;
    /** Состояние датчика углового положения ротора.*/
    /** alias: rotor_ang_sens_status_t */
    int8_t rotor_sens_state;
    /** Данные от датчика углового положения ротора, рад +-512pi.*/
    float rotor_sens_angle;
    /** Угловая скорость датчика положения ротора, рад/с.*/
    float rotor_sens_speed;
} bup_drv_state_msg_t;
typedef struct command_answer_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Запрошенная комманда. */
    command_type_k command;
    /** Код состояния исполнения комманды. */
    command_state_k state;
    /** Счетчик запроса комманды, на которое отправлен ответ.*/
    uint32_t cnt;
    /** Дополнительная информация о выполнении комманды. Формат определяется разработчиком СЧ Кодировка CP866. */
    char info[32];
} command_answer_msg_t;
typedef struct command_request_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /**  */
    command_type_k type;
} command_request_msg_t;
typedef struct dbg_data_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /**  */
    float fval[5];
} dbg_data_msg_t;
typedef struct dcu_telemetry_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Способ управления приводом.*/
    /** alias: drv_ctrl_mode_t */
    int8_t mode;
    /** Состояние.*/
    /** alias: dcu_status_t */
    int8_t status;
    /** Код ошибки смены способа управления.*/
    /** alias: drv_ctrl_error_t */
    int8_t err;
    /** Состояние датчика углового положения нагрузки.*/
    /** alias: load_ang_sens_status_t */
    int8_t load_sens_state;
    /** Данные от датчика углового положения нагрузки, рад +-pi.*/
    float load_sens_angle;
    /** Угловая скорость датчика положения нагрузки, рад/с.*/
    float load_sens_speed;
    /** Напряжение питания силовых цепей, В.*/
    float power_vdc;
    /** Трехфазный ток, A. */
    three_phase_val_t current;
    /** Коэффициент заполнения ШИМ. */
    three_phase_val_t pwm;
    /** Напряжение на фазах в СК Парка-Горева, В. */
    park_vec_t park_voltage;
    /** Ток фаз в СК Парка-Горева, A. */
    park_vec_t park_current;
    /** Ток тормоза.*/
    float ibrk;
    /** Температра статора, C.*/
    float stator_temp;
    /** Состояние тормоза.*/
    /** alias: rotor_brake_state_t */
    int8_t brake_state;
    /** Напряжение питания модуля, В.*/
    float power_voltage;
    /** Мощность, положителная - потребляем, отрицательная - генерируем в сеть, ВА.*/
    float electrical_power;
    /** Состояние ПИД регулятора угла. */
    pid_state_t ang_pid_state;
    /** Состояние ПИД регулятора скорости ротора. */
    pid_state_t rotor_spd_pid_state;
    /** Состояние ПИД регулятора скорости нагрузки. */
    pid_state_t load_spd_pid_state;
    /** Состояние ПИД регулятора тока q. */
    pid_state_t curr_q_pid_state;
    /** Состояние ПИД регулятора тока d. */
    pid_state_t curr_d_pid_state;
    /** Состояние датчика углового положения ротора.*/
    /** alias: rotor_ang_sens_status_t */
    int8_t rotor_sens_state;
    /** Данные от датчика углового положения ротора, рад +-pi.*/
    float rotor_sens_angle;
    /** Угловая скорость датчика положения ротора, рад/с.*/
    float rotor_sens_speed;
    /** Состояние дискретного сигнала ON.*/
    /** alias: relay_signal_state_t */
    int8_t on;
    /** Состояние дискретного сигнала MANUAL.*/
    /** alias: relay_signal_state_t */
    int8_t manual;
    /** Состояние дискретного сигнала BLOCK.*/
    /** alias: relay_signal_state_t */
    int8_t block;
    /** Состояние дискретного сигнала SYNC.*/
    /** alias: relay_signal_state_t */
    int8_t sync;
    /** Перегрузка по току или перегрев преобразователя. Активный уровень - low.*/
    /** alias: relay_signal_state_t */
    int8_t inv_octw;
    /** Отказ. Активный уровень - low.*/
    /** alias: relay_signal_state_t */
    int8_t inv_fault;
    /** Включение драйвера затворов.*/
    /** alias: relay_signal_state_t */
    int8_t en_gate;
    /** Логические уровни датчиков Холла. */
    hall_sensor_t hall;
} dcu_telemetry_msg_t;
typedef struct drive_master_ctrl_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** */
    float current;
} drive_master_ctrl_msg_t;
typedef struct drive_slave_fb_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** */
    float rotor_speed;
} drive_slave_fb_msg_t;
typedef struct drivers_sens_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Ток, А. */
    float currents_gn[3];
    /** Угол ротора, рад.*/
    float rotor_angle_gn;
    /** Номинальное напряжение привода, В.*/
    float v_nom;
} drivers_sens_msg_t;
typedef struct formular_info_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Обозначение СЧ. Формат обозначения определяет разработчик СЧ. Рекомендуемый формат обозначения: ХХХХ.123456.123-12. Обозначение СЧ представляется в строковом виде в кодировке CP866. */
    char description[32];
    /** Заводской номер СЧ. Заводской номер представляется в строковом виде в кодировке CP866. */
    char factory_number[32];
    /** Дата изготовления СЧ. Задается в формате HH : MM dd.mm.yyyy. */
    char factory_date[32];
    /** Версия ПО СЧ. Формат номера версии ПО определяется разработчиком СЧ Версия ПО представляется в строковом виде в кодировке CP866. */
    char software_version[32];
    /** Версия реализованного протокола. Формат номера версии протокола определяется разработчиком СЧ Версия реализованного протокола представляется в строковом виде в кодировке CP866. */
    char protocol_version[32];
    /** Глобально уникальный идентификационый номер устройства. Формат определяется разработчиком СЧ Представляется в строковом виде в шестнадцатеричном формате пример: 0D01020A0BFF. */
    char GUID[32];
    /** Текущая наработка СЧ с момента первого включения, секунды.*/
    int32_t operation_time;
    /** Контрольная сумма ПО. Формат: HEX. */
    char software_checksum[64];
    /** Код блока.*/
    uint8_t code;
} formular_info_msg_t;
typedef struct im_bro_drive_ctrl_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Напряжения, прикладываемые к якорю привода, В. */
    float voltage[3];
    /** Признак включения источника напряжения.*/
    bool connected;
} im_bro_drive_ctrl_msg_t;
typedef struct msg_answer_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** ID запрошенного сообщения.*/
    /** alias: MSG_ID_FROM_SPEC_t */
    uint16_t id;
    /** Счетчик запроса сообщения, на которое отправлен ответ.*/
    uint32_t cnt;
    /** Код состояния отправки. */
    msg_state_k state;
} msg_answer_msg_t;
typedef struct msg_request_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** ID запрашиваемого сообщения.*/
    /** alias: MSG_ID_FROM_SPEC_t */
    uint16_t id;
} msg_request_msg_t;
typedef struct parameter_answer_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** ID запрошенного параметра.*/
    /** alias: PRM_ID_FROM_SPEC_t */
    uint32_t id;
    /** Результат выполнения запроса. */
    parameter_status_k ans;
    /** Значение параметра. */
    char val[32];
} parameter_answer_msg_t;
typedef struct parameter_request_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** Тип запроса. */
    parameter_request_type_k type;
    /** ID запрашиваемого параметра.*/
    /** alias: PRM_ID_FROM_SPEC_t */
    uint32_t id;
    /** Новое значение параметра. */
    char val[32];
} parameter_request_msg_t;
typedef struct ptp_info_msg{
    /** Header */
    struct{
        uint16_t src;
        uint16_t dst;
        uint16_t id;
        uint16_t cnt;
        uint32_t ts_s;
        union{
            struct{
                uint32_t ts_ns:30;
                uint32_t ts_status:2;
            };
            uint32_t ts_low;
        };
    } hdr;
    /** */
    bool is_master;
    /** */
    int32_t path_delay;
    /** */
    int32_t offset_ns;
    /** */
    int32_t mean_offset_ns;
    /**  */
    sync_state_k state;
} ptp_info_msg_t;

mj_check_result_t bup_drv_control_type_check(bup_drv_control_msg_t * ptr);
mj_check_result_t bup_drv_multi_control_type_check(bup_drv_multi_control_msg_t * ptr);
mj_check_result_t bup_drv_state_type_check(bup_drv_state_msg_t * ptr);
mj_check_result_t command_answer_type_check(command_answer_msg_t * ptr);
mj_check_result_t command_request_type_check(command_request_msg_t * ptr);
mj_check_result_t dbg_data_type_check(dbg_data_msg_t * ptr);
mj_check_result_t dcu_telemetry_type_check(dcu_telemetry_msg_t * ptr);
mj_check_result_t drive_master_ctrl_type_check(drive_master_ctrl_msg_t * ptr);
mj_check_result_t drive_slave_fb_type_check(drive_slave_fb_msg_t * ptr);
mj_check_result_t drivers_sens_type_check(drivers_sens_msg_t * ptr);
mj_check_result_t formular_info_type_check(formular_info_msg_t * ptr);
mj_check_result_t im_bro_drive_ctrl_type_check(im_bro_drive_ctrl_msg_t * ptr);
mj_check_result_t msg_answer_type_check(msg_answer_msg_t * ptr);
mj_check_result_t msg_request_type_check(msg_request_msg_t * ptr);
mj_check_result_t parameter_answer_type_check(parameter_answer_msg_t * ptr);
mj_check_result_t parameter_request_type_check(parameter_request_msg_t * ptr);
mj_check_result_t ptp_info_type_check(ptp_info_msg_t * ptr);
#ifdef __cplusplus
}
#endif

#endif /* MICROJET_BRO30_TYPES_H */