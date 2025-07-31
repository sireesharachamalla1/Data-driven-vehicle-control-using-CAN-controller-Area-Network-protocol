// TD1 CAN1_TX pin no alternate function
#define TD1_PIN

#define RD1_PIN0_25  // p0.25 as RD1

// BIT TIMING SETTING

#define PCLK          15000000
#define BIT_RATE      125000         //BITS_PER_SEC
#define QUANTA        20
#define BRP           (PCLK/(BIT_RATE*QUANTA))
#define SAMPLE_POINT  (0.7*QUANTA)
#define TSEG1         ((unsigned)SAMPLE_POINT-1)
#define TSEG2         (QUANTA-(1+TSEG1))
#define SJW           ((TSEG2>=5)?4:(TSEG2-1))

//cfg values for CxBTR sfr
#define SAM         0   //0/1,sample bus 1/3 times
#define BTR_LVAL    ((SAM<<23)|((TSEG2-1)<<20)|((TSEG1-1)<<16)|\
                    ((SJW-1)<<14)|(BRP-1))

// CxCMR sfr bit defines
#define TR_BIT   0
#define RRB_BIT  2
#define STB1_BIT 5

//CxGSR sfr bit
#define RBS_BIT  0
#define TBS1_BIT 2
#define TCS1_BIT 3
#define RS_BIT   4

//CxTF1/CxRFS  sfr
#define RTR_BIT   30
#define DLC_BITS  16

//CxMOD sfr
#define RM_BIT   0

//AFMR sfr
#define AccOFF_BIT  0
#define AccBP_BIT   1
