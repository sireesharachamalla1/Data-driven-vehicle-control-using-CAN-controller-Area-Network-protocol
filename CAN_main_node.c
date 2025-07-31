#include <LPC21XX.H>
#include "types.h"
#include "can.h"
#include "lcd.h"
#include "can_defines.h"
#include "ext_interrupt.h"
#include "lcd_defines.h"
#include "DS18B20_sens.h"
volatile u8 Gear,cnt;
CANF txF;
int main() {
        f32 temp;
        Int_Enable();
        InitLCD();
       // Intro();
        Init_CAN1();
        txF.ID=2;
        txF.BFV.RTR=0;
        txF.BFV.DLC=1;
        IOSET0=1<<LED;
        IODIR0|=1<<LED;
        CmdLCD(DSP_ON_CUR_OFF);
        while(1) {
                CmdLCD(RET_CUR_HOME);
                if(Gear==0)
                        StrLCD("FWD");
                else
                        get_dist();
                temp=data_read();
                CmdLCD(GOTO_LINE2_POS0);
                if(temp<-55)
                        StrLCD("T:ERROR");
                else {
                        StrLCD("T:");
                        F32LCD(temp,2);
                        CharLCD(0xDF);
                        StrLCD("C  ");
                }
                Window_disp(cnt);
        }
}