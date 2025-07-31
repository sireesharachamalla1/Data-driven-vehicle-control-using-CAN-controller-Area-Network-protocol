#include "types.h"
#include <LPC21XX.H>
#include "adc.h"
#include "defines.h"
#include "delay.h"
void Init_ADC(void) {
        ADCR=(1<<PDN_BIT)|(0<<CLKS)|(CLKDIV<<8); // PDN->1 ADC IN OPERATIONAL .. 0=CLKS=000 i.e 11 CLKS/CONVERSION  ..CLKDIV=(3+1)
        PINSEL1|=0x15400000;
}
f32 Read_ADC(u8 chNo) {
        u16 adcVal=0;f32 eAR;
        WRITEBYTE(ADCR,0,chNo);//SELECT CHANNEL NO A-0..A7
        SETBIT(ADCR,ADC_START_BIT);// CONVERSION WILL START FROM NOW
        delay_us(3); //Wait for Conversion time (2.44us Minimun);
        while(!(READBIT(ADDR,DONE_BIT)));
        CLRBIT(ADCR,ADC_START_BIT);// Stop's Conversion After Conversion Completed
        adcVal=(ADDR>>6)&0x3FF; // 10 bit data
        eAR=adcVal*(3.3/1023); //step size = (2^n)-1 //n=no of bits ..
return eAR;
}