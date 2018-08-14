#include <Torch_LED.h>

Torch_LED LEDs(5,2,8);

void setup() 
{
}

void loop() 
{
   LEDs.run();
}