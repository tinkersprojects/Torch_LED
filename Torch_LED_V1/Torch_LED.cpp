/**********************************************************************************************
 * Arduino Torch LED V1 Library - Version 1.1
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Torch_LED_V1.h"

/******************* SETUP *******************/

Torch_LED_V1::Torch_LED_V1(int FuncNum,int button,int FirstLED,int SecondLED,int ThirdLED)
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

Torch_LED_V1::Torch_LED_V1(int FuncNum,int button,int FirstLED,int SecondLED)
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

Torch_LED_V1::Torch_LED_V1(int FuncNum,int button,int FirstLED)
{
    NumberOfFunctions = FuncNum;
    NumberOfLEDs = 1;
    ButtonPin = button;
    LED1Pin = FirstLED;
    pinMode(LED1Pin, OUTPUT);
    pinMode(ButtonPin, INPUT);
}



/******************* SET *******************/

void Torch_LED_V1::NextFunction()
{
    FunctionCount++;
    if(FunctionCount >= 6 || FunctionCount >= NumberOfFunctions+1)
    FunctionCount = 0;
    
    this->off();
    this->run();
}

void Torch_LED_V1::GotoFunction(int FunctionNumber)
{
    FunctionCount = FunctionNumber;
    if(FunctionCount >= 6 || FunctionCount >= NumberOfFunctions+1)
    FunctionCount = 0;
    this->off();
    this->run();
}

void Torch_LED_V1::SetFunction(int FuctionNumber, void (*FCB) ())
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

void Torch_LED_V1::run()
{
    bool currentbuttonState = digitalRead(ButtonPin);
    if(currentbuttonState != buttonState && currentbuttonState == HIGH) 
    {
        lastButtonPressTime = millis();
        buttonState = currentbuttonState; 
    }
    else if(currentbuttonState != buttonState && currentbuttonState == LOW) 
    {
        this->NextFunction();
        buttonState = currentbuttonState; 
    }
    else if(buttonState == HIGH && lastButtonPressTime+3000 < millis()) 
    {
        FunctionCount = 0;
    }

    switch(FunctionCount)
    {
        case 1:
            if(FCB1 != NULL)
                FCB1();
            else
                this->F1();
            break;
        case 2:
            if(FCB2 != NULL)
                FCB2();
            else
                this->F2();
            break;
        case 3:
            if(FCB3 != NULL)
                FCB3();
            else
                this->F3();
            break;
        case 4:
            if(FCB4 != NULL)
                FCB4();
            else
                this->strobe();
            break;
        case 5:
            if(FCB5 != NULL)
                FCB5();
            else
                this->SOS();
            break;
        default:
            this->off();
            break;
    }
}

void Torch_LED_V1::off()
{
    digitalWrite(LED1Pin,LOW);
    digitalWrite(LED2Pin,LOW);
    digitalWrite(LED3Pin,LOW);
}

void Torch_LED_V1::high(int LED)
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

void Torch_LED_V1::low(int LED)
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

void Torch_LED_V1::value(int LED, int LEDvalue)
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

void Torch_LED_V1::F1()
{
    this->high(1);
}

void Torch_LED_V1::F2()
{
    switch(NumberOfLEDs){
        case 1:
            this->value(1,180);
            break;
        case 2:
            this->value(1,180);
            break;
        case 3:
            this->high(2);
            break;
    }
}

void Torch_LED_V1::F3()
{
    switch(NumberOfLEDs)
    {
        case 1:
            this->value(1,120);
            break;
        case 2:
            this->high(2);
            break;
        case 3:
            this->high(3);
            break;
    }
}

void Torch_LED_V1::strobe()
{
    if(millis()/100%2)
        this->high(1);
    else
        this->low(1);
}

void Torch_LED_V1::party()
{
    this->strobe();
    if(NumberOfLEDs > 1)
    {
        if(millis()/100%2)
            this->low(2);
        else
            this->high(2);
    }
}

void Torch_LED_V1::SOS()
{
    int timing = millis()/200%22;
    if(timing == 0 || timing == 2 || timing == 4  || (timing >= 8 && timing <= 10)  || (timing >= 12 && timing <= 14)  || (timing >= 16 && timing <= 18))
        this->high(1);
    else
        this->low(1);
}
