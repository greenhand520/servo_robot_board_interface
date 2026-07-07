# Board Event
# Event and protection status
uint8  charge_phase        # Charge phase (0=NotCharging, 1=PreCharge, 2=Cc, 3=Cv, 4=Full, 5=PdSinkFault, 6=UnsupportedCharger)
uint16 state_change_flags  # State Change flags bitmask(bit0=ChargerConnect, bit1=Fan bit2=PowerServo bit3=Power5V bit4=BatExtOut)
uint16 protection_flags    # Protection flags bitmask (bit0=ServoOvercurrent, bit1=ServoThermal, bit2=Dcdc5vThermal, bit3=ChargeDerating, bit4=ChargeThermal, bit5=BatteryLow)
uint16 error_flags		   # Error flags bitmask (bit0=UNKNOWN_ERROR, bit1=UART1_ERROR, bit2=UART2_ERROR, bit3=I2C1_ERROR, bit4=I2C3_ERROR, bit5=SPI1_ERROR, bit6=USB_ERROR, bit7=DMA_ERROR)
