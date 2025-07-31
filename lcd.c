#include "types.h"
#include <LPC21XX.H>
#include "lcd_defines.h"
#include "defines.h"
#include "delay.h"
#include "lcd.h"
void WriteLCD(u8 byte) {
        SCLRBIT(IOCLR0,LCD_RW); // SELECT  WRITE OPERATION FOR THAT MAKE LCD_RW 0
        WRITEBYTE(IOPIN0,LCD_DATA,byte); //cmd/ascii/value
        SSETBIT(IOSET0,LCD_EN); // WRITING 1 on ENABLE
        delay_us(1);   // wait for >=450 ns
        SCLRBIT(IOCLR0,LCD_EN); // WRITING 0 on ENABLE
        delay_ms(2);
}
void CmdLCD(u8 cmd) {
        SCLRBIT(IOCLR0,LCD_RS); // WRITING 0 on RS //(Cmd/ins reg) will be sleceted so data on data pins treated as commands
        WriteLCD(cmd);
}
void InitLCD(void) {
        WRITEBYTE(IODIR0,LCD_DATA,0xFF);// Making LCD conneceted port pins as O/P Pins
        SETBIT(IODIR0,LCD_RS);   // RS_port pin as output
        SETBIT(IODIR0,LCD_RW);  // RW_port pin as output
        SETBIT(IODIR0,LCD_EN);
        delay_ms(15);
        CmdLCD(0x30);// func set cmd
        delay_ms(5); // to poduce delay >=4.1 msec
        CmdLCD(0x30); // fun set cmd
        delay_us(100); // to prodoce delay>=100 us
        CmdLCD(0x30); // fun set cmd
        CmdLCD(MODE_8BIT_2LINE); //8-bit mode with 2 line
        CmdLCD(DSP_ON_CUR_BLINK); // programmer choice
        CmdLCD(CLEAR_LCD);
}
void CharLCD(u8 asciiVal) {
        SSETBIT(IOSET0,LCD_RS);// RS --> to DATA REG
        WriteLCD(asciiVal);// data is sent to DDRAM via DATA REG
}
void StrLCD(s8 *str) {
        while(*str) {     // unitll pointer reaches NULL loop continues
                CharLCD(*str++); // post pointer inc previous (*val) sent to CharLCD
        }
}
void U32LCD(u32 num) {
        u8 a[10];   // array to stote each extracted digit as char
        s16 i=0;    // to access the array elements by indexing
        if(num==0) {
                CharLCD('0');  // if num is 0 directly print char '0'
        }
        else {
                while(num) {    // digit extraction .. unit becomes zero
                        a[i++]=(num%10)+'0';  // storing extarcted digit in array as char
                        num/=10;
                }
        }
        for(--i;i>=0;i--) {
                CharLCD(a[i]); // passing each char to fun to write on lcd
        }
}
void F32LCD(f32 num,u32 nDp) {  // to display float values .. 1st arg Float num.. 2nd arg is nDp_no_of_Decimal_points
        u32 i_num;
        if (num<0.0) { // if it  is -ve
                num=-num;
                CharLCD('-');  // printing -ve char
        }
        i_num=num; // extarcting non decimal part
        U32LCD(i_num); // passing it to U32LCD(fun)
        CharLCD('.');
        while(nDp--) {
                num=(num-i_num)*10; // assigning float value by shiftinng decimal each time towards right ..
                i_num=num; // exactracting non decimal part
                CharLCD(i_num+0x30);  // converting it to char passing
        }
}
void Intro() {
        u8 i,j;
        u8 *ptr=(u8 *)"WELCOME TO CAN PROJECT ";
        for(j=0;j<2;j++) {
                for(i=0;i<16;i++) {
                        CharLCD(ptr[i]);
                        delay_ms(100);
                }
                CmdLCD(GOTO_LINE2_POS0);
                for(;i<32;i++) {
                        CharLCD(ptr[i]);
                        delay_ms(100);
                }
                CmdLCD(GOTO_LINE1_POS0);
                for(i=0;i<16;i++) {
                        CharLCD(' ');
                        delay_ms(50);
                }
                CmdLCD(GOTO_LINE2_POS0);
                for(;i<32;i++) {
                        CharLCD(' ');
                        delay_ms(50);
                }
        CmdLCD(CLEAR_LCD);
        }
        CmdLCD(DSP_ON_CUR_OFF);
        StrLCD("  VECTOR INDIA");
        delay_s(2);
        CmdLCD(CLEAR_LCD);
}
