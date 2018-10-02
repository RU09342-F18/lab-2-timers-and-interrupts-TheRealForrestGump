#include <msp430.h> 
/**
 * Kyle McKeown
 * MSP430G2553_Timer_A_Blink
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;        // stop watchdog timer
    BCSCTL3 |= LFXT1S_2;             // This forces the ACLK to use the VLOCLK rather than the 32kHz crystal oscillator
    P1DIR |= BIT0;                   // Sets Pin 1.0 (GREEN LED) to be an output
    P1REN |= BIT3;                   // Sets Pin 1.3 (Button) to be pull up/down enabled
    P1OUT |= BIT3;                   // Sets Pin 1.3 (Button) to pull up resistor
    P1OUT |= BIT0;                   // Sets Pin 1.0 (GREEN LED) to be on initially
    P1IE  |= BIT3;                   // Enables interrupt on Pin 1.3 (Button)
    P1IES |= BIT3;                   // Enables high - to - low behavior on (Button press)
    CCTL0  = CCIE;                   // CC interrupt enable
    CCR0   =  1000;                  // Sets value in the CCR0 register
    TACTL  = TASSEL_1 + MC_1 + ID_3; // ACLK selected, Up-Count Enabled, Divide by 8 (Timer A Control)

__enable_interrupt(); //Enables interrupts

    while (1) // While there is power
    {

    }
}
#pragma vector = TIMER0_A0_VECTOR //Timer A Interrupt that is triggered when the value in the CCR0 register is met by the clock

    __interrupt void Timer_A ()
    {
        P1OUT ^= BIT0; //Toggles Green LED
    }

#pragma vector = PORT1_VECTOR //Port 1 Interrupt that is triggered when button is pressed
    __interrupt void Port_1(void)
    {
        CCR0 -= 50; //Subtracts the value in the CCR0 register by 50, speeding up the frequency
        P1IFG &= ~BIT3; //Resets interrupt flag initially triggered
    }
