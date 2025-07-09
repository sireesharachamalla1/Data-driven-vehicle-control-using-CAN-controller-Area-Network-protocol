#include<lpc21xx.h>
#include "delay.h"
#include "defines.h"
#include "DS18B20_tempsens.h"

//FUNCTION TO PERFORM A 1-WIRE RESET AND PRESENCE DETECT

u8 reset_pulse()
{
     u8 presence;
	 //MAKE PIN AS OUTPUT PIN
	 SETBIT(IODIR1,DS18B20_PIN);
	 //MAKE PIN LOW 
	 SCLRBIT(IOCLR1,DS18B20_PIN);
	 //RESET PULSE DURATION
	 delay_us(480);
	 //MAKE PIN AS INPUT PIN
	 CLRBIT(IODIR1,DS18B20_PIN);
	 //WAIT FOR PRESENCE DETECT
	 delay_us(60);
	 //0(PRESENT) 1(NOT ON THE BUS)
	 presence=READBIT(IOPIN1,DS18B20_PIN);
	 // COMPLETE THE RESET CYCLE
	 delay_us(420);
	 return presence;
}

   // FUNCTION TO WRITE A BYTE TO THE 1-WIRE BUS

void write_byte(u8 byte)
{
      u8 i;
	  for(i=0;i<8;i++)
	  {
	     //MAKE PIN AS OUTPUT PIN
		 SETBIT(IODIR1,DS18B20_PIN);
		 // MAKE PIN LOW
		 SCLRBIT(IOCLR1,DS18B20_PIN);
		 //WRITE '1' IF BIT IS HIGH '0' IF LOW
		 delay_us((byte&1)? 10 : 60);  //10us DELAY IF BIT IS 1 THEN MAKING BIT AS HIGH...60us DELAY THAT IMPLIES 
		 SSETBIT(IOSET1,DS18B20_PIN);  // THIS WONT EFFECT IF BIT IS LOW
		 delay_us((byte&1)? 50 : 10 ); // REMAINING TIME SLOT
		 // write_bit(byte & 0x01);
		 byte >>=1;
	  }
}

//FUNCTION TO READ A BYTE FROM THE 1 - WIRE BUS 
u8 read_byte()
{
       u8 byte =0,i;
	   for(i=0;i<8;i++)
	   {
	         //MAKE PIN AS OUTPUT PIN
			 SETBIT(IODIR1,DS18B20_PIN);
			 // MAKE PIN LOW
			 SCLRBIT(IOCLR1,DS18B20_PIN);
			 delay_us(1);
			 //MAKE PIN AS INPUT PIN
			 CLRBIT(IODIR1,DS18B20_PIN);
			 // SAMPLE AFTER 15 us 
			 delay_us(14);
			 byte |= (READBIT(IOPIN1,DS18B20_PIN)<<i);
			 //REMAINING TIME SLOT
			 delay_us(45);
		}
		return byte;
}

// FUNCTION TO READ TEMPARATURE DATA FROM THE DS18B20
float data_read()
{
        s16 raw_temp;
		if(reset_pulse())
		{
		      // NO PRESENCE DETECTED,RETURN ERROR VALUE OR HANDLE ACCRODINGLY
			  return -273.15; // EXAMPLE ERROR VALUE (ABSOLUTE ZERO)
		}
		write_byte(SKIP_ROM);
		write_byte(CONVERT_T);
		// wait for 12- bit conversion 
		delay_ms(750);
		if(reset_pulse())
		{
		      return -273.15;
		}
		write_byte(SKIP_ROM);
		write_byte(READ_SCRATCHPAD);
		raw_temp = read_byte();
		raw_temp = raw_temp |(read_byte()<<8);
		return (float)raw_temp / 16.0;
}
