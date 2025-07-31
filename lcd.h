#ifndef _LCD_H
#define _LCD_H
#include "types.h"

void InitLCD(void);
void WriteLcd(u8 byte);
void CharLCD(u8 ascii);
void CmdLCD(u8 cmd);
void StrLCD(s8 *);
void S32LCD(s32);
void U32LCD(u32);
void F32LCD(f32, u32);
void BuildCgram(u8 *p,u8 );
void SetCursor(u8,u8);
void octLCD(u32 );
void hexLCD(u32 );

#endif





