/*
 *  Button Interrupt Example
 *
 *  Created on: Jan 30, 2023
 *      Author: Brandon Tran
 *      Version: 2.0
 *
 *      This example will show you how to configure an Interrupt and Interrupt Service Routine.
 *
 *      Your task for this lab is to change which LED each time the button has been pressed.
 *      For example, this starts blinking the Red LED, and then when the button is pressed,
 *      it should move to the Green LED. If the button is pressed again, it should move to the Red LED again.
 *
 *      There have been some "todo" notes which can be helpful in finding things to change in the code.
 */

#include <msp430.h>

char ToggleEnable = 0x01;                       // Global Variable to track if the LED should be on or off
char RedGreen = 0;                              // Global Variable to specify RED or GREEN is on or off (0 equals Red and 1 equals Green)
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    // Configure GPIO
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
    P1DIR |= BIT0;                          // Set P1.0 to output direction
    P6OUT &= ~BIT6;                         //Clear P6.6 output latch for a defined power-on state
    P6DIR |= BIT6;                         //Set P6.6 to output direction



    P2OUT |= BIT3;                          // Configure P2.3 as pulled-up
    P2REN |= BIT3;                          // P2.3 pull-up register enable
    P2IES &= ~BIT3;                         // P2.3 Low --> High edge
    P2IE |= BIT3;                           // P2.3 interrupt enabled

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    P2IFG &= ~BIT3;                         // P2.3 IFG cleared

    __bis_SR_register(GIE);                 // Enter LPM3 w/interrupt

    while(1)
    {
        // @TODO You will need to modify this code to change between blinking the Red LED or the Green LED

        if (ToggleEnable && RedGreen){ //If Toggle and RedGreen is 1
            P1OUT ^= BIT0;                  // P1.0 = toggle
        }
        else if (ToggleEnable && (~RedGreen)){ //If Toggle is 1 and RedGreen is 0
            P6OUT ^= BIT6;                  // P6.6 = toggle
        }
        else {
            P1OUT &= ~BIT0;                // Set P1.0 to 0
            P6OUT &= ~BIT6;                // Set P6.6 to 0
        }
        __delay_cycles(100000);

    }
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    // @TODO You might need to modify this based on your approach to the lab
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    ToggleEnable ^= 0x01;                   // Enable if the toggle should be active
    if(ToggleEnable)
    RedGreen ^= 0x01;                       // Enable if P1.0 or P6.6 should be active
}



