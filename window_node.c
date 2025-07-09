#include<lpc21xx.h>
#include "delay.h"
#include "can.h"
#define LED 0
void update_LEDS(u32 level)
{
	IOCLR0=0xFF<<LED;
	switch(level)
	{
		case 0:IOSET0=0xFF<<LED;
		        break;
		case 1:IOSET0=0xFE<<LED;
		        break;
		case 2:IOSET0=0xFC<<LED;
		        break;
		case 3:IOSET0=0xF8<<LED;
		        break;
		case 4:IOSET0=0xF0<<LED;
		        break;
		case 5:IOSET0=0xE0<<LED;
		        break;
		case 6:IOSET0=0xC0<<LED;
		        break;
		case 7:IOSET0=0x80<<LED;
		        break;
		case 8:IOSET0=0x00<<LED;
		        break;
		default:break;
	}
}
int main()
{
	CANF rxF;
	Init_CAN1();
	IODIR0|=0xFF<<LED;
	while(1)
	{
		CAN1_Rx(&rxF);
		if(rxF.ID==2)
		{
			u32 w_level=rxF.Data1;
			if(w_level<=8)
			{
				update_LEDS(w_level);
			}
		}
	}
}
				