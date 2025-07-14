#include<lpc21xx.h>
#include "can.h"
#include "lcd.h"
#include "DS18B20_tempsens.h"
#include "delay.h"
#include "interrupts.h"
#include<string.h>

// Constants
#define MAX_WINDOW_LEVEL 8
#define MIN_DISTANCE_ALERT 15
#define LED_PIN 9
#define BUZZER_PIN 10 

// Enums
enum GearMode { FORWARD = 0, REVERSE = 1 };

// Globals variablea
int Gear;
int Window;
CANF Rx_Frame, Tx_Frame;
float arr[8] = {12.5, 25, 37.5, 50, 62.5, 75, 87.5, 100};

// Display Messages
char str1[] = "HELLO    ";
char str2[] = "CAN MAJOR PROJECT  ";
char str3[] = "ID= V24HE5R2   ";

// Function Prototypes
void Show_Startup_Sequence(void);
void Display_Temperature(float temp);
void Display_Window_Status(int level);
void Handle_Reverse_Mode(void);
void Show_Forward_Mode(void);
void Init_LED(void);
void Control_LED(int distance);
void Setup_CAN_Frame(void);
void Init_Buzzer(void);


// Main Function
int main()
{
   // int distance;
    float temp;

    Init_CAN1();
    InitLCD();
	  Init_Buzzer(); 
    Init_Enable();
    Init_LED();
    Setup_CAN_Frame();
    Show_Startup_Sequence();

    while (1) {
        temp = data_read();
        Display_Temperature(temp);

        if (Gear == REVERSE)
            Handle_Reverse_Mode();
        else
            Show_Forward_Mode();

        Display_Window_Status(Window);
    }
}
// hello,id  display
void Show_Startup_Sequence(void)
{
    char *msgs[] = {str1, str2, str3};
    int positions[] = {0x80 + 5, 0xC0, 0x01};
     int i,j;
    for ( i = 0; i < 3; i++) 
    {
        CmdLCD(positions[i]);
        for (j =0;j<strlen(msgs[i]);j++)
	{
            CharLCD(msgs[i][j]);
            delay_ms(150);
        }
        delay_s(1);
        if (i != 2)
	  CmdLCD(0x01);  // Clear screen for next line
    }
 }

// Temperature display
void Display_Temperature(float temp) 
{
    CmdLCD(0xC0);
    StrLCD((s8*)"T=");
    F32LCD(temp, 1);
    CharLCD(0xDF);
    CharLCD('C');
}

// Reverse gear display and CAN receive
void Handle_Reverse_Mode(void)
{
    CmdLCD(0x80);
    StrLCD((s8*)"R:MODE");

    if (((C1GSR >> 1) & 1) == 1)
     {
        CAN1_Rx(&Rx_Frame);
        if (Rx_Frame.ID == 2)
	{
            int distance = Rx_Frame.Data1;
            CmdLCD(0x80 + 7);
            StrLCD((s8*)"D=");
            U32LCD(distance);
						StrLCD((s8*)"cm"); 
            Control_LED(distance);
        }
     }
     else
     {
        CmdLCD(0x80 + 7);
        StrLCD((s8*)"         ");
    }
  }

// Forward gear display
void Show_Forward_Mode(void)
{
    CmdLCD(0x80);
    StrLCD((s8*)"F:MODE      ");
  }

// Window status display
void Display_Window_Status(int level) 
{
    CmdLCD(0xC0 + 8);
    StrLCD((s8*)"W:");

    if (level == 0) 
    {
        StrLCD((s8*)"OPEN  ");
    } 
     else if (level == 7) 
      {
        StrLCD((s8*)"CLOSE ");
      }
      else
      {
        F32LCD(arr[level], 1);
        CharLCD('%');
      }
}

// LED control for reverse alert
void Control_LED(int distance) 
{
    if (distance < MIN_DISTANCE_ALERT)
     {
		IOCLR0 = 1 << LED_PIN;
		IOSET0 = 1 << BUZZER_PIN ;  // Buzzer ON
     }		    
    else
     {
	IOSET0 = 1 << LED_PIN;
        IOCLR0 = 1 << BUZZER_PIN;    //  Buzzer OFF 
     }
 }

// LED pin setup
void Init_LED(void) 
{
    IODIR0 |= 1 << LED_PIN;
    IOSET0 = 1 << LED_PIN;
  } 

	//  Buzzer Setup
void Init_Buzzer(void)
{
    IODIR0 |= 1 << BUZZER_PIN;
    IOCLR0 = 1 << BUZZER_PIN;  // Initially OFF
  }


	
// CAN frame setup
void Setup_CAN_Frame(void) 
{
    Tx_Frame.ID = 2;
    Tx_Frame.BFV.RTR = 0;
    Tx_Frame.BFV.DLC = 4;
  }
