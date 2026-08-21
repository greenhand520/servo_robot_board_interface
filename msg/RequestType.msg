# 重启 MCU
uint8 RESET                  = 0x01
# 关机（切断全部电源）
uint8 SHUTDOWN               = 0x02
# 触发 OTA 更新（bootloader 拷贝 OTA Temp → App 后重启）
uint8 OTA                    = 0x03
# ═══ 配置/查询 (0x10~0x1F, 需要应答) ═══
# 写入单个配置项
uint8 CONFIG_WRITE           = 0x10
# 查询单个配置项
uint8 CONFIG_QUERY           = 0x11
# 查询所有配置
uint8 CONFIG_QUERY_ALL       = 0x12
# 查询设备标识与内存布局（静态信息）
uint8 DEVICE_INFO            = 0x13
# ═══ 外设转发 (0x20~0x2F, 需要应答) ═══
# 转发舵机命令
uint8 SERVO_FORWARD          = 0x20
# 固件更新数据块
uint8 FIRMWARE_UPDATE        = 0x21