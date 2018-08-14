
#ifndef Torch_LED_V3_h
#define Torch_LED_V3_h

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
    #include <wiring.h>
#endif


typedef void (*CallbackFunction) ();
class Torch_LED_V3
{ 


    private:
        byte LEDPins[];
        int FunctionCount = 0;

        //typedef void (*CallbackFunction) ();
        CallbackFunction Callback[];

        void setUp(CallbackFunction FunctionsArray[]);

    public:
        Torch_LED_V3(byte LEDs,CallbackFunction FunctionsArray[] = {});
        Torch_LED_V3(byte LEDs[],CallbackFunction FunctionsArray[] = {});
        
        void NextFunction();
        void GotoFunction(byte FunctionNumber);
        void run();
        void off();

        void high(byte LED);
        void allHigh();
        void low(byte LED);
        void allLow();
        void value(byte LED, byte LEDvalue);

        void defult();
        void strobe();
        void party();
        void SOS();
};



#endif 
