# Board Configuration Snapshot
# Current board configuration values
# Field order matches protocol ConfigType enum values

# === Switches (0x10~0x13) ===
bool     power_servo_on            # Servo power state
bool     power_5v_on               # 5V power state
bool     charge_on                 # Charge state
bool     bat_ext_out_on            # Battery extra output state

# === Charge settings (0x20~0x21) ===
uint8    charge_stop_percentage    # Charge stop percentage (1~100)
uint8    tx_log_level              # The log level sent by mcu to the host computer (0:OFF 1:DEBUG 2:INFO 3:WARN 4:ERROR)

# === Limits (0x30~0x37) ===
uint16   servo_current_limit_ma    # Servo current limit (mA)
float32  servo_temp_limit          # Servo temperature limit (°C, protocol ×10)
float32  temp_5v_limit             # 5V temperature limit (°C, protocol ×10)
uint16   charge_max_current_ma     # Charge max current (mA)
float32  charge_temp_derating      # Charge temp derating (°C, protocol ×10)
float32  charge_temp_limit         # Charge temp limit (°C, protocol ×10)
uint16   charge_stop_voltage_mv    # Charge stop voltage (mV)
uint32   servo_baud_rate           # STM32 servo communication baud rate
