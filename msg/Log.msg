# mcu 发送给上位机的日志消息

uint8 LEVEL_OFF      = 0
uint8 LEVEL_DEBUG    = 1
uint8 LEVEL_INFO     = 2
uint8 LEVEL_WARN     = 3
uint8 LEVEL_ERROR    = 4

# Log level
uint8 level

# 源文件名（协议中以 null 结尾）
string file_name

# 源函数名称（协议中以 null 结尾）
string fun_name

# 日志消息内容
string msg

