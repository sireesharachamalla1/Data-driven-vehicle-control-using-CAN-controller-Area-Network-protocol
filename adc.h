#include "types.h"
#ifndef _ADC_H
#define _ADC_H

#define CH0 (1<<0)   //p0.27
#define CH1 (1<<1)   //p0.28
#define CH2 (1<<2)   //p0.29
#define CH3 (1<<3)   //p0.30

#define FOSC    12000000
#define CCLK    (5*FOSC)
#define PCCLK   (CCLK/4)
#define ADCLK   3750000  //PCCLK/4 (<=4.5MHZ)
#define CLKDIV  ((PCCLK/ADCLK)-1)

#define PDN_BIT   21
#define CLKS      17

#define ADC_START_BIT 24
//defines for ADDR
#define DONE_BIT   31

void Init_ADC(void);
f32 Read_ADC(u8);

#endif
