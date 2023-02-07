
/*
 * OccupancyDetector.c
 *
 *  Created on: Feb 1, 2023
 *      Author: Brandon Tran
 *      References: Ben Harrison for utilizing how to use GPIO_Driver to make coding easier
 *      Modified on: 2/6/2023
*/

#include <msp430.h>

#include "GPIO_Driver.h"
 //Technique referenced and learned from Ben Harrison to make code easier to understand for me


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               //stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                   // to activate previously configured port settings


    //initialize states for switch statements (referenced from original readme)
    #define ARMED_STATE 0
    #define WARNING_STATE 1
    #define ALERT_STATE 2

    //initialize inputs
    gpioInit(1, 3, 0);          //set pin 1.3 as an input
    gpioInit(4, 1, 0);          //set button 4.1 as input

    //initialize outputs
    gpioInit(1, 0, 1);          //set P1.0 as output
    gpioInit(6, 6, 1);          //set P6.6 as output

    //Set outputs to 0
    gpioWrite(1, 0, 0);         // Clear Pin 1.0 as 0 initially
    gpioWrite(6, 6, 0);         // Clear Pin 6.6 as 0 initially


    char state = ARMED_STATE;   //char to hold the state of the security system.

    char LED_Blink = 0x00;       //char to hold state off the LED as on or off

    char timer = 0;           //char to count the seconds in warning state before moving to alert state


    while(1)
    {
      //char to see if there is movement detected on P1.3 (hooked up to sensor)
      char motion_detect = gpioRead(1, 3);
      LED_Blink ^= 0x01;           // Toggle LED State between on and off to make LED blink (referenced from Ben Harrison)


      switch (state) {

          //State is ARMED. Green light is blinking for every 3 seconds.
          case ARMED_STATE:

              //if no motion detected, blink green
              if(!motion_detect){
                  //P6.6 is set to blink for 3 sec
                  gpioWrite(6, 6, LED_Blink);
              }
              //if motion is detected, move to warning state and turn off green LED
              else{
                  //P6.6 is cleared
                  gpioWrite(6, 6, 0);

                  //set state to warning
                  state = WARNING_STATE;
              }

              //1.5s delay, 3 sec total for green light to blink on and off
              __delay_cycles(1500000);
              break;

        //if person detected, move to WARNING_STATE
        case WARNING_STATE:

            gpioWrite(1, 0, LED_Blink); //RED led is set to BLINK for 1 sec.
            //P1OUT ^= BIT0;

            //check if motion is still detected within 20 half seconds (10 seconds), change to ALERT state
            if(motion_detect && timer == 20){

                //set the state to alert
                state = ALERT_STATE;

                //reset timer
                timer = 0;
            }

            //if no movement detected and timer has reached 10 seconds (20 half seconds)
            else if(!motion_detect && timer == 20){

                //set the state to armed
                state = ARMED_STATE;

                //reset timer
                timer = 0;
            }

            //add 1 half second to the timer
            timer++;

            //0.5s delay, 1 sec total to toggle RED LED
            __delay_cycles(500000);
            break;

        //case where alert state is on
        case ALERT_STATE:
            //set RED LED on until disarmed
            gpioWrite(1, 0, 1);

            break;
      }


      //If button pressed, disarm system back to ARM_STATE
                  if(!gpioRead(4, 1)){

                      //reset the state
                      state = ARMED_STATE;

                      //turn off LEDs
                      gpioWrite(1, 0, 0); // P1.0 is cleared
                      gpioWrite(6, 6, 0); // P6.6 is cleared

                      //Loops infinite amount of times
                      while(!gpioRead(4, 1));
      }
  }
}

