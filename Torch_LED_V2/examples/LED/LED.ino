#include <Torch_LED_V2.h>

Torch_LED_V2 LEDs(5,2,8);

void setup() 
{
}

void loop() 
{
   LEDs.run();
}