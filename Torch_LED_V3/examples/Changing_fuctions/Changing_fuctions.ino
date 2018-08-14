#include <Torch_LED_V3.h>

Torch_LED_V3 LEDs(3,2,8,9);

CallbackFunction Callback[] = {LEDs.F1,LEDs.F2,LEDs.strobe};
Torch_LED_V3 LEDs({3,2,8,9},Callback);

void setup() 
{
    
}

void loop() 
{
   LEDs.run();
}