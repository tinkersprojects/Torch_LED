#include <Torch_LED_V2.h>

Torch_LED_V2 LEDs(5,2,8,9,10);

void setup() 
{
    LEDs.SetFunction(1,function1);
    LEDs.SetFunction(2,function2);
    LEDs.SetFunction(3,function3);
    LEDs.SetFunction(4,function4);
    LEDs.SetFunction(5,function5);
}

void loop() 
{
   LEDs.run();
}



void function1()
{
    LEDs.value(1, 100);
}

void function2()
{
    LEDs.value(1, 180);
}

void function3()
{
    LEDs.high(1);
}

void function4()
{
    LEDs.high(2);
}

void function5()
{
    LEDs.high(3);
}