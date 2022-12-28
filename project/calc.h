#ifndef calc.h 
#define calc.h

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




// function prototypes
void calculator (void);
int perform_operation(char* input);
char *strpbrk(const char *str1, const char *str2);


#endif