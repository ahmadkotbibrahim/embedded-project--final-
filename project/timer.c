#include "timer.h"


void Timer(void)
{
  // Set the system clock to run at 40 MHz from the PLL
  SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

  // Initialize peripherals
  initGPIO();
  initUART();
  initTimer();
  init_keypad();
  LCD_init();
  LCD_clear();

  // Enable interrupts
  IntMasterEnable();

  // Wait for user input
  while (1)
  {
     if (get_key() == '#')
    {
            break;
    }
    // Check if the user pressed the D button on the keypad
    if (get_key() == 'D')
    {
      // Read the user's input as minutes and seconds
      LCD_clear();
      LCD_write_string("Enter minutes: ");
      minutes = get_key() - '0';
      LCD_write_char(minutes + '0');
      LCD_write_string("Enter seconds: ");
      seconds = get_key() - '0';
      LCD_write_char(seconds + '0');

      // Start the timer
      while (sysTickCount < minutes * 60 + seconds)
      {
        // Display the remaining time on the LCD
        LCD_clear();
        LCD_write_string("Time remaining: ");
        LCD_write_char(minutes - sysTickCount / 60 + '0');
        LCD_write_char(':');
        LCD_write_char(seconds - sysTickCount % 60 + '0');
      }

      // Display "finished" on the LCD
      LCD_clear();
      LCD_write_string("Finished!");
      break;  // exit the loop
    }
  }

}

// Initialize GPIO pins
void initGPIO(void)
{
  // Enable GPIO peripherals
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

  // Configure keypad columns as output pins
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0);

  // Configure keypad rows as input pins
  GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

  // Configure PF0 as an input pin
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

  // Configure LCD pins as output pins
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                        GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
                        GPIO_PIN_6 | GPIO_PIN_7);
}

void initUART(void)
{
  // Enable UART0 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  // Configure UART0 pins
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  // Set UART0 baud rate and other parameters
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
  UARTStdioConfig(0, 115200, 16000000);
}

// Initialize SysTick timer
void initTimer(void)
{
  // Set SysTick timer to generate an interrupt every 1 second
  SysTickPeriodSet(16000000);
  SysTickIntEnable();
  SysTickEnable();
}

// SysTick interrupt handler
void SysTickIntHandler(void)
{
  sysTickCount++;
}

