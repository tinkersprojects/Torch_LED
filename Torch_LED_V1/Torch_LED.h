
#ifndef Torch_LED_h
#define Torch_LED_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


class Torch_LED
{
    public:

        Torch_LED(byte FuncNum,byte button,byte FirstLED,byte SecondLED,byte ThirdLED);
        Torch_LED(byte FuncNum,byte button,byte FirstLED,byte SecondLED);
        Torch_LED(byte FuncNum,byte button,byte FirstLED);
        void NextFunction();
        void GotoFunction(byte FunctionNumber);
        void SetFunction(byte FuctionNumber, void (*FCB) ());
        void run();
        void off();

        void high(byte LED);
        void low(byte LED);
        void value(byte LED, byte LEDvalue);

        void F1();
        void F2();
        void F3();
        void strobe();
        void party();
        void SOS();

    private:
        byte NumberOfFunctions;
        byte NumberOfLEDs;
        byte ButtonPin;
        byte LED1Pin;
        byte LED2Pin;
        byte LED3Pin; 

        void (*FCB1) ();
        void (*FCB2) ();
        void (*FCB3) ();
        void (*FCB4) ();
        void (*FCB5) ();

        byte FunctionCount = 0;
        unsigned long lastButtonPressTime;
        bool buttonState;
};



#endif 
