# 统一应答帧
# 对应协议: response.rs / sr_response / RequestType

uint8 request_type     # RequestType 值 (0x01=Reset, 0x10=ConfigWrite, 0x11=ConfigQuery, 见RequestType.msg)
bool success           # 是否成功
uint8[] data           # 应答附加数据 (如 Config 值、BoardConfigSnapshot、DeviceInfo 等)
