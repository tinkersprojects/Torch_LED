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

#include "Torch_LED.h"

/******************* SETUP *******************/

Torch_LED::Torch_LED(byte FuncNum,byte button,byte FirstLED,byte SecondLED,byte ThirdLED)
{
    NumberOfFunctions = FuncNum;
    NumberOfLEDs = 3;
    ButtonPin = button;
    LED1Pin = FirstLED;
    LED2Pin = SecondLED;
    LED3Pin = ThirdLED;
    pinMode(LED1Pin, OUTPUT);
    pinMode(LED2Pin, OUTPUT);
    pinMode(LED3Pin, OUTPUT);
    pinMode(ButtonPin, INPUT);
}

Torch_LED::Torch_LED(byte FuncNum,byte button,byte FirstLED,byte SecondLED)
{
    NumberOfFunctions = FuncNum;
    NumberOfLEDs = 2;
    ButtonPin = button;
    LED1Pin = FirstLED;
    LED2Pin = SecondLED;
    pinMode(LED1Pin, OUTPUT);
    pinMode(LED2Pin, OUTPUT);
    pinMode(ButtonPin, INPUT);
}

Torch_LED::Torch_LED(byte FuncNum,byte button,byte FirstLED)
{
    NumberOfFunctions = FuncNum;
    NumberOfLEDs = 1;
    ButtonPin = button;
    LED1Pin = FirstLED;
    pinMode(LED1Pin, OUTPUT);
    pinMode(ButtonPin, INPUT);
}



/******************* SET *******************/

void Torch_LED::NextFunction()
{
    FunctionCount++;
    if(FunctionCount >= 5 || FunctionCount >= NumberOfFunctions)
    FunctionCount = 0;
    Torch_LED::off();
    Torch_LED::run();
}

void Torch_LED::GotoFunction(byte FunctionNumber)
{
    FunctionCount = FunctionNumber;
    if(FunctionCount >= 5 || FunctionCount >= NumberOfFunctions)
    FunctionCount = 0;
    Torch_LED::off();
    Torch_LED::run();
}

void Torch_LED::SetFunction(byte FuctionNumber, void (*FCB) ())
{
    switch(FuctionNumber){
        case 1:
            FCB1 = FCB;
            break;
        case 2:
            FCB2 = FCB;
            break;
        case 3:
            FCB3 = FCB;
            break;
        case 4:
            FCB4 = FCB;
            break;
        case 5:
            FCB5 = FCB;
            break;
    }
}


/******************* COMMANDS *******************/

void Torch_LED::run()
{
    bool currentbuttonState = digitalRead(ButtonPin);
    if(currentbuttonState != buttonState && currentbuttonState == HIGH) 
    {
        lastButtonPressTime = millis();
        buttonState = currentbuttonState; 
    }
    else if(currentbuttonState != buttonState && currentbuttonState == LOW) 
    {
        Torch_LED::NextFunction();
        buttonState = currentbuttonState; 
    }
    else if(buttonState == HIGH && lastButtonPressTime+3000 < millis()) 
    {
        FunctionCount = 0;
    }

    switch(FunctionCount){
        case 1:
            if(FCB1 != NULL)
                FCB1();
            else
                Torch_LED::FCB1();
            break;
        case 2:
            if(FCB2 != NULL)
                FCB2();
            else
                Torch_LED::FCB2();
            break;
        case 3:
            if(FCB3 != NULL)
                FCB3();
            else
                Torch_LED::FCB3();
            break;
        case 4:
            if(FCB4 != NULL)
                FCB4();
            else
                Torch_LED::strobe();
            break;
        case 5:
            if(FCB5 != NULL)
                FCB5();
            else
                Torch_LED::SOS();
            break;
        default:
            Torch_LED::off();
            break;
    }
}

void Torch_LED::off()
{
    Torch_LED::low(1);
    Torch_LED::low(2);
    Torch_LED::low(3);
}

void Torch_LED::high(byte LED)
{
    if(LED == 1)
    {
        digitalWrite(LED1Pin,HIGH);
    }
    else if(LED == 2 && NumberOfLEDs>1)
    {
        digitalWrite(LED2Pin,HIGH);
    }
    else if(LED == 3 && NumberOfLEDs>2)
    {
        digitalWrite(LED3Pin,HIGH);
    }
}

void Torch_LED::low(byte LED)
{
    if(LED == 1)
    {
        digitalWrite(LED1Pin,LOW);
    }
    else if(LED == 2 && NumberOfLEDs>1)
    {
        digitalWrite(LED2Pin,LOW);
    }
    else if(LED == 3 && NumberOfLEDs>2)
    {
        digitalWrite(LED3Pin,LOW);
    }
}

void Torch_LED::value(byte LED, byte LEDvalue)
{
    if(LED == 1)
    {
        analogWrite(LED1Pin,LEDvalue);
    }
    else if(LED == 2 && NumberOfLEDs>1)
    {
        analogWrite(LED2Pin,LEDvalue);
    }
    else if(LED == 3 && NumberOfLEDs>2)
    {
        analogWrite(LED3Pin,LEDvalue);
    }
}


/******************* FUNCTIONS *******************/

void Torch_LED::F1()
{
    Torch_LED::high(1);
}

void Torch_LED::F2()
{
    switch(NumberOfLEDs){
        case 1:
            Torch_LED::value(1,180);
            break;
        case 2:
            Torch_LED::value(1,180);
            break;
        case 3:
            Torch_LED::high(2);
            break;
    }
}

void Torch_LED::F3()
{
    switch(NumberOfLEDs)
    {
        case 1:
            Torch_LED::value(1,120);
            break;
        case 2:
            Torch_LED::high(2);
            break;
        case 3:
            Torch_LED::high(3);
            break;
    }
}

void Torch_LED::strobe()
{
    if(millis()/100%2)
        Torch_LED::high(1);
    else
        Torch_LED::low(1);
}

void Torch_LED::party()
{
    Torch_LED::strobe();
    if(NumberOfLEDs > 1)
    {
        if(millis()/100%2)
            Torch_LED::low(2);
        else
            Torch_LED::high(2);
    }
}

void Torch_LED::SOS()
{
    byte timing = millis()/200%22;
    if(timing == 0 || timing == 2 || timing == 4  || (timing >= 8 && timing <= 10)  || (timing >= 12 && timing <= 14)  || (timing >= 16 && timing <= 18))
        Torch_LED::high(1);
    else
        Torch_LED::low(1);
}
