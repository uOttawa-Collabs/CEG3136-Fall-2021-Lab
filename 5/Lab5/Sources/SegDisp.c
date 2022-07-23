/*--------------------------------------------
File: SegDisp.c
Description:  Segment Display Module
              Uses Timer Channel 1
---------------------------------------------*/

#include "mc9s12dg256.h"
#include "SegDisp.h"

#include <string.h>

// Global Variables
const static unsigned char digit[] = {
  0x3f, 0x06, 0x5b, 0x4f, 0x66,
  0x6d, 0x7d, 0x07, 0x7f, 0x6f,
  0x40    
};

static unsigned char display[4];


/*---------------------------------------------
Function: initDisp
Description: initializes hardware for the 
             7-segment displays.
-----------------------------------------------*/
void initDisp(void)
{
	DDRB = DDRP = 0xff;
	PTP = 0x0f;
	clearDisp();
	
	// Set output compare and enable interrupt for timer channel 1
	TIOS |= 0x02;
	TIE |= 0x02;
	
	// Set up the first interrupt
	TC1 = TCNT + 3750;
}

/*---------------------------------------------
Function: clearDisp
Description: Clears all displays.
-----------------------------------------------*/
void clearDisp(void) 
{
  memset(display, 0, sizeof(display));
}

/*---------------------------------------------
Function: setCharDisplay
Description: Receives an ASCII character (ch)
             and translates
             it to the corresponding code to 
             display on 7-segment display.  Code
             is stored in appropriate element of
             codes for identified display (dispNum).
-----------------------------------------------*/
void setCharDisplay(char ch, byte dispNum) 
{
  unsigned char d = ch - '0';
  dispNum %= 4;
  
  if (d > 9)
  {
    d = 10;      
  }
  
  display[dispNum] = digit[d] | (display[dispNum] & 0x80);
}


/*---------------------------------------------
Function: turnOnDP
Description: Turns on the decimal point of 2nd
             display from the left.
-----------------------------------------------*/
void turnOnDP(int dNum) 
{
  display[dNum % 4] |= 0x80;  
}

/*---------------------------------------------
Function: turnOffDP
Description: Turns off the decimal point of 2nd
             display from the left.
-----------------------------------------------*/
void turnOffDP(int dNum) 
{
  display[dNum % 4] &= ~0x80;
}


/*-------------------------------------------------
Interrupt: disp_isr
Description: Display interrupt service routine that
             to update displays every 5 ms.
---------------------------------------------------*/
void interrupt VectorNumber_Vtimch1 disp_isr(void)
{
  static int i = 0, segment = 1;

  PTP = (PTP & 0xf0) | (~segment & 0x0f);
  PORTB = display[i++];
  segment <<= 1;
  
  if (i >= 4)
  {
    i = 0;
    segment = 1;
  }
  
  
  // Set up next interrupt
  TC1 += 3750;
}


