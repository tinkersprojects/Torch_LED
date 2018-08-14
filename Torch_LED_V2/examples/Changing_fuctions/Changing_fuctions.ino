#include <Torch_LED_V2.h>

Torch_LED_V2 LEDs(3,2,8,9);

void setup() 
{
    LEDs.SetFunction(1,LEDs.F1());
    LEDs.SetFunction(2,LEDs.F2());
    LEDs.SetFunction(3,LEDs.strobe());
}

void loop() 
{
   LEDs.run();
}