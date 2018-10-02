#include <msp430f5529.h>
/**
 * Kyle McKeown
 * MSP430F5529LP_Button_Interrupt
 * main.c
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= BIT0;              // Sets Pin 1.0 (RED LED) to be an output
    P1OUT |= BIT1;              // Sets Pin 1.1 (Button) to enable pull up resistor
    P1REN |= BIT1;              // Enables Pull up/down resistor
    P1OUT &= ~BIT0;             // Sets Pin 1.0 (RED LED) to 0 initially
    P1IE  |= BIT1;              // Interrupt is enabled on Pin 1.1 (Button)
    P1IES |= BIT1;              // Initially sets interrupt edge to go from high to low on PIN 1.1 (Button)

    __enable_interrupt();

    while(1)
    {

    }
}
// need to initialize the Ports to be interrupt enabled and clear the flags,
// this "Pragma Vector" tells the compiler that when a particular interrupt occurs, run this code.
#pragma vector=PORT1_VECTOR //Port 1 Vector interrupt occurs when Pin 1.1 (Button) goes from high to low

    __interrupt void Port_1(void)
    {
        P1OUT ^= BIT0;  // Red LED
        P1IFG &= ~BIT1; // Flag clear on Pin 1.1 (Button)
    }
