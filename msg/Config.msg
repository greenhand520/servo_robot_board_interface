# 当前配置值的快照，字段顺序与协议 ConfigType 枚举值匹配

# === Switches/开关配置 (0x10~0x13) ===
bool     power_servo_on            # 舵机电源开关状态
bool     power_5v_on               # 5V电源开关状态
bool     charge_on                 # 充电开关状态
bool     bat_ext_out_on            # 电池对外输出开关状态

# === 充电设置 (0x20~0x21) ===
uint8    charge_stop_percentage    # 充电停止百分比 (1~100)
uint8    tx_log_level              # mcu发送给上位机的日志级别 (0:OFF 1:DEBUG 2:INFO 3:WARN 4:ERROR)

# === Limits (0x30~0x37) ===
uint16   servo_current_limit_ma    # 舵机母线电流限制 (mA)
float32  servo_power_temp_limit    # 舵机供电温度限制 (°C, protocol ×10)
float32  temp_5v_limit             # 5V电源温度限制 (°C, protocol ×10)
uint16   charge_max_current_ma     # 电池端充电限制电流 (mA)
float32  charge_temp_derating      # 充电温度降额 (°C, protocol ×10)
float32  charge_temp_limit         # 充电电路温度限制 (°C, protocol ×10)
uint16   charge_stop_voltage_mv    # 充电截止电压 (mV)
uint32   servo_baud_rate           # STM32与串口舵机通讯的波特率
