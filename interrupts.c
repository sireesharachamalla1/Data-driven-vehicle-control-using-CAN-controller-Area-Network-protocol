#include<lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "can.h"

#define	EINT0_PIN    16
#define EINT1_PIN	   14
#define	EINT2_PIN	   15

#define	EINT0_VIC_CHNO	    14
#define	EINT1_VIC_CHNO	    15
#define	EINT2_VIC_CHNO	    16

extern int Gear;
extern int Window;
extern CANF Tx_Frame;

void Toggle_Gear(void)__irq
{
    Gear ^= 1;  // Toggle gear 

    EXTINT = 1<<0;         // Clear's EINT0 interrupt flag
    VICVectAddr = 0;       // Signaling that  end of ISR
}

void Window_up(void)__irq
{
    if(Window != 8)        // checking for maximum pos
    {
        Window++;
        Tx_Frame.Data1 = Window;
        CAN1_Tx(Tx_Frame);  // Sending data  over CAN1 structure for transmission
    }

    EXTINT = 1<<1;         // Clear's EINT1 interrupt flag
    VICVectAddr = 0;       // Signaling that  end of ISR
}

void Window_down(void)__irq
{
    if(Window != 0)        // checking for minimum pos
    {
        Window--;
        Tx_Frame.Data1 = Window;
        CAN1_Tx(Tx_Frame);  //  Sending data  over CAN1 structure for transmission
    }

    EXTINT = 1<<2;         // Clear EINT2 interrupt flag
    VICVectAddr = 0;       // End of ISR
}
void Init_Enable(void)
{
    PINSEL0 |= 0xA0000000;   // Setting P0.14 & P0.15 as EINT1 & EINT2
    PINSEL1 |= 0x15400001;   // Setting  P0.16 as EINT0 

    VICIntEnable = (1<<EINT0_VIC_CHNO) | (1<<EINT1_VIC_CHNO) | (1<<EINT2_VIC_CHNO);// Enable interrupts for EINT0,1,2

    // Assign ISRs to interrupt vectors
    VICVectCntl0 = (1<<5) |EINT0_VIC_CHNO;
    VICVectAddr0 = (u32)Toggle_Gear;

    VICVectCntl1 = (1<<5) |EINT1_VIC_CHNO;
    VICVectAddr1 = (u32)Window_up;

    VICVectCntl2 = (1<<5) | EINT2_VIC_CHNO;
    VICVectAddr2 = (u32)Window_down;


    EXTMODE = (1<<0) | (1<<1) | (1<<2);  // All as edge triggered

    EXTPOLAR = 0x0;  // All are  AL triggered
	}

