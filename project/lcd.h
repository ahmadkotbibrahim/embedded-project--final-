#ifndef lcd.h 
#define lcd.h


#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

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


#define LCD_RS  GPIO_PIN_0  // RS signal pin
#define LCD_RW  GPIO_PIN_1  // RW signal pin
#define LCD_E   GPIO_PIN_2  // E signal pin
#define LCD_D4  GPIO_PIN_4  // D4 data pin
#define LCD_D5  GPIO_PIN_5  // D5 data pin
#define LCD_D6  GPIO_PIN_6  // D6 data pin
#define LCD_D7  GPIO_PIN_7  // D7 data pin

#define LCD_WIDTH 16 // assume the LCD screen is 16 characters wide

// Function prototypes
void LCD_init(void);
void LCD_clear(void);
void LCD_set_cursor(uint8_t row, uint8_t col);
void LCD_write_string(char *string);
void LCD_write_char(char c);
void LCD_write_command(uint8_t command);
void LCD_write_data(uint8_t data);
void LCD_printf(const char* format, ...);


#endif