# Kyle McKeown - Button Based Delay
	The goal in this portion of the lab is to blink and LED at the same rate that a button is pressed down. In other words when the user presses and holds the button on the board, the LED will flash on and off at 50 percent duty cycle for an equal amount of time that the button is pressed. This is accomplished setting the initial frequency in the CCRO register to a preset value for the desired frequency and once the button is pressed triggering an interrupt to run based on the speed of the timer and an interrupt to trigger with a button press.

## This directory contains the following two project folders
* MSP430G2553_Button_Based_Delay
* MSP430F5529LP_Button_Based_Delay

## Processes Used to Imlement the Button Based Delay

The fundemental concept behind the inner-workings of this program is that it is layed out in a way that can be compared to a functional state machine. This state machine has three states and triggers to the next state based on the button being pressed, the button being released, and the blinking state that the program returns to as the button is released.

## Initial conditions

Timer A clock is selected
Up Mode is enabled
frequency is 10 Hz
the LED is blinking at a constant rate with 50 percent duty cycle

## When the button is pressed

The 10 Hz frequency that was determined in the initial conditions is cleared
Timer A is changed to continuous mode and counts up while that value is being recorded
The button is set to recognize low to high output(inverse logic) so that when the button is released it will chnge states

## When the Button is released

The value that was counted up to in the continuous mode on the Timer A register is stored in the CCR0 register.
Timer A is set back to up mode at this point
the button is set back to it's initial state to read from high to low (look for another button press)
The flag is cleared to exit the intterupt 

## Returns to the blinking state

At this point the program returns to the blinking state with the new value stored in the CCR0 register controlling the frequency in which the LED blinks.
The light will continue to blink at this rate until the button is pressed again to record a new value in the CCR0 register or until reset is pressed to return the value of the frequency to it's initial preset condition.

