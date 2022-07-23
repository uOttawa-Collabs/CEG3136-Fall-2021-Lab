/*------------------------------------------------
File: siren.c

Description: The Siren module.
-------------------------------------------------*/
#include "mc9s12dg256.h"

// 
#define HIGH_CYCLE 500
#define LOW_CYCLE 500

void initSiren()
{
  // Set up output compare for channel 5
  TIOS |= 0x20;
}

#define HIGH 1
#define LOW 0
int levelTC5;  // level on TC5


void turnOnSiren()
{
  // Set OC5 output line to 1  
  TCTL1 |= 0x0c;
  // Forcing an event on timer channel 5 
  CFORC = 0x20;
   
  levelTC5 = HIGH;
  
  // Toggle OC5 output line
  TCTL1 &= (~0x0c | 0x04);
  
  // Initialize counter for the first interrupt
  // Since we are forcing high in the beginning,
  // the timer is added with HIGH_CYCLE
  TC5 = TCNT + HIGH_CYCLE;

  // Enable interrupt
  TIE |= 0x20;
}

void turnOffSiren()
{
  // Disable interrupt
  TIE &= ~0x20;
  // Disconnect timer from output pin
  TCTL1 &= 0xf3;
  
  // Forcing low level
  levelTC5 = LOW;
  // Forcing an event on timer channel 5
  CFORC = 0x20;
}


// ISR Call 
void interrupt VectorNumber_Vtimch5 siren_ISR(void)
{
  TC5 += (levelTC5 == HIGH ? HIGH_CYCLE : LOW_CYCLE);
  levelTC5 = (levelTC5 == HIGH ? LOW : HIGH);
}



