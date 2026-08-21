uint8 SWITCH_SERVO_POWER            = 0x10
uint8 SWITCH_5V_POWER               = 0x11
uint8 SWITCH_CHARGE                 = 0x12
uint8 SWITCH_BAT_EXT_OUT            = 0x13
uint8 CHARGE_STOP_SOC               = 0x20
# servo robot board发送的日志等级
uint8 TX_LOG_LEVEL                  = 0x21
uint8 POWER_SERVO_CURRENT_LIMIT_MA  = 0x30
uint8 POWER_SERVO_TEMP_LIMIT        = 0x31
uint8 POWER_5V_TEMP_LIMIT           = 0x32
uint8 CHARGE_MAX_CURRENT_MA         = 0x33
uint8 CHARGE_TEMP_DERATING          = 0x34
uint8 CHARGE_TEMP_LIMIT             = 0x35
uint8 CHARGE_STOP_VOLTAGE_MV        = 0x36
# STM32与串口舵机通讯的波特率
uint8 SERVO_BAUD_RATE               = 0x37