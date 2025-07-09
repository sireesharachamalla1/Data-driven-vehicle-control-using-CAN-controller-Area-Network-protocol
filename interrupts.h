#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

void Init_Enable(void);
void Toggle_Gear(void)__irq;
void Window_up(void)__irq;
void Window_down(void)__irq;

#endif
