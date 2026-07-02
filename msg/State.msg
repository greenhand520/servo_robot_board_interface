# stm32 board info and state, message: /sensor/board_state

std_msgs/Header header

# servo DC-DC temperature (°C)
float32 servo_power_temp

# stm32 MCU temperature (°C)
float32 mcu_temp

# 5V output DC-DC temperature (°C)
float32 power_5v_temp

# servo DC-DC output voltage
float32 servo_power_voltage_v

# servo DC-DC output current
float32 servo_power_current_a

# charge_state
ChargerState charger_state
