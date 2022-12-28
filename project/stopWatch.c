#include "stopWatch.h"

void StopWatch(void)
{
// initialize LCD
LCD_init();

// configure 3 push buttons in a breadboard and connect them to Tiva C microcontroller

// enable clock for port F
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

// configure buttons as inputs
GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

// enable digital input on buttons
GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2,
                 GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

// enable pull-up resistors on buttons
GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

// configure buttons for interrupt-on-change behavior
GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2,
               GPIO_BOTH_EDGES);

// clear pending interrupts and enable interrupts on buttons
GPIOPinIntClear(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
GPIOPinIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

// define button press functions
    // main loop
    while (1)
    {
    if (get_key() == '#')
    {
            break;
    }
        // check button 1
        if (button1_pressed())
        {
            start_stopwatch();
        }
        // check button 2
        else if (button2_pressed())
        {
            pause_stopwatch();
        }
        // check button 3
        else if (button3_pressed())
        {
            reset_stopwatch();
        }

        // update LCD display
        update_lcd();
    }

}

// start the stopwatch
void start_stopwatch(void)
{
    // start timer
    // enable timer clock
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;

    // configure timer as periodic timer
    TimerDisable(TIMER1_BASE, TIMER_BOTH);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_BOTH, 16000000);

    // clear interrupt flag and enable timer interrupts
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER1A);

    // start timer
    TimerEnable(TIMER1_BASE, TIMER_BOTH);
}

// pause the stopwatch
void pause_stopwatch(void)
{
    // stop timer
    // disable timer
    TimerDisable(TIMER1_BASE, TIMER_BOTH);
}

// reset the stopwatch
void reset_stopwatch(void)
{
    // reset timer
    // disable timer
    TimerDisable(TIMER1_BASE, TIMER_BOTH);

    // reset timer
    TimerLoadSet(TIMER1_BASE, TIMER_BOTH, 16000000);
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // reset stopwatch
    seconds = 0;
    minutes = 0;
}

// update the LCD display
void update_lcd(void)
{
    // clear LCD
    LCD_clear();

    // update LCD with stopwatch time
    LCD_printf("%02d:%02d", minutes, seconds);
}

//check if buttons were pressed

bool button1_pressed(void)
{
    // check if button 1 is pressed
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != 0)
    {
        //button 1 is pressed
        return true;
    }
    else
    {
        // no buttons are pressed
        return false;
    }
}

bool button2_pressed(void)
{
    // check if button 2 is pressed
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) != 0)
    {
        //button 2 is pressed
        return true;
    }
    else
    {
        // no buttons are pressed
        return false;
    }
}
bool button3_pressed(void)
{
    // check if button 3 is pressed
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2) != 0)
    {
        //button 3 is pressed
        return true;
    }
    else
    {
        // no buttons are pressed
        return false;
    }
}