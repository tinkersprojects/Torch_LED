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

#include "Torch_LED_V2.h"

/******************* SETUP *******************/

Torch_LED_V2::Torch_LED_V2(byte FirstLED,byte SecondLED,byte ThirdLED)
{
    LEDPin[0] = FirstLED;
    LEDPin[1] = SecondLED;
    LEDPin[2] = ThirdLED;
    pinMode(LEDPin[0], OUTPUT);
    pinMode(LEDPin[1], OUTPUT);
    pinMode(LEDPin[2], OUTPUT);
}

Torch_LED_V2::Torch_LED_V2(byte FirstLED,byte SecondLED)
{
    LEDPin[0] = FirstLED;
    LEDPin[1] = SecondLED;
    pinMode(LEDPin[0], OUTPUT);
    pinMode(LEDPin[1], OUTPUT);
}

Torch_LED_V2::Torch_LED_V2(byte FirstLED)
{
    LEDPin[0] = FirstLED;
    pinMode(LEDPin[0], OUTPUT);
}



/******************* SET *******************/

void Torch_LED_V2::NextFunction()
{
    FunctionCount++;
    Torch_LED_V2::GotoFunction(FunctionCount);
}

void Torch_LED_V2::GotoFunction(byte FunctionNumber)
{
    if(FuctionNumber <= sizeof(Callback) && Callback[FunctionNumber] != NULL)
        FunctionCount = FunctionNumber;
    else
        FunctionCount = 0;

    Torch_LED_V2::off();
    Torch_LED_V2::run();
}

void Torch_LED_V2::SetFunction(byte FuctionNumber, void (*newCallback) ())
{
    if(FuctionNumber <= sizeof(Callback) && FuctionNumber != 0)
    Callback[FuctionNumber+1] = newCallback;
}


/******************* COMMANDS *******************/

void Torch_LED_V2::run()
{
    if(ButtonPin != -1)
    {
        bool currentbuttonState = digitalRead(ButtonPin);
        if(currentbuttonState != buttonState && currentbuttonState == HIGH) 
        {
            lastButtonPressTime = millis();
            buttonState = currentbuttonState; 
        }
        else if(currentbuttonState != buttonState && currentbuttonState == LOW) 
        {
            Torch_LED_V2::NextFunction();
            buttonState = currentbuttonState; 
        }
        else if(buttonState == HIGH && lastButtonPressTime+3000 < millis()) 
        {
            FunctionCount = 0;
        }
    }



    if(FuctionNumber <= sizeof(Callback) && Callback[FuctionNumber-1] != NULL && FuctionNumber != 0)
        Callback[FuctionNumber-1]();
    else
        Torch_LED_V2::off();
}

void Torch_LED_V2::off()
{
    Torch_LED_V2::low(1);
    Torch_LED_V2::low(2);
    Torch_LED_V2::low(3);
}

void Torch_LED_V2::high(byte LED)
{
    if(LED <= sizeof(LEDPin) && LED != 0 && LEDPin[LED-1] != -1)
        digitalWrite(LEDPin[LED-1],HIGH);
}

void Torch_LED_V2::low(byte LED)
{
    if(LED <= sizeof(LEDPin) && LED != 0 && LEDPin[LED-1] != -1)
        digitalWrite(LEDPin[LED-1],LOW);
}

void Torch_LED_V2::value(byte LED, byte LEDvalue)
{
    if(LED <= sizeof(LEDPin) && LED != 0 && LEDPin[LED-1] != -1)
        analogWrite(LEDPin[LED-1],LEDvalue);
}


/******************* FUNCTIONS *******************/

void Torch_LED_V2::F1()
{
    Torch_LED_V2::high(1);
}

void Torch_LED_V2::F2()
{
    if(LEDPin[0] != -1 && LEDPin[1] != -1 && LEDPin[2] != -1)
            Torch_LED_V2::high(2);
    if(LEDPin[0] != -1 )
            Torch_LED_V2::value(1,180);
}

void Torch_LED_V2::F3()
{

    if(LEDPin[0] != -1 && LEDPin[1] != -1 && LEDPin[2] != -1)
            Torch_LED_V2::high(3);
    if(LEDPin[0] != -1 && LEDPin[1] != -1)
            Torch_LED_V2::high(2);
    if(LEDPin[0] != -1)
            Torch_LED_V2::value(1,120);

}

void Torch_LED_V2::strobe()
{
    if(millis()/100%2)
        Torch_LED_V2::high(1);
    else
        Torch_LED_V2::low(1);
}

void Torch_LED_V2::party()
{
    Torch_LED_V2::strobe();
    if(LEDPin[1] != -1)
    {
        if(millis()/100%2)
            Torch_LED_V2::low(2);
        else
            Torch_LED_V2::high(2);
    }
}

void Torch_LED_V2::SOS()
{
    byte timing = millis()/200%22;
    if(timing == 0 || timing == 2 || timing == 4  || (timing >= 8 && timing <= 10)  || (timing >= 12 && timing <= 14)  || (timing >= 16 && timing <= 18))
        Torch_LED_V2::high(1);
    else
        Torch_LED_V2::low(1);
}
