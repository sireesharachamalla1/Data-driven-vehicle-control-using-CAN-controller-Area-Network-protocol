#include <LPC21xx.H>


#include "adc_defines.h"

#include "types.h"

#include "defines.h"

#include "delay.h"




void Init_ADC(void)

{
  PINSEL1|= 0x15400000;
  ADCR = (1<<PDN_BIT)|(0<<CLKS)|(CLKDIV<<8);	

}


f32 Read_ADC(u8 chNo)

{

	u16 adcVal=0;f32 eAR;

       //select channel

	WRITEBYTE(ADCR,0,chNo);  

	//start the adc conversion

	SETBIT(ADCR,ADC_START_BIT);  

	//wait for conversion time (10 bit conversion time: 2.44 us)

        delay_us(3);

	//wait for done bit

        while(READBIT(ADDR,DONE_BIT) == 0);

	//stop the adc conversion

        CLRBIT(ADCR,ADC_START_BIT);  

	//collect the ADDR register content into adcVal variable

        adcVal = (ADDR>>6)&0x3FF;

	//eAR=((converted voltage*vref)/2^n-1);

	eAR = adcVal*(3.3/1023);

       return eAR;

}
