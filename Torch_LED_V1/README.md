# Torch_LED_V1
[https://tinkersprojects.com/](https://tinkersprojects.com/)

Torch_LED_V1 is the first library for the control of light functions within torches. There can be any number of functions of functions that can be used to control the torch LEDs. There are 7 built in functions within the library that can be used and 6 are set at default functions. There is also an ability to make your own functions, this will help you get the best settings for your torch. 
This library gets controlled internally by a button presses. By pressing the button, it will cycle through each function. Once there are no more functions, the torch will turn off. If the button is held down for more than 3 seconds the torch will turn off.

## Other Torch_LED Versions
- [All Torch_LED](https://github.com/tinkersprojects/Torch_LED/)
- [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1)
- [Torch_LED_V2](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V2)
- [Torch_LED_V3](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V3)


## Functions
### SETUP
#### Torch_LED(byte FuncNum,byte button,byte FirstLED,byte SecondLED,byte ThirdLED);
#### Torch_LED(byte FuncNum,byte button,byte FirstLED,byte SecondLED);
#### Torch_LED(byte FuncNum,byte button,byte FirstLED);

### Library Control  
#### void NextFunction();
#### void GotoFunction(byte FunctionNumber);
#### void SetFunction(byte FunctionNumber, void (*FCB) ());
#### void run();
#### void off();

### LED Control
#### void high(byte LED);
#### void low(byte LED);
#### void value(byte LED, byte LEDvalue);

### Colour Functions
#### void F1();
#### void F2();
#### void F3();
#### void strobe();
#### void party();
#### void SOS();


## Example
### Example 1: One LED

```c++
#include <Torch_LED.h>

Torch_LED LEDs(5,2,8);

void setup() 
{
}

void loop() 
{
   LEDs.run();
}
```

### Example 2: Multi LEDs

```c++
#include <Torch_LED.h>

Torch_LED LEDs(5,2,8,9,10);

void setup() 
{
}

void loop() 
{
   LEDs.run();
}
```

### Example 3: Changing Functions

```c++
#include <Torch_LED.h>

Torch_LED LEDs(3,2,8,9);

void setup() 
{
    LEDs.SetFunction(1,LEDs.F1());
    LEDs.SetFunction(2,LEDs.F2());
    LEDs.SetFunction(3,LEDs.strobe());
}

void loop() 
{
   LEDs.run();
}
```

### Example 4: New Functions

```c++
#include <Torch_LED.h>

Torch_LED LEDs(5,2,8,9,10);

void setup() 
{
    LEDs.SetFunction(1,function1);
    LEDs.SetFunction(2,function2);
    LEDs.SetFunction(3,function3);
    LEDs.SetFunction(4,function4);
    LEDs.SetFunction(5,function5);
}

void loop() 
{
   LEDs.run();
}



void function1()
{
    LEDs.value(1, 100);
}

void function2()
{
    LEDs.value(1, 180);
}

void function3()
{
    LEDs.high(1);
}

void function4()
{
    LEDs.high(2);
}

void function5()
{
    LEDs.high(3);
}
```
