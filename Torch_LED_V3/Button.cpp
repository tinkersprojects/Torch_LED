/**********************************************************************************************
 * Arduino LED Func Library - Version 1.0
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Button.h"

/******************* SETUP *******************/

Button::Button(byte LEDs,CallbackFunction FunctionsArray[])
{
    LEDPins[1] = {LEDs};
}

/******************* SET *******************/

void Torch_LED_V3::NextFunction()
{
    FunctionCount++;
}
