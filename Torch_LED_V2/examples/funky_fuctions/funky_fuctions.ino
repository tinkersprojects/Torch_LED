#include <Torch_LED_V2.h>

Torch_LED_V2 LEDs(5,2,8,9,10);

void setup() 
{
    LEDs.SetFunction(1,LEDs.party());
    LEDs.SetFunction(2,function1);
    LEDs.SetFunction(3,function2);
    LEDs.SetFunction(4,function3);
    LEDs.SetFunction(5,function4);
}

void loop() 
{
   LEDs.run();
}



void function1()
{
    switch(millis()/800%3)
    {
        case 0:
            LEDs.high(1);
            LEDs.low(2);
            LEDs.low(3);
            break;
        case 1:
            LEDs.low(1);
            LEDs.high(2);
            LEDs.low(3);
            break;
        case 2:
            LEDs.low(1);
            LEDs.low(2);
            LEDs.high(3);
            break;
    }
}

void function2()
{
    if(millis()/800%2)
        LEDs.high(1);
        LEDs.high(2);
        LEDs.high(3);
    else
        LEDs.low(1);
        LEDs.low(2);
        LEDs.low(3);
}

void function3()
{
    if(millis()/100%2)
        LEDs.high(1);
        LEDs.high(2);
        LEDs.high(3);
    else
        LEDs.low(1);
        LEDs.low(2);
        LEDs.low(3);
}

void function4()
{
    if(millis()/1004%2)
        LEDs.value(1,(millis()%1004)/4);
        LEDs.value(2,(millis()%1004)/4);
        LEDs.value(3,(millis()%1004)/4);
    else
        LEDs.value(1,255-((millis()%1004)/4));
        LEDs.value(2,255-((millis()%1004)/4)));
        LEDs.value(3,255-((millis()%1004)/4)));
}