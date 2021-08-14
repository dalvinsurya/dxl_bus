# dxl_bus
firmware to emulate a dynamixel protocol based devices using dynamixel2arduino library.
Read slave's registers by sending read instruction packet from master device, slave will respond by sending status packet containing data from registers.

tested on teensy 3.1/3.2 boards at 1mbps baud.
