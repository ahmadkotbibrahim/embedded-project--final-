#include "lcd.h"

// Initialize the LCD
void LCD_init(void)
{
    // Wait for the LCD to power on
    delay(100);

    // Set the LCD to 4-bit mode
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RS|LCD_RW|LCD_D4|LCD_D5|LCD_D6|LCD_D7, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, LCD_E);
    delay(1);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, 0);

    delay(5);

    // Set the LCD to 4-bit mode
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RS|LCD_RW|LCD_D4|LCD_D5|LCD_D6|LCD_D7, 0);
}

// Clear the LCD display
void LCD_clear(void)
{
    LCD_write_command(0x01);
    delay(2);
}

// Set the cursor to the specified position
void LCD_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address;
    if (row == 0)
        address = 0x80 + col;
    else
        address = 0xC0 + col;
    LCD_write_command(address);
}

// Write a character to the LCD display
void LCD_write_char(char c)
{
    LCD_write_data(c);
}

// Write a string to the LCD display
void LCD_write_string(char *string)
{
    while (*string)
        LCD_write_char(*string++);
}

// Write a command to the LCD
void LCD_write_command(uint8_t command)
{
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RS|LCD_RW|LCD_D4|LCD_D5|LCD_D6|LCD_D7, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, LCD_E);
    delay(1);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_D4|LCD_D5|LCD_D6|LCD_D7, command>>4);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, 0);
    delay(1);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, LCD_E);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_D4|LCD_D5|LCD_D6|LCD_D7, command);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, 0);
    delay(1);
}

// Write data to the LCD
void LCD_write_data(uint8_t data)
{
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RW, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RS, LCD_RS);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, LCD_E);
    delay(1);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_D4|LCD_D5|LCD_D6|LCD_D7, data>>4);
    GPIOPinWrite(GPIO_PORTF_BASE, LCD_E, 0);
    delay(1);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, LCD_E);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_D4|LCD_D5|LCD_D6|LCD_D7, data);
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E, 0);
    delay(1);
}

// print formatted string to LCD
void LCD_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    lcd_print(buffer);
}
