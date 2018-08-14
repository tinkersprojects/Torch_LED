# Torch_LED_V3 (working progress)
[https://tinkersprojects.com/](https://tinkersprojects.com/)

This library is similar to [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1) and [Torch_LED_V2](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V2) but with major updated  to functions, different setup and  button control. The setup to try make it easier to implement into any design and ay number of LEDs or functions. 
This library for the control of light functions within torches. There can be any number of functions or LEDs that can be used to controlled. There are 4 built in functions within the library that can be used. The default functions is run the number of times that there are LEDs to allow each LED to be lit up. There is also an ability to make your own functions, this will help you get the best settings for your torch. 
Torch_LED_V3 does not gets controlled internally by a button presses but instead by the **Button class**. The **Button class** is not required for the Torch_LED_V3 to be used and implement into any design. Functions NextFunction, GotoFunction and off are used to control the Torch_LED_V3 light functions.

## Other Torch_LED Versions
- [All Torch_LED](https://github.com/tinkersprojects/Torch_LED/)
- [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1)
- [Torch_LED_V2](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V2)
- [Torch_LED_V3](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V3)


## Torch_LED_V3 Functions
### SETUP
#### Torch_LED_V3(byte LEDs,CallbackFunction FunctionsArray[] = {});
#### Torch_LED_V3(byte LEDs[],CallbackFunction FunctionsArray[] = {});
     
### Library Control   
#### void NextFunction();
#### void GotoFunction(byte FunctionNumber);
#### void run();
#### void off();

### LED Control
#### void high(byte LED);
#### void allHigh();
#### void low(byte LED);
#### void allLow();
#### void value(byte LED, byte LEDvalue);

### Colour Functions
#### void defult();
#### void strobe();
#### void party();
#### void SOS();

## Button Functions

## Example
### Example 1: One LED

```c++
#include <Torch_LED_V3.h>

Torch_LED_V3 LEDs(5);

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

Torch_LED LEDs({5,2,8,9,10});

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
#include <Torch_LED_V3.h>

Torch_LED_V3 LEDs(3,2,8,9);

CallbackFunction Callback[] = {LEDs.F1,LEDs.F2,LEDs.strobe};
Torch_LED_V3 LEDs({3,2,8,9},Callback);

void setup() 
{
    
}

void loop() 
{
   LEDs.run();
}
```

### Example 4: New Functions

```c++
#include <Torch_LED_V3.h>

CallbackFunction Callback[] = {function1,function2,function3,function4,function5};
Torch_LED_V3 LEDs({5,2,8,9,10},Callback);

void setup() 
{
    
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
