#include "calc.h"

void calculator (void)
{
  char input[LCD_WIDTH+1]; // buffer to store user input
  char key; // variable to store key press
  int input_len = 0; // variable to store length of user input
  int done = 0; // flag to indicate when user is finished inputting
  int result; // variable to store result of arithmetic operation

  // initialize keypad and LCD
  init_keypad();
  LCD_init();
  LCD_clear();

  // loop until user is finished inputting
  while (!done) {
    // get the key press from the user
    key = get_key();

    // check if key press is a digit
    if (key >= '0' && key <= '9') {
      // add the digit to the input buffer
      input[input_len] = key;
      input_len++;

      // update the input displayed on the first row of the LCD
      input[input_len] = '\0';
      LCD_set_cursor(0,0);
      LCD_write_string(input);
    }
    // check if key press is an operator
    else if (key == '+' || key == '-' || key == '/' || key == '*') {
      // add the operator to the input buffer
      input[input_len] = key;
      input_len++;

      // update the input displayed on the first row of the LCD
      input[input_len] = '\0';
      LCD_set_cursor(0,0);
      LCD_write_string(input);
    }
    // check if key press is the equals sign
    else if (key == '=') {
      // set the flag to indicate that the user is finished inputting
      done = 1;
    }

    // check if the input buffer is full
    if (input_len == LCD_WIDTH) {
      // set the flag to indicate that the user is finished inputting
      done = 1;
    }
  }

  // null-terminate the input string
  input[input_len] = '\0';

  // perform the arithmetic operation
  result = perform_operation(input);

  // print the result on the second row of the LCD
  char result_str[LCD_WIDTH+1];
  sprintf(result_str, "Result: %d", result);
  LCD_set_cursor(1,0);
  LCD_write_string(result_str);

  
}

int perform_operation(char* input) {
  char* op_ptr; // pointer to location of operator in input string
  int num1, num2; // operands
  char op; // operator
  int result; // result of arithmetic operation

  // find the location of the operator in the input string
  op_ptr = strpbrk(input, "+-*/");
  if (op_ptr == NULL) {
    // invalid input
    return 0;
  }

  // extract the operands and operator from the input string
  num1 = atoi(input);
  num2 = atoi(op_ptr + 1);
  op = *op_ptr;

  // perform the arithmetic operation
  switch (op) {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '/':
      result = num1 / num2;
      break;
    case '*':
      result = num1 * num2;
      break;
    default:
      // invalid operator
      result = 0;
      break;
  }

  return result;
}

char *strpbrk(const char *str1, const char *str2) {
  const char *s1, *s2;

  for (s1 = str1; *s1 != '\0'; s1++) {
    for (s2 = str2; *s2 != '\0'; s2++) {
      if (*s1 == *s2) {
        return (char *) s1;
      }
    }
  }

  return NULL;
}