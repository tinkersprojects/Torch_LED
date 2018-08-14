
#ifndef Button_h
#define Button_h

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
    #include <wiring.h>
#endif

class Button
{ 


    private:
        byte LEDPins[];
        int FunctionCount = 0;

    public:
        Torch_LED_V3(byte LEDs,CallbackFunction FunctionsArray[] = {});

        void NextFunction();
};



#endif 
