/*----------------------------------------------
File: Lab5Prog.c
Description: Main module for testing the Thermistor Module.
--------------------------------------------------*/
#include <stdtypes.h>
#include "main_asm.h"
#include "Thermistor.h"
#include "SegDisp.h"
#include "mc9s12dg256.h"

// Definitions
#define TSCALE 0b00000101 // 24Mhz Bus clock /32 gives 1 1/3 micro-sec/tick
#define HI_TEMP 270  // above hi temp - turn on led
#define BIT0 0b00000001
#define BIT1 0b00000010
#define BIT2 0b00000100
#define BIT4 0b00010000
#define BIT5 0b00100000
#define BIT6 0b01000000
#define BIT7 0b10000000
#define TEN_MS 7500 // ten ms = 7500 * 1.3333 micro-sec.
#define HIGH_TEMP 270

// Global variables
int displayTempFlag = TRUE;

//Prototypes
void initMain(void);
void displayTemp(int num); 

/*----------------------------------------------------
Function: main
Description:
  Overall control of Digital Thermometre. Consists of 
  a loop the reads temperature value and updates the
  7-segment display to show temperature and turns
  on/off LED.
---------------------------------------------------*/
void main()
{
   PLL_init();        // set system clock frequency to 24 MHz
   initMain();        // System initilisation
   for(;;) // loop forever
   {
   }
}

/*----------------------------------------------------
Function: initMain
Description: System initialisation.
             1) Setups Timer
             2) Calls module initialisation functions
             3) Configures PORTM to control LED.
             4) Allow interrupts.
----------------------------------------------------*/
void initMain(void)
{
   // Setup Timer
   TSCR1 = 0b10010000; // Enable and used fast clear
   TSCR2 = TSCALE;     // sets length of tick

   // Initialise Modules
   initThermistor();
   initDisp();
   
   // Setup Port P
   DDRP |= BIT4 | BIT5; // set pin 0 to output
   PTP &= ~BIT4; // turn off RED LED
   PTP |= BIT5;  // turn on Blue LED
   
      // Configure Timer Channel 6 for interrupt every 200 ms
   TIOS |= BIT6; // set TC4 to output-compare
	 TC6 = TCNT + TEN_MS; // Set TC6 for one ms delay
	 TIE |= BIT6; // enable interrupt timer channel 4
	 displayTempFlag = TRUE;   

   
   // Turn off LEDS
   PTJ |= BIT1; 
   
   asm cli; // enables interrupts 
}

/*----------------------------------------------------
Interrupt: tc6_isr
Description: This service routine displays temperature
             on the 7-segment display.
-------------------------------------------------------*/
void interrupt VectorNumber_Vtimch6 tc6_isr(void) 
{
    static int count = 20;  // need to count 20 - 10-ms times
    int temperature;
    count--;
    if(count == 0) 
    {
        temperature = getTemp();
        if(temperature >= HIGH_TEMP) 
        {
          PTP |= BIT4; // turn on RED LED
          PTP &= ~BIT5;  // turn off Blue LED
        }
        else 
        {
          PTP &= ~BIT4; // turn off RED LED
          PTP |= BIT5;  // turn on Blue LED
        }
        if(displayTempFlag) // check that its enabled
        {
            setCharDisplay(' ',3);  // blank last display
            displayTemp(temperature); // display the temperature
        }
        count = 20;      // reset count
    }
    TC6 = TC6+TEN_MS; // reading TC2 resets interrupt      
}

/*---------------------------------------------
Function: displayTemp
Description:  Setups the codes (calling setCharDisplay)
              for the temperature passed.
---------------------------------------------------*/
void displayTemp(int num) 
{
   byte ch;
   // tenth of degree
   ch = (byte)(num%10);  // get tenth
   ch = ch | 0x30; // convert to ASCII
   setCharDisplay(ch,2); // sets code for 3rd display
   turnOnDP(1);
   // units
   num = num/10;  
   ch = (byte)(num%10);  // get degree units
   ch = ch | 0x30; // convert to ASCII
   setCharDisplay(ch,1); // sets code for 2nd display 
   // 10's of degrees
   num = num/10;
   if(num != 0) 
   {
      ch = (byte)num;  // get 10's of degrees
      ch = ch | 0x30; // convert to ASCII
      setCharDisplay(ch,0); // sets code for 1rst display 
   } 
   else setCharDisplay(' ',0);
}
