/*--------------------------------------------
File: SegDisp.c
Description:  Segment Display Module
---------------------------------------------*/

#include <stdtypes.h>
#include "mc9s12dg256.h"
#include "SegDisp.h"
#include "Delay_asm.h"

#include <string.h>

static unsigned char display[4];

// Prototypes for internal functions

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
}

/*---------------------------------------------
Function: clearDisp
Description: Clears all displays.
-----------------------------------------------*/
void clearDisp(void) 
{
  memset(display, 0, sizeof(display));
  segDisp();
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
  switch (ch)
  {
  	case '0':
  		display[dispNum % 4] = 0x3f;
  		break;

  	case '1':
  		display[dispNum % 4] = 0x6;
  		break;

  	case '2':
  		display[dispNum % 4] = 0x5b;
  		break;

  	case '3':
  		display[dispNum % 4] = 0x4f;
  		break;

  	case '4':
  		display[dispNum % 4] = 0x66;
  		break;

  	case '5':
  		display[dispNum % 4] = 0x6d;
  		break;

  	case '6':
  		display[dispNum % 4] = 0x7d;
  		break;

  	case '7':
  		display[dispNum % 4] = 0x7;
  		break;

  	case '8':
  		display[dispNum % 4] = 0x7f;
  		break;

  	case '9':
  		display[dispNum % 4] = 0x6f;
  		break;
  	
  	default:
  	  display[dispNum % 4] = 0x40;
  	  break;
  }
}

/*---------------------------------------------
Function: segDisp
Description: Displays the codes in the code display table 
             (contains four character codes) on the 4 displays 
             for a period of 100 milliseconds by displaying 
             the characters on the displays for 5 millisecond 
             periods.
-----------------------------------------------*/
void segDisp(void) 
{
  int i, j, segment;
  
  setDelay(5);
  for (i = 0; i < 10; ++i)
  {
    segment = 1;
    for (j = 0; j < 4; ++j)
    {
      PTP = (PTP & 0xf0) | (~segment & 0x0f);
      PORTB = display[j];
      segment <<= 1;
      polldelay();
    }
  }
}
