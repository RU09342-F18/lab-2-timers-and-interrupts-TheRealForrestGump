#include <msp430.h>
/**
 * Kyle McKeown
 * MSP430F5529LP_Button_Based_Delay
 * main.c
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                // stop watchdog timer
    P1DIR |= BIT0;                           // Sets Pin 1.0 (RED LED) as an output
    P1REN |= BIT1;                           // Sets Pin 1.1 to be pull up/down enabled
    P1OUT |= BIT1;                           // Sets Pin 1.1 to pull up resistor
    P1OUT |= BIT0;                           // Sets Pin 1.0 (RED LED) to be ON to begin
    P1IE  |= BIT1;                           // Enables interrupt on Pin 1.1
    P1IES |= BIT1;                           // Enables high - to - low behavior on interrupt on Pin 1.1
    TA0CCTL0 = CCIE;                         // CCR0 Interrupt Enabled
    TA0CCR0 =  300;                          // Set Frequency
    TA0CTL = TASSEL_1 + MC_1 + ID_3;         // ACLK selected, Up-Mode, Divider

__enable_interrupt(); //Enables Interrupts

    while (1) // Generates an infinite loop
    {

    }
}

#pragma vector = TIMER0_A0_VECTOR //Timer Interrupt that is triggered when clock counts up to CCR0 value

    __interrupt void Timer_A ()
    {
        P1OUT ^= BIT0; //Toggles PIN 1.0 (RED LED) on/off
    }

#pragma vector=PORT1_VECTOR //Port 1 Interrupt that is triggered on button press (PIN 1.0) from high to low

    __interrupt void Port_1(void)
    {
        if (P1IES & BIT1) // button is pressed
        {
            TA0CTL = TACLR; //Clear existing value in clock's register
            TA0CTL = TASSEL_1 + MC_2 + ID_3;  //Clock is changed to Continuous mode but maintains ACLK and Divider 8
            P1IES &= ~BIT1; //Edge select is set to 0
        }
        else
        {
        // the button is released
            TA0CCR0 = TA0R; // Value in CCR0 is replaced by value in Timer A's register.
            TA0CTL = TASSEL_1 + MC_1 + ID_3;  // return to initial state
            P1IES |= BIT1; // back to initial state
        }

    P1IFG &= ~BIT1; //Flag from initial interrupt is cleared
    }
