/*----------------
File: Thermistor.c
Description: 
    Thermistor Module implementation
    Timer Channel 3
    ATD Channel 0
--------------------*/


#include "mc9s12dg256.h"
#include "thermistor.h"

// 10 ms
#define PERIOD 7500

volatile static int value;
static int i = 0;

void initThermistor(void)
{
    // Enable ATD converter
    ATD0CTL2 = 0xc2;
    // Minimum 20-microsecond delay
    for (i = 0; i < 480; ++i);
    
    // Conversion sequence length is set to 1
    ATD0CTL3 = 0x08;
    
    // 10-bit resolution, 16-cycle (maximum) sampling time, divisor 48
    // 0.5 MHz ATD clock
    ATD0CTL4 = 0x77;
    
    // Set output compare for timer channel 3
    TIOS |= 0x08;
    
    // Enable interrupt on timer channel 3
    TIE |= 0x08;
        
    // Start conversion
    ATD0CTL5 = 0x85;
    
    // Set up the first interrupt
    TC3 = TCNT + PERIOD;
}

int getTemp(void)
{
    return value * 5;
}

void interrupt VectorNumber_Vatd0 ATD_ISR(void)
{
    value = ATD0DR0;
}

void interrupt VectorNumber_Vtimch3 Timer_ISR(void)
{
    // Start conversion
    ATD0CTL5 = 0x85;
    
    TC3 = TC3 + PERIOD;
}
