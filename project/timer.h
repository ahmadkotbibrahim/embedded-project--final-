#ifndef timer.h 
#define timer.h

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "lcd.h"
#include "keypad.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_types.h"
#include "tm4c123gh6pm.h"
#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM 1
#endif
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "utils/delay.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"

// Declare functions
void initGPIO(void);
void initUART(void);
void initTimer(void);
void SysTickIntHandler(void);
void Timer(void);


// Global variables
uint32_t minutes = 0;
uint32_t seconds = 0;
uint32_t sysTickCount = 0;



#endif
