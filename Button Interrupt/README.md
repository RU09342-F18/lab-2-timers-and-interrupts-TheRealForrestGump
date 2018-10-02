# Kyle McKeown - Button Interrupt
The goal of this portion of the lab is to utilize the function of interrupts to turn an LED on with a button press and with another button press enable the interrupt again to turn the LED off. This is accomplished by the use of "PRAGMA VECTOR" which tells the compiler to to run a particular code when an interrupt occurs. In this case the interrupt is a button on the board that registers when a high to low output is detected. 

## This Directory contains the following two folders

* MSP430G2553_Button_Interrupt
* MSP430F5529LP_Button_Interrupt

## Task

An important concept to consider in the case of an interrupt is the flag clear after the interrupt has been executed. This can be viewed as similar to a break statement to tell the compiler to only execute the code within the interrupt code once as desired. There may be a situation where the user would want to run the code more than one time before the flags were cleared but in the case of toggling an LED on and off we only want the bit to change states and then exit the intterupt code.

## Differences between the two boards

There is not much difference at all between the code for the two boards used. all of the components are the same, a clock is not used so we do not need to worry about varying frequencies.
The ports are in slightly different locations and the LED colors vary from green to red on port (1.0) but the application of the code is exactly the same.

