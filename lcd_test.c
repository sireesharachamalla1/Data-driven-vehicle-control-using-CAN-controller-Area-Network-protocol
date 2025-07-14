 #include "lcd.h"

#include "delay.h"

#include "lcd_defines.h"


u8 CGRAM_LUT[] = {0x17,0x14,0x14,0x1F,0x05,0x05,0x1D,0x00,0x0E,0x0E,0x15,0x0E,0x0E,0x04,0x0A,0x11};

int main()
{

	u8 i;

	InitLCD();

	BuildCGRAM(CGRAM_LUT,16);

	CharLCD(67);

	CharLCD(0);

	CharLCD(1);


	CharLCD('A');

	delay_s(1);

	CmdLCD(0x88);

	delay_s(1);

	CharLCD('B');

	delay_s(1);

	CmdLCD(0xC0);

	delay_s(1);

	CharLCD('X');

	delay_s(1);

	CmdLCD(0xC8);

	delay_s(1);

	CharLCD('Z');

	delay_s(1);

	CmdLCD(0x01);

	StrLCD("Hello World!");

	delay_s(1);

	CmdLCD(0x0C);

	for(i=0x8F;i>=0x80;i--)
	{

		CmdLCD(i);

		CharLCD('A');

		delay_ms(100);

		CmdLCD(CLEAR_LCD);
	}

	U32LCD(1234);

	S32LCD(-4587);

	F32LCD(1542.457,3);

	while(1);
}

