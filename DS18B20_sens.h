#include "types.h"
#define DS18B20_PIN 16 // Assuming P1.16 is used, adjust as needed

// 1-Wire protocol commands
#define SKIP_ROM        0xCC
#define CONVERT_T       0x44
#define READ_SCRATCHPAD 0xBE

//1-Wire protocol function
u8 reset_pulse(void);
void write_byte(u8 byte);
u8 read_byte(void);
f32 data_read(void);