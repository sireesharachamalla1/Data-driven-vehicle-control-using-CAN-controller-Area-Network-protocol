#include <LPC21XX.H>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "can_defines.h"
#include "can.h"
void Init_CAN1(void) {
        //cfg p0.25 as CAN1_Rx
        PINSEL1=PINSEL1|0x15440000;
        //Reset CAN1 Controller
        SETBIT(C1MOD,RM_BIT);
        // Make all received messages are accepted
        CLRBIT(AFMR,AccOFF_BIT);
        SETBIT(AFMR,AccBP_BIT);
        //AFMR = 0x02;  // Directly set bypass mode
        //Set Baud Rate
        C1BTR=BTR_LVAL;
        //Enable CAN1 controller
        CLRBIT(C1MOD,RM_BIT);
}
void CAN1_Tx(CANF txF) {
        //check that the Tx buffer is empty/not
        while(READBIT(C1GSR,TBS1_BIT)==0);

        //cfg Tx ID in C1TID1
        C1TID1=txF.ID;
        //cfg RTR & DLC
        C1TFI1=(txF.BFV.RTR<<RTR_BIT)|(txF.BFV.DLC<<DLC_BITS);
        // Check wheather Data/Remote Frame to Transmit

        if(txF.BFV.RTR==0) { // Data Frame
                //load 1st 4 bytes in C1TDA1
                C1TDA1=(txF.Data[3]<<24)|(txF.Data[2]<<16)|(txF.Data[1]<<8)|(txF.Data[0]);

                //load 5-8 bytes in C1TDB1;
                C1TDB1=(txF.Data[7]<<24)|(txF.Data[6]<<16)|(txF.Data[5]<<8)|(txF.Data[4]);
        }

        //Select Tx Buff 1 & Start Xmission
        C1CMR|=(1<<TR_BIT)|(1<<STB1_BIT);
        // wait until Tx complete
        while(READBIT(C1GSR,TCS1_BIT)==0);
}
void CAN1_Rx(CANF *rxF) {
        //wait for CANF frame recv status
        while(READBIT(C1GSR,RBS_BIT)==0);
        // The above Bit will clear expicity or when entire recv bytes are read /partial read will not able to clear

        //read 11-bit CANid of recvd frame
        rxF->ID=C1RID;
        // Read and Extract data/remote frame
        rxF->BFV.RTR=(C1RFS>>RTR_BIT)&1;
        // Extract the Data lenth
        rxF->BFV.DLC=(C1RFS>>DLC_BITS)&0x0F;
        // check for Data/remote Frame

        if(rxF->BFV.RTR==0) { // recived Data Frame
                //Extract data bytes 1-4;
                rxF->Data[0]=C1RDA;
                rxF->Data[1]=C1RDA>>8;
                rxF->Data[2]=C1RDA>>16;
                rxF->Data[3]=C1RDA>>24;
                //Extract data bytes 5-8;
                rxF->Data[4]=C1RDB;
                rxF->Data[5]=C1RDB>>8;
                rxF->Data[6]=C1RDB>>16;
                rxF->Data[7]=C1RDB>>24;
        }
         //while (READBIT(C1GSR, RS_BIT));  // RS = 1 ? receiving, wait for 0
        // Release receive buffer command
        C1CMR|=1<<RRB_BIT;
}
