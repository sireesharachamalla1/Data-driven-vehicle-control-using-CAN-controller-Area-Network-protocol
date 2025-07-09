/* can.h */
#ifndef __CAN_H__
#define __CAN_H__
#include "types.h"
typedef struct CAN_Frame
{
     u32 ID;
     struct BitField
     {
           u8 RTR : 1;
           u8 DLC : 4;
     }BFV;
     u32 Data1,Data2;
}CANF;
void Init_CAN1(void);
void CAN1_Tx(struct CAN_Frame);
void CAN1_Rx(struct CAN_Frame *);
#endif
