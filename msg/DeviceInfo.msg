# 设备标识与内存布局（静态信息, 运行期间不变）
# 对应协议: device_info.rs / sr_device_info

uint16 device_id             # STM32 device ID (DBGMCU.IDCODE)
uint32 uid                   # STM32 unique ID
uint8 imu_id                 # IMU chip ID
string firmware_version      # 固件版本 "major.minor.patch"
uint16 ram_kb                # RAM 大小 (KB)
uint16 flash_boot_kb         # Bootloader Flash (KB)
uint16 flash_app_kb          # Application Flash (KB)
uint16 flash_ota_kb          # OTA Temp Flash (KB)
uint16 flash_user_kb         # User Data Flash (KB)
