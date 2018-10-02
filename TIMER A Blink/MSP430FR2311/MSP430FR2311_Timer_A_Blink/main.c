#include <msp430.h>
/**
 * Kyle McKeown
 * MSP430FR2311_Timer_A_Blink
 * main.c
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;            // Disable the GPIO power-on default high-impedance mode
    P1DIR |= BIT0;                   // Sets Pins 1.0 (RED LED) to be an output
    P1REN |= BIT1;                   // Sets Pin 1.1 (Button) to be pull up/down enabled
    P1OUT |= BIT1;                   // Sets Pin 1.1 (Button) to pull up resistor
    P1OUT |= BIT0;                   // Sets Pin 1.0 (RED LED) to be ON
    P1IE  |= BIT1;                   // Enables interrupt on Pin 1.1 (Button)
    P1IES |= BIT1;                   // Enables high - to - low behavior on (Button press)
    TB0CCTL0 = CCIE;                 // CC interrupt enable
    TB0CCR0 =  1000;                 // Sets value in the CCR0 register
    TBCTL = TBSSEL_1 + MC_1 + ID_3;  // ACLK selected, Up-Count Enabled, Divide by 8

__enable_interrupt(); //Enables interrupts

    while (1) // While there is power
    {

    }
}
#pragma vector = TIMER0_B0_VECTOR //Timer B Interrupt that is triggered when the value in the CCR0 register is met by the clock

    __interrupt void Timer_B () // Major difference is that this is TImer B and there is no Timer A
    {
        P1OUT ^= BIT0; //Toggles Pin 1.0 (GREEN LED) on and off
    }
#pragma vector=PORT1_VECTOR //Port 1 Interrupt that is triggered when button is pressed

    __interrupt void Port_1(void)
    {
        TB0CCR0 -= 50; //Subtracts the value in the CCR0 register by 50, speeding up the frequency
        P1IFG &= ~BIT1; //Resets interrupt flag initially triggered
    }
