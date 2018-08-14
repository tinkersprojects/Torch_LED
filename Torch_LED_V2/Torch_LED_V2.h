
#ifndef Torch_LED_V2_h
#define Torch_LED_V2_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif


class Torch_LED_V2
{
    public:

        Torch_LED_V2(byte FirstLED,byte SecondLED,byte ThirdLED);
        Torch_LED_V2(byte FirstLED,byte SecondLED);
        Torch_LED_V2(byte FirstLED);
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
        int ButtonPin = -1;
        int LEDPin[3] = {-1,-1,-1};

        typedef void (*CallbackFunction) ();
        CallbackFunction Callback[5];

        byte FunctionCount = 0;
        unsigned long lastButtonPressTime;
        bool buttonState;
};



#endif 
