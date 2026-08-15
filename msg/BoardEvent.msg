# Board Event
# Event and protection status

# Charge phase constants
uint8 CHARGE_PHASE_NOT_CHARGING          = 0
uint8 CHARGE_PHASE_PRE_CHARGE            = 1
uint8 CHARGE_PHASE_CC                    = 2
uint8 CHARGE_PHASE_CV                    = 3
uint8 CHARGE_PHASE_FULL                  = 4
uint8 CHARGE_PHASE_PD_SINK_FAULT         = 5
uint8 CHARGE_PHASE_UNSUPPORTED_CHARGER   = 6

# State Change flags bitmask constants
uint16 STATE_CHANGE_FLAG_CHARGER_CONNECT = 1      # bit0
uint16 STATE_CHANGE_FLAG_FAN             = 2      # bit1
uint16 STATE_CHANGE_FLAG_POWER_SERVO     = 4      # bit2
uint16 STATE_CHANGE_FLAG_POWER_5V        = 8      # bit3
uint16 STATE_CHANGE_FLAG_BAT_EXT_OUT     = 16     # bit4

# Protection flags bitmask constants
uint16 PROTECTION_FLAG_SERVO_OVERCURRENT = 1      # bit0
uint16 PROTECTION_FLAG_SERVO_THERMAL     = 2      # bit1
uint16 PROTECTION_FLAG_DCDC_5V_THERMAL   = 4      # bit2
uint16 PROTECTION_FLAG_CHARGE_DERATING   = 8      # bit3
uint16 PROTECTION_FLAG_CHARGE_THERMAL    = 16     # bit4
uint16 PROTECTION_FLAG_BATTERY_LOW       = 32     # bit5

# Error flags bitmask constants
uint16 ERROR_FLAG_UNKNOWN                = 1       # bit0
uint16 ERROR_FLAG_UART1                  = 2       # bit1
uint16 ERROR_FLAG_UART2                  = 4       # bit2
uint16 ERROR_FLAG_I2C1                   = 8       # bit3
uint16 ERROR_FLAG_I2C3                   = 16      # bit4
uint16 ERROR_FLAG_SPI1                   = 32      # bit5
uint16 ERROR_FLAG_USB                    = 64      # bit6
uint16 ERROR_FLAG_DMA                    = 128     # bit7

# Fields
uint8 charge_phase                                 # Charge phase (use CHARGE_PHASE_* constants)
uint16 state_change_flags                          # State Change flags bitmask (use STATE_CHANGE_FLAG_* constants)
uint16 protection_flags                            # Protection flags bitmask (use PROTECTION_FLAG_* constants)
uint16 error_flags                                 # Error flags bitmask (use ERROR_FLAG_* constants)