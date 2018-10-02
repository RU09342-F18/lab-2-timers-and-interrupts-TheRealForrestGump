#include <msp430.h>
/**
 * Kyle McKeown
 * MSP430G2553_Button_Based_Delay
 * main.c
*/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                // stop watchdog timer
    BCSCTL3 = LFXT1S_2;                      // This forces the ACLK to use the VLOCLK rather than the 32kHz crystal oscillator
    P1DIR |= BIT0;                           // Sets Pins 1.0 (GREEN LED) as an output
    P1REN |= BIT3;                           // Sets Pin 1.3 (Button) to be pull up/down enabled
    P1OUT |= BIT3;                           // Sets Pin 1.3 (Button) to pull up resistor
    P1OUT |= BIT0;                           // Sets Pin 1.0 (GREEN LED) to be initially on
    P1IE  |= BIT3;                           // Enables interrupt on PIN 1.3 (Button)
    P1IES |= BIT3;                           // Enables high - to - low behavior on interrupt on Pin 1.3 (BUTTON)
    CCTL0 = CCIE;                            // Enables interrupts
    CCR0  =  300;                            // Set Frequency
    TACTL = TASSEL_1 + MC_1 + ID_3;          // ACLK selected, Up-Count Enabled, Divider = 8

__enable_interrupt(); //Enables Interrupts

    while (1) //Infinite while loop
    {

    }
}

#pragma vector = TIMER0_A0_VECTOR //Timer Interrupt that is triggered when clock counts up to CCR0 value

    __interrupt void Timer_A ()
    {
        P1OUT ^= BIT0; //Toggle Pin 1.0 and 1.6 (RED and GREEN LEDs)
    }

#pragma vector=PORT1_VECTOR //Port 1 Interrupt that is triggered when Pin 1.3 (BUTTON) changes from high to low

    __interrupt void Port_1(void)
    //when the button is pressed
    {
        if (P1IES & BIT3) //button is pressed
        {
            TACTL = TACLR; // Clears any prexisting value stored in Timer A's register
            TACTL = TASSEL_1 + MC_2 + ID_3;  // Changes clock mode to Continuous mode
            P1IES &= ~BIT3; // Sets Port 1's edge select to 0 (Low - to - High)
        }
        else
        {
            CCR0 = TA0R; //Sets value in CCR0 register to the value in Timer A's register
            TACTL = TASSEL_1 + MC_1 + ID_3;  //back to initial state
            P1IES |= BIT3; //back to initial state
        }

        P1IFG &= ~BIT3; //Resets interrupt flag initially triggered
    }
