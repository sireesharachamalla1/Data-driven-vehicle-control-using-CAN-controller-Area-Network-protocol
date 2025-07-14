#include<lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "adc.h"
#include "adc_defines.h"
#include "delay.h"
#include "can.h"
f32 aR0;
f32 distance;
CANF txF;

// Converts voltage to distance using GP2D12 sensor model
f32 volt_dist(f32 eAR) 
{
    f32 v = eAR; // eAR is already in volts
    distance = (6787 / (v - 3)) - 4;
    return distance;
}

int main()
{
    Init_CAN1();    // Initialize CAN1 peripheral
    Init_ADC();     // Initialize ADC peripheral

    txF.ID = 3;         // CAN message ID for reverse node
    txF.BFV.RTR = 0;    // Data frame (not remote)
    txF.BFV.DLC = 4;    // 4 bytes of data

    while (1)
    {
        aR0 = Read_ADC(CH0);          // Read analog voltage from channel 0
        distance = volt_dist(aR0);    // Convert voltage to distance

        if ((distance >= 6) && (distance <= 85))
	{
            txF.Data1 = distance;     // Send distance in Data1
            CAN1_Tx(txF);             // Transmit via CAN
	}

        delay_ms(100);                // Transmit every 100 ms
   }

    return 0;
  }
