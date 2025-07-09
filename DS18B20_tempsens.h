#include"types.h"
#define DS18B20_PIN 16 

// 1-WIRE PROTOCOL COMMANDS

#define SKIP_ROM         0XCC
#define CONVERT_T        0X44
#define READ_SCRATCHPAD  0XBE


// 1-WIRE PROTOCOL FUNCTION 
u8 reset_pulse(void);
void write_byte(u8 byte);
u8 read_byte(void);
f32 data_read(void);
