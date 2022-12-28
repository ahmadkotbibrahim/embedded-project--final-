#ifndef stopWatch.h 
#define stopWatch.h


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

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
#include "lcd.h"

// global variables
uint32_t seconds = 0; // stopwatch seconds
uint32_t minutes = 0; // stopwatch minutes

// function prototypes
void start_stopwatch(void);
void pause_stopwatch(void);
void reset_stopwatch(void);
void update_lcd(void);
void StopWatch(void);
bool button1_pressed(void);
bool button2_pressed(void);
bool button3_pressed(void);


#endif