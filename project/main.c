#include "lcd.h"
#include "calc.h"
#include "keypad.h"
#include "stopWatch.h"

int counter = 3;

#include <stdio.h>


void welcome(void)
{
LCD_set_cursor(0, 0);
LCD_write_string("Welcome");
}


int main(void)
{
    // Set the system clock to run at 40 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    // Enable the GPIO port that the LCD is connected to
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);      

    // Configure the LCD pins as outputs
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, LCD_RS|LCD_RW|LCD_E|LCD_D4|LCD_D5|LCD_D6|LCD_D7);

    // Initialize the LCD
    LCD_init();
    
    // Clear the LCD display
    LCD_clear();
    
    // Initialize the keypad
    init_keypad();

    while(1)
    {
    if (get_key() == '#')
    {
      counter+=1;
      counter = counter % 3;
    }

    switch (counter)
    case 3 :
      welcome();
      break;
    case 0 :
      StopWatch();
      LCD_clear();
      break;
    case 1 :
      calculator();
      LCD_clear();
      break;
    case 2 :
      Timer();
      LCD_clear();
      break;
    }
    return 0;
}

