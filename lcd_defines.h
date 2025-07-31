#ifndef _LCD_DEFINES_H
#define _LCD_DEFINES_H
#include "types.h"
//HD44780 commands
#define CLEAR_LCD 0X01

#define RET_CUR_HOME 0X02
#define SHIFT_CUR_RIGHT 0X06
#define SHIFT_CUR_LEFT 0X10

#define DSP_OFF 0X08
#define DSP_ON_CUR_OFF 0X0C
#define DSP_ON_CUR_ON 0X0E
#define DSP_ON_CUR_BLINK 0X0F

#define SHIFT_DISP_LEFT 0X10
#define SHIFT_DISP_RIGHT 0X14

#define MODE_8BIT_1LINE 0X30
#define MODE_8BIT_2LINE 0X38

#define MODE_4BIT_1LINE 0X20
#define MODE_4BIT_2LINE 0X28

#define GOTO_LINE1_POS0 0X80
#define GOTO_LINE2_POS0 0XC0
#define GOTO_LINE3_POS0 0X94
#define GOTO_LINE4_POS0 0XD4
#define GOTO_CGRAM_START 0X40

#define LCD_DATA 8   //p0.8-p.15
#define LCD_RS 16    //p0.16
#define LCD_RW 17    //p0.17
#define LCD_EN 18    //p0.18



#endif







