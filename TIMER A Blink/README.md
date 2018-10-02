# Kyle McKeown- TIMER A Blink

## Timer_A_Blink contains the following two folders
* MSP430G2553_Timer_A_Blink
* MSP430FR2311_Timer_A_Blink

	The goal in this portion of the lab was to use the built in timer modules to blink an LED based on the the clock speed that varies based on how many times the button is pressed. The way that I implemented the code was to trigger an interrupt to subtract a specified value from the CCR0 register that is enabled in up-count mode and compare that register to the timer A module that is continuously running. Each pass that the interrupt makes subtracts the value of 50 from the CCR0 register which causes the inturrupt that triggers the LED to happen at a faster rate with each button press. In my main function I am running an infinite while loop. However the lights cease to blink when the Frequency becomes too high or the value in the CCR0 register becomes 0

## Up, Down, Continuous 
	For Timer_A_Blink the CCR0 register is set to up mode. It was implemented this way so that the value in CCR0 register could be compared to the value in the Timer A register and fire an intterupt when the values were reached. 

## Differences Between The Two Boards
	One of the major differences between the two implementations of this code is that the FR2311 has a timer B module that has a different frequency than the timer A module that is found on the G2553. 
	The MSP430G2553  TIMER A operates at a frequency of 20 kHz
	The MSP430FR2311 TIMER B operates at a frequency of 8 MHz

In addition ports needed to be changed between the two boards and for the MSP430G2553 the 32kHZ crystal needed to be deactivated in favor of the VLOCLK and the GPIO power-on default had to be disabled on the MSP430FR2311 based on a reccomendation from the compiler. I still do not quite understand the significance of this but I know that the code runs much better with the following line of code: 

PM5CTLO &= ~LOCKLPM5;


