# 运行时诊断数据（持续变化）
# 对应协议: diagnostic.rs / sr_diagnostic
# 温度字段: 实际值 = 原始值 / 10, 这里直接用 float32 表示实际值

uint32 uptime_s                  # 运行时间 (s)
uint8 cpu_usage_percent          # CPU 占用率 (%)
uint16 free_heap_kb              # 空闲堆 (KB)
uint16 stack_watermark_min_kb    # 启动以来最小剩余栈空间 (KB)
uint16 i2c_error_count
uint16 spi_error_count
uint16 uart_error_count
uint16 usb_error_count
uint32 frames_sent_total         # 累计发送帧数
uint16 pd_request_voltage_mv     # PD 握手请求电压 (mV)
uint16 pd_request_current_ma     # PD 握手请求电流 (mA)
float32 temp_servo_power         # 舵机电源温度 (°C)
float32 temp_5v_power            # 5V 电源温度 (°C)
float32 temp_mcu                 # MCU 温度 (°C)
float32 temp_charge              # 充电电路温度 (°C)
float32 temp_battery             # 电池温度 (°C)
