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

    FCB1 = F1;
    FCB2 = F2;
    FCB3 = F3;
    FCB4 = strobe;
    FCB5 = SOS;
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

    FCB1 = F1;
    FCB2 = F2;
    FCB3 = F3;
    FCB4 = strobe;
    FCB5 = SOS;
}

Torch_LED::Torch_LED(byte FuncNum,byte button,byte FirstLED)
{
    NumberOfFunctions = FuncNum;
    NumberOfLEDs = 1;
    ButtonPin = button;
    LED1Pin = FirstLED;
    pinMode(LED1Pin, OUTPUT);
    pinMode(ButtonPin, INPUT);

    FCB1 = F1;
    FCB2 = F2;
    FCB3 = F3;
    FCB4 = strobe;
    FCB5 = SOS;
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
            FCB1();
            break;
        case 2:
            FCB2();
            break;
        case 3:
            FCB3();
            break;
        case 4:
            FCB4();
            break;
        case 5:
            FCB5();
            break;
        default:
            Torch_LED::off();
            break;
    }
}

void Torch_LED::off()
{
    switch(NumberOfLEDs){
        case 3:
            digitalWrite(LED1Pin,LOW);
            digitalWrite(LED2Pin,LOW);
            digitalWrite(LED3Pin,LOW);
            break;
        case 2:
            digitalWrite(LED1Pin,LOW);
            digitalWrite(LED2Pin,LOW);
            break;
        case 1:
            digitalWrite(LED1Pin,LOW);
            break;
    }
}


/******************* FUNCTIONS *******************/

void F1()
{
    digitalWrite(LED1Pin,HIGH);
}

void F2()
{
    switch(NumberOfLEDs){
        case 1:
            digitalWrite(LED1Pin,HIGH);
            break;
        case 2:
            digitalWrite(LED2Pin,HIGH);
            break;
    }
}

void F3()
{
    switch(NumberOfLEDs){
        case 1:
            digitalWrite(LED1Pin,HIGH);
            break;
        case 2:
            digitalWrite(LED2Pin,HIGH);
            break;
        case 3:
            digitalWrite(LED3Pin,HIGH);
            break;
    }
}

void strobe()
{
    if(millis()/100%2)
        digitalWrite(LED1Pin,HIGH)
    else
        digitalWrite(LED1Pin,LOW);
}

void party()
{
    strobe();
    switch(NumberOfLEDs)
    {
        case 2:
            if(millis()/100%2)
                digitalWrite(LED2Pin,LOW)
            else
                digitalWrite(LED2Pin,HIGH);
            break;
    }
}

void SOS()
{
    byte timing = millis()/200%22;
    if(timing == 0 || timing == 2 || timing == 4  || (timing >= 8 && timing <= 10)  || (timing >= 12 && timing <= 14)  || (timing >= 16 && timing <= 18))
        digitalWrite(LED1Pin,HIGH);
    else
        digitalWrite(LED1Pin,LOW);
}
