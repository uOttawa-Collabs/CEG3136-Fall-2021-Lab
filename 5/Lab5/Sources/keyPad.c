/*-----------------------------------------------------------
    File: keyPad.c
    Description: Module for reading the keypad using interrupts
                 and timer channel 4.
	fall 2020
-------------------------------------------------------------*/

#include "mc9s12dg256.h"
#include "keyPad.h"

// Prescale = 32
// Scaled clock period = 1/24 * 32 us = 4/3 us
// Delay period = 7500 * 4/3 us = 10000 us = 10 ms
#define DELAY_CYCLE 7500

// Global variables
const static struct
{
  unsigned char keycode;
  char character;
}
keyCodeMap[] = {
  { 0xee, '1' },
  { 0xed, '2' },
  { 0xeb, '3' },
  { 0xe7, 'a' },
  { 0xde, '4' },
  { 0xdd, '5' },
  { 0xdb, '6' },
  { 0xd7, 'b' },
  { 0xbe, '7' },
  { 0xbd, '8' },
  { 0xbb, '9' },
  { 0xb7, 'c' },
  { 0x7e, '*' },
  { 0x7d, '0' },
  { 0x7b, '#' },
  { 0x77, 'd' }
};
  
volatile unsigned char keyCode;

// Local Function Prototypes


/*---------------------------------------------
Function: initKeyPad
Description: initializes hardware for the 
             KeyPad Module.
-----------------------------------------------*/
void initKeyPad(void) 
{
  DDRA = 0xf0;
  PORTA = 0x00;
  PUCR |= 0x01;
  
  // TC4 - Output compare
  TIOS |= 0x10;
  // Enable interrupt
  TIE |= 0x10;
  // Set up first interrupt
  TC4 = TCNT + DELAY_CYCLE;
  
  keyCode = NOKEY;
}

/*-------------------------------------------------
Interrupt: readKey
Description: Waits for a key and returns its ASCII
             equivalent.
---------------------------------------------------*/
char readKey() 
{
  char c;
  
  while (keyCode == NOKEY);
  c = translate(keyCode);
  keyCode = NOKEY;
  
  return c;
}
/*-------------------------------------------------
Interrupt: pollReadKey
Description: Checks for a key and if present returns its ASCII
             equivalent; otherwise returns NOKEY.
---------------------------------------------------*/
char pollReadKey() 
{
  char c;
  
  if (keyCode == NOKEY)
    c = NOKEY;
  else
  {
    c = translate(keyCode);
    keyCode = NOKEY;  
  }
  
  return c;
}

/*---------------------------------------------
Function: translate
Description: translate the keycode to ASCII char
-----------------------------------------------*/
char translate(unsigned char keyCode)
{
  int i;
  char c = BADCODE;
  
  for (i = 0; i < sizeof(keyCodeMap); ++i)
  {
    if (keyCodeMap[i].keycode == keyCode)
    {
      c = keyCodeMap[i].character;
      break;
    }
  }
  
  return c;
}

/*---------------------------------------------
Function: readKeyCode
Description: get a keycode from the keypad
-----------------------------------------------*/
#define ROW1 0xef
#define ROW2 0xdf
#define ROW3 0xbf
#define ROW4 0x7f

unsigned char readKeyCode()
{
  volatile unsigned char code;
  
  PORTA = ROW1;
  if (PORTA == ROW1)
  {
    PORTA = ROW2;
    if (PORTA == ROW2)
    {
      PORTA = ROW3;
      if (PORTA == ROW3)
      {
        PORTA = ROW4;
      }
    }
  }
  
  code = PORTA;
  PORTA = 0;
  return code;
}

/*-------------------------------------------------
Interrupt: key_isr
Description: Display interrupt service routine
             that checks keypad every 10 ms.
---------------------------------------------------*/
void interrupt VectorNumber_Vtimch4 key_isr(void)
{
  static unsigned char state = 0;
  static unsigned char t;
  
  switch (state)
  {
    case 0:           // State 0: Waiting for the key press from user
      t = PORTA;
      if (t != 0x0f)
        ++state;
      break;
    case 1:           // State 1: Debouncing key press
      if (t != PORTA)  
        --state;
      else
      {
        t = readKeyCode();
        ++state;
      }
      break;
    case 2:           // State 2: Waiting for the key release from user
      if (PORTA == 0x0f)
        ++state;
      break;
    case 3:           // State 3: Debouncing release
      if (PORTA != 0x0f)
        --state;
      else
      {
        keyCode = t;
        state = 0;
      }
      break;
    default:
      break;
  }
  // Set up next interrupt
  TC4 = TC4 + DELAY_CYCLE;
}
