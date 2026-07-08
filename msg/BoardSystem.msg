# Board System Information,System status and diagnostics

uint16 device_id               # MCU Device ID
uint32 uid                     # MCU Unique ID
uint8  imu_id                  # IMU ID
uint32 uptime_s                # Uptime in seconds
uint8  cpu_usage_percent       # CPU usage (0-100)
uint16 free_heap_kb            # Free heap memory (KB)
uint16 stack_watermark_min_kb  # Minimum stack watermark (KB)
uint16 i2c_error_count         # I2C bus error count
uint16 spi_error_count         # SPI error count
uint16 uart_error_count        # UART error count
uint16 usb_error_count         # USB error count
uint32 frames_sent_total       # Total frames sent
uint16 pd_request_voltage_mv   # PD handshake voltage (mV)
uint16 pd_request_current_ma   # PD handshake current (mA)
string firmware_version        # mcu firmware_version

# Board Thermal Data,Temperature measurements

float32 temp_servo_power   # Servo power MOSFET temperature (°C)
float32 temp_5v_power      # 5V regulator temperature (°C)
float32 temp_mcu           # MCU die temperature (°C)
float32 temp_charge        # Charge circuit temperature (°C)
float32 temp_battery       # Battery NTC temperature (°C)
