# Torch_LED (working progress)
[https://tinkersprojects.com/](https://tinkersprojects.com/)
These are libraries for a torch that can do different functions. Each version is similar to each other with updated functionality and control.


## [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1)
Torch_LED_V1 is the first library for the control of light functions within torches. There can be any number of functions that can be used to control the torch LEDs. There are 7 built in functions within the library that can be used and 6 are set at default functions. There is also an ability to make your own functions, this will help you get the best settings for your torch. 
This library gets controlled internally by a button presses. By pressing the button, it will cycle through each function. Once there are no more functions, the torch will turn off. If the button is held down for more than 3 seconds the torch will turn off.

## [Torch_LED_V2](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V2)
This library is very similar to [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1) but with updated functions, different setup and updated internal button control. The setup to try make it easier to implement into any design. 
This library for the control of light functions within torches. There can be any number of functions that can be used to control the torch LEDs. There are 7 built in functions within the library that can be used and 6 are set at default functions. There is also an ability to make your own functions, this will help you get the best settings for your torch. 
This library does not by default gets controlled internally by a button presses but it can light in [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1). By pressing the button, it will cycle through each function. Once there are no more functions, the torch will turn off. If the button is held down for more than 3 seconds the torch will turn off.

## [Torch_LED_V3](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V3)
This library is similar to [Torch_LED_V1](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V1) and [Torch_LED_V2](https://github.com/tinkersprojects/Torch_LED/tree/master/Torch_LED_V2) but with major updated  to functions, different setup and  button control. The setup to try make it easier to implement into any design and ay number of LEDs or functions. 
This library for the control of light functions within torches. There can be any number of functions or LEDs that can be used to controlled. There are 4 built in functions within the library that can be used. The default functions is run the number of times that there are LEDs to allow each LED to be lit up. There is also an ability to make your own functions, this will help you get the best settings for your torch. 
Torch_LED_V3 does not gets controlled internally by a button presses but instead by the **Button class**. The **Button class** is not required for the Torch_LED_V3 to be used and implement into any design. Functions NextFunction, GotoFunction and off are used to control the Torch_LED_V3 light functions.
