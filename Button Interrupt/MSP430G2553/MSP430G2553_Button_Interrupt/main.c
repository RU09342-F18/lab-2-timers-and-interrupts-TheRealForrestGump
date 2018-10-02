#include <msp430.h> 
/**
 * Kyle McKeown
 * MSP430G2553_Button_Interrrupt
 * main.c
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0;              // Sets Pin 1.0 (GREEN LED) to be an output
    P1OUT |= BIT3;              // Sets Pin 1.3 (Button) to enable pull up resistor
    P1REN |= BIT3;              // Enables Pull up/down resistor
    P1OUT &= ~BIT0;             // Sets Pin 1.0 (GREEN LED) to 0 initially
    P1IE  |= BIT3;              // Interrupt is enabled on Pin 1.3 (Button)
    P1IES |= BIT3;              // Initially sets interrupt edge to go from high to low on PIN 1.3 (Button)

    __enable_interrupt();

    while(1)
    {

    }
}
// need to initialize the Ports to be interrupt enabled and clear the flags,
// this "Pragma Vector" tells the compiler that when a particular interrupt occurs, run this code.
#pragma vector=PORT1_VECTOR //Port 1 Vector interrupt occurs when Pin 1.3 (Button) goes from high to low

    __interrupt void Port_1(void)
    {
        P1OUT ^= BIT0;  // Green LED
        P1IFG &= ~BIT3; // Flag clear on Pin 1.3 (Button)
    }
