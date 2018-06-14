#include <Torch_LED.h>

Torch_LED LEDs(5,2,8,9,10);

void setup() 
{
}

void loop() 
{
   LEDs.run();
}