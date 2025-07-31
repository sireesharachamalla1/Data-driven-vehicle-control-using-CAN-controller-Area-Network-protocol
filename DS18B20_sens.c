#include <LPC21xx.h>
#include "delay.h"
#include "defines.h"
#include "DS18B20_sens.h"

// Function to perform a 1-Wire reset and presence detect
u8 reset_pulse() {
				u8 presence;
        // Make pin as Output PIN
				SETBIT(IODIR1,DS18B20_PIN);
        // Make pin LOW
        SCLRBIT(IOCLR1,DS18B20_PIN);
        // Reset pulse duration
        delay_us(480);
        // Make pin as Input PIN
        CLRBIT(IODIR1,DS18B20_PIN);
				// Wait for presence detect
        delay_us(60);
        //0(present) 1(not on the bus)
        presence=READBIT(IOPIN1,DS18B20_PIN);
        // Complete the reset cycle
        delay_us(420);
				return presence;
}

// Function to write a byte to the 1-Wire bus
void write_byte(u8 byte) {
				u8 i;
        for (i = 0; i < 8; i++) {
                // Make pin as Output PIN
                SETBIT(IODIR1,DS18B20_PIN);
                // Make pin LOW
                SCLRBIT(IOCLR1,DS18B20_PIN);
                // Write '1' if bit is high, '0' if low
                delay_us((byte&1)? 10 : 60); //10us delay if bit is 1 then making bit as high ..60us delay that implies the bit is low
                SSETBIT(IOSET1,DS18B20_PIN);  // this wont effect if bit is low
                delay_us((byte&1)? 50 : 10); // Remaining time slot
                //                      write_bit(byte & 0x01);
                byte >>= 1;
        }
}

// Function to read a byte from the 1-Wire bus
u8 read_byte() {
        u8 byte = 0,i;
        for (i = 0; i < 8; i++) {
                // Make pin as Output PIN
                SETBIT(IODIR1,DS18B20_PIN);
                // Make pin LOW
                SCLRBIT(IOCLR1,DS18B20_PIN);
                delay_us(1);
                // Make pin as Input PIN
                CLRBIT(IODIR1,DS18B20_PIN);
                // Sample after 15 us
                delay_us(14);
                byte|=(READBIT(IOPIN1,DS18B20_PIN)<<i);
          // Remaining time slot
                delay_us(45);
        }
	return byte;
}

// Function to read temperature data from the DS18B20
float data_read() {
        s16 raw_temp;
        if (reset_pulse()) {
                // No presence detected, return error value or handle accordingly
                return -273.15; // Example error value (Absolute Zero)
        }
        write_byte(SKIP_ROM);
        write_byte(CONVERT_T);
        // Wait for 12-bit conversion
        delay_ms(750);
        if (reset_pulse()) {
                return -273.15;
        }
        write_byte(SKIP_ROM);
        write_byte(READ_SCRATCHPAD);
        raw_temp = read_byte();
        raw_temp = raw_temp|(read_byte()<<8);
				return (float)raw_temp / 16.0;
}
