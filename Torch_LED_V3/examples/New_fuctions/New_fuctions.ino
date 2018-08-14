#include <Torch_LED_V3.h>

CallbackFunction Callback[] = {function1,function2,function3,function4,function5};
Torch_LED_V3 LEDs({5,2,8,9,10},Callback);

void setup() 
{
    
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