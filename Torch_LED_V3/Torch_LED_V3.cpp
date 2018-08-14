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

#include "Torch_LED_V3.h"

/******************* SETUP *******************/
/*
Torch_LED_V3::Torch_LED_V3(...)
{
    va_list arguments;                     
    double sum = 0;

    va_start ( arguments, num );           
    for ( int x = 0; x < num; x++ )        
    {
        sum += va_arg ( arguments, double ); 
    }
    va_end ( arguments );                  // Cleans up the list

    return sum / num;

    
    LEDPins[sizeof(LEDs)] = LEDs;

    for(int i=0;i<sizeof(LEDPins);i++)
    {
        pinMode(LEDPins[i], OUTPUT);
    }
}*/

Torch_LED_V3::Torch_LED_V3(byte LEDs,CallbackFunction FunctionsArray[])
{
    LEDPins[1] = {LEDs};
    Torch_LED_V3::setUp(FunctionsArray);
}

Torch_LED_V3::Torch_LED_V3(byte LEDs[],CallbackFunction FunctionsArray[])
{
    LEDPins[sizeof(LEDs)] = LEDs;
    Torch_LED_V3::setUp(FunctionsArray);
}


void Torch_LED_V3::setUp(CallbackFunction FunctionsArray[])
{
    for(int i=0;i<sizeof(LEDPins);i++)
    {
        pinMode(LEDPins[i], OUTPUT);
    }

    if(sizeof(FunctionsArray)<=0)return;
    Callback[sizeof(FunctionsArray)] = {};
    for(int i=0;i<sizeof(FunctionsArray);i++)
    {
        Callback[i] = FunctionsArray[i];
    }
}


/******************* SET *******************/

void Torch_LED_V3::NextFunction()
{
    FunctionCount++;
}

void Torch_LED_V3::GotoFunction(byte FunctionNumber)
{
    FunctionCount = FunctionNumber+1;
}


/******************* COMMANDS *******************/

void Torch_LED_V3::run()
{
    if(FunctionCount > 0 && sizeof(Callback) <= 0)
    {
        Torch_LED_V3::defult();
    }
    else if(FunctionCount>0)
    {
        if(FunctionCount > sizeof(Callback)) FunctionCount = 1;
        Callback[FunctionCount]();
    }
    else
    {
        Torch_LED_V3::off();
    }
}

void Torch_LED_V3::off()
{
    FunctionCount = 0;
    Torch_LED_V3::allLow();
}

void Torch_LED_V3::high(byte LED)
{
    if(LED<sizeof(LEDPins))
    {
        digitalWrite(LEDPins[LED], HIGH);
    }
}

void Torch_LED_V3::allHigh()
{
    for(int i=0;i<sizeof(LEDPins);i++)
    {
        digitalWrite(LEDPins[i], HIGH);
    }
}

void Torch_LED_V3::low(byte LED)
{
    if(LED<sizeof(LEDPins))
    {
        digitalWrite(LEDPins[LED], LOW);
    }
}

void Torch_LED_V3::allLow()
{
    for(int i=0;i<sizeof(LEDPins);i++)
    {
        digitalWrite(LEDPins[i], LOW);
    }
}

void Torch_LED_V3::value(byte LED, byte LEDValue)
{
    if(LED<sizeof(LEDPins))
    {
        analogWrite(LEDPins[LED], LEDValue);
    }
}


/******************* FUNCTIONS *******************/

void Torch_LED_V3::defult()
{
    if(FunctionCount > sizeof(LEDPins) + 3) FunctionCount = 1;
         if(FunctionCount == sizeof(LEDPins) + 1) Torch_LED_V3::SOS();
    else if(FunctionCount == sizeof(LEDPins) + 2) Torch_LED_V3::strobe();
    else if(FunctionCount == sizeof(LEDPins) + 3) Torch_LED_V3::party();
    else
    {
        for(int i=0;i<sizeof(LEDPins);i++)
        {
            if(FunctionCount-1 == i)
            Torch_LED_V3::high(i);
            else
            Torch_LED_V3::low(i);
        }
    }
}

void Torch_LED_V3::strobe()
{
    for(int i=1;i<sizeof(LEDPins);i++)
    {
        Torch_LED_V3::low(i);
    }

    if(millis()/100%2)
        Torch_LED_V3::high(0);
    else
        Torch_LED_V3::low(0);
}

void Torch_LED_V3::party()
{
    for(int i=0;i<sizeof(LEDPins);i++)
    {
        if(millis()/200%sizeof(LEDPins) == i)
        Torch_LED_V3::high(i);
        else
        Torch_LED_V3::low(i);
    }
}

void Torch_LED_V3::SOS()
{
    for(int i=1;i<sizeof(LEDPins);i++)
    {
        Torch_LED_V3::low(i);
    }

    byte timing = millis()/200%22;
    if(timing == 0 || timing == 2 || timing == 4  || (timing >= 8 && timing <= 10)  || (timing >= 12 && timing <= 14)  || (timing >= 16 && timing <= 18))
        Torch_LED_V3::high(0);
    else
        Torch_LED_V3::low(0);
}
