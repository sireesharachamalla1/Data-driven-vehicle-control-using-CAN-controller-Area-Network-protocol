#include "types.h"

// ext pins
#define E0 1     //p0.1
#define E1 3     //p0.3  another pin also support p0.14
#define E2 7     //p0.7  another pin also support p0.15
//#define E3 20  //p0.20 another pin also supporrt p0.9
// channels
#define E0_CH 14
#define E1_CH 15
#define E2_CH 16
//#define E3_CH 17

// funs & isr s
void Int_Enable(void);
void get_dist(void);
void Window_disp(u8);
void Toggle_Gear(void)__irq;
void Window_Up(void)__irq;
void Window_Down(void)__irq;

#define LED 22  //p0.22
