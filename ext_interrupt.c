#include <LPC21XX.H>
#include "ext_interrupt.h"
#include "lcd.h"
#include "adc.h"
#include "lcd_defines.h"
#include "can.h"
#include "can_defines.h"
#include "delay.h"
#include "defines.h"

extern volatile u8 cnt,Gear;
extern CANF txF;

void Toggle_Gear(void)__irq {
        Gear^=1;
        CmdLCD(0x80+5);
        StrLCD("           ");
        EXTINT=1<<0;
        VICVectAddr=0;
}

void Window_Up(void)__irq {
        if(cnt!=8) {
                cnt++;
                txF.Data[0]=cnt;
                CAN1_Tx(txF);
        }
        EXTINT=1<<1;
        VICVectAddr=0;
}

void Window_Down(void)__irq {
        if(cnt!=0) {
                cnt--;
                txF.Data[0]=cnt;
                CAN1_Tx(txF);
        }
        EXTINT=1<<2;
        VICVectAddr=0;
}

void Int_Enable(void) {
        PINSEL0|=0x0000C0CC;
        VICIntEnable=(1<<E0_CH)|(1<<E1_CH)|(1<<E2_CH);
        VICVectCntl0=(1<<5)|(E0_CH);
        VICVectAddr0=(u32)Toggle_Gear;
        VICVectCntl1=(1<<5)|(E1_CH);
        VICVectAddr1=(u32)Window_Up;
        VICVectCntl2=(1<<5)|(E2_CH);
        VICVectAddr2=(u32)Window_Down;
        EXTMODE = ((1<<0) | (1<<1) | (1<<2));
        //configure EINT0,EINT1&EINT2 as Falling Edge Triggerd (use EXTPOLAR SFR)
}

void get_dist(void) {
        CANF RevF;
        u8 i;
        f32 dis;
				u32 idis;
        StrLCD("REV  ");
	
        if((READBIT(C1GSR,RBS_BIT))&&(C1RID==1)) {
				//	if(RevF.ID==1)
				//	{
                CAN1_Rx(&RevF);
					
                if(RevF.BFV.DLC==1) {
                        CmdLCD(GOTO_LINE1_POS0+7);
                        StrLCD("D:");
                        StrLCD("ERROR  ");
                }
                else {
                        for(i=0;i<4;i++)
                                ((u8*)&dis)[i]=RevF.Data[i];
									
				idis=(u32)(dis+0.5);   //convert float to integer
                        if(dis<15.0) {
                                if((((IOPIN0^=1<<LED)>>LED)&1)==0) {
                                        CmdLCD(GOTO_LINE2_POS0+12);
                                        CharLCD(0xEF);
                                }
                                else {
                                        CmdLCD(GOTO_LINE2_POS0+12);
                                        CharLCD(' ');
                                }
                        }
                        else if(((IOPIN0>>LED)&1)==0) {
                                CmdLCD(GOTO_LINE2_POS0+12);
                                CharLCD(' ');
                                IOSET0=1<<LED;
                        }
                        CmdLCD(GOTO_LINE1_POS0+7);
                        StrLCD("D:");
			U32LCD(idis);
		        StrLCD(" cm ");
                }
        }
        else
                StrLCD("         ");
}

void Window_disp(u8 num) {
        u8 i=0;
        static u8 c=1;
        if((((IOPIN0>>LED)&1)==0)&&(Gear==0)) {
                CmdLCD(GOTO_LINE2_POS0+12);
                CharLCD(' ');
                IOSET0=1<<LED;
        }
        if(c!=num) {
                // Building CGRAM TO SHOW WINDOW STATUS;
                for(i=0;i<(8-num);i++) {
                        CmdLCD(GOTO_CGRAM_START+i);
                        CharLCD(0x00);
                }
                if(num!=0) {
                        for(;i<8;i++) {
                                CmdLCD(GOTO_CGRAM_START+i);
                                CharLCD(0xFF);
                        }
                }
                c=num;
        }
        CmdLCD(GOTO_LINE2_POS0+15);
        CharLCD(0);
}
