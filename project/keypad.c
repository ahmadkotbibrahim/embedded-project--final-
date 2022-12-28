#include "keypad.h"

void init_keypad() {
  // enable the GPIO port and pins for the keypad rows and columns
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);                  
  GPIOPinTypeGPIOInput(KEYPAD_ROW_PORT, KEYPAD_ROW1_PIN | KEYPAD_ROW2_PIN | KEYPAD_ROW3_PIN | KEYPAD_ROW4_PIN);
  GPIOPinTypeGPIOOutput(KEYPAD_COL_PORT, KEYPAD_COL1_PIN | KEYPAD_COL2_PIN | KEYPAD_COL3_PIN | KEYPAD_COL4_PIN);

  // set the keypad column pins to low
  GPIOPinWrite(KEYPAD_COL_PORT, KEYPAD_COL1_PIN | KEYPAD_COL2_PIN | KEYPAD_COL3_PIN | KEYPAD_COL4_PIN, 0);
}

// get the key pressed on the keypad
char get_key() {
  // define an array of characters for the keys
  char keys[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };

  // scan the keypad rows and columns
  for (int row = 0; row < KEYPAD_ROWS; row++) {
    // set the keypad row pin to high
    GPIOPinWrite(KEYPAD_ROW_PORT, KEYPAD_ROW1_PIN | KEYPAD_ROW2_PIN | KEYPAD_ROW3_PIN | KEYPAD_ROW4_PIN, (1 << row));

    // scan the keypad columns
    for (int col = 0; col < KEYPAD_COLUMNS; col++) {
      // check if the keypad column pin is low
      if (!GPIOPinRead(KEYPAD_COL_PORT, KEYPAD_COL1_PIN | KEYPAD_COL2_PIN | KEYPAD_COL3_PIN | KEYPAD_COL4_PIN)) {
        // return the key corresponding to the row and column
        return keys[row][col];
      }

      // set the keypad column pin to high
      GPIOPinWrite(KEYPAD_COL_PORT, KEYPAD_COL1_PIN | KEYPAD_COL2_PIN | KEYPAD_COL3_PIN | KEYPAD_COL4_PIN, (1 << col));
    }

    // set the keypad row pin to low
    GPIOPinWrite(KEYPAD_ROW_PORT, KEYPAD_ROW1_PIN | KEYPAD_ROW2_PIN | KEYPAD_ROW3_PIN | KEYPAD_ROW4_PIN, 0);
  }

  // no key was pressed
  return '\0';
}