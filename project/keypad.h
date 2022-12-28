#ifndef keypad.h 
#define keypad.h

#include <stdio.h>
#include <string.h>
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


// define constants for keypad rows and columns
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4

// define constants for keypad row and column pins
#define KEYPAD_ROW1_PIN GPIO_PIN_0
#define KEYPAD_ROW2_PIN GPIO_PIN_1
#define KEYPAD_ROW3_PIN GPIO_PIN_2
#define KEYPAD_ROW4_PIN GPIO_PIN_3
#define KEYPAD_COL1_PIN GPIO_PIN_4
#define KEYPAD_COL2_PIN GPIO_PIN_5
#define KEYPAD_COL3_PIN GPIO_PIN_6
#define KEYPAD_COL4_PIN GPIO_PIN_7

// define constants for keypad ports
#define KEYPAD_ROW_PORT GPIO_PORTE_BASE
#define KEYPAD_COL_PORT GPIO_PORTC_BASE

// define constants for keypad buttons
#define KEY_A 'A'
#define KEY_B 'B'
#define KEY_C 'C'
#define KEY_D 'D'
#define KEY_STAR '*'
#define KEY_HASH '#'


// function prototypes
void init_keypad();
char get_key();



#endif