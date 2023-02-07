/*
 * GPIO_Driver.c
 *
 *  Created on: Jan 6, 2023
 *      Author: (Updated by) Brandon Tran
 *      Version: 1/29/2023
 */



#include "GPIO_Driver.h"
#include <msp430.h>


//*********  Used to configure a single GPIO pin as an input or output.************
void gpioInit(char Port, char Pin, char Direction){
    /*
     * char Port: takes values from 1-6
     * char Pin: takes values from 0-7
     * char Direction: 0 for Input, 1 for Output
      */

 char TargetPin = BIT0 << Pin;    // Make out target pin value


    if(Direction){
        //*******switch statement is used to assign a port (1 - 6) as an output since DIRECTION = 1*******

        //******* BITWISE OR operator means to SET ***********

        switch(Port){

            case 1:
                P1DIR |= TargetPin; //Port 1 Direction SETS Pin Number
                break;
            case 2:
                P2DIR |= TargetPin; //Port 2 Direction SETS Pin Number
                break;
            case 3:
                P3DIR |= TargetPin; //Port 3 Direction SETS Pin Number
                break;
            case 4:
                P4DIR |= TargetPin; //Port 4 Direction SETS Pin Number
                break;
            case 5:
                P5DIR |= TargetPin; //Port 5 Direction SETS Pin Number
                break;
            case 6:
                P6DIR |= TargetPin; //Port 6 Direction SETS Pin Number
                break;
        }
    }
    else{
        //*******switch statement is used to assign a port (1 - 6) as an input since DIRECTION = 0 ************
        switch(Port){

            // ***** BITWISE AND is used to CLEAR ********
            case 1:
                P1DIR &= ~TargetPin; //Port 1 Direction CLEARS Pin Number
                P1REN |= TargetPin;  //Port 1 Resistor enable SETS Pin Number
                P1OUT |= TargetPin;  //Port 1 Output SETS Pin Number
                break;               // **********The following is similar to the other cases below.*********
            case 2:
                P2DIR &= ~TargetPin;
                P2REN |= TargetPin;
                P2OUT |= TargetPin;
                break;
            case 3:
                P3DIR &= ~TargetPin;
                P3REN |= TargetPin;
                P3OUT |= TargetPin;
                break;
            case 4:
                P4DIR &= ~TargetPin;
                P4REN |= TargetPin;
                P4OUT |= TargetPin;
                break;
            case 5:
                P5DIR &= ~TargetPin;
                P5REN |= TargetPin;
                P5OUT |= TargetPin;
                break;
            case 6:
                P6DIR &= ~TargetPin;
                P6REN |= TargetPin;
                P6OUT |= TargetPin;
                break;
            }
        }
    }


// *******Used to write a 1 or 0 to a Pin which has already been declared as an output.******
void gpioWrite(char Port, char Pin, char Value){
    /*
    * char Port: takes values from 1-6
    * char Pin: takes values from 0-7
    * char Value: 0 or 1


     */
 char TargetPin = BIT0 << Pin;    // Make out target pin value

        //When Value is set as 1, Port Output is SETs a pin number
        if(Value){
            //switch statement to assign pin via PxOUT
            switch(Port){

                case 1:
                    P1OUT |= TargetPin;
                    break;
                case 2:
                    P2OUT |= TargetPin;
                    break;
                case 3:
                    P3OUT |= TargetPin;
                    break;
                case 4:
                    P4OUT |= TargetPin;
                    break;
                case 5:
                    P5OUT |= TargetPin;
                    break;
                case 6:
                    P6OUT |= TargetPin;
                    break;
            }
        }
        else{
            //switch statement is used to clear pin via PxOUT
            switch(Port){

                case 1:
                    P1OUT &= ~TargetPin;
                    break;
                case 2:
                    P2OUT &= ~TargetPin;
                    break;
                case 3:
                    P3OUT &= ~TargetPin;
                    break;
                case 4:
                    P4OUT &= ~TargetPin;
                    break;
                case 5:
                    P5OUT &= ~TargetPin;
                    break;
                case 6:
                    P6OUT &= ~TargetPin;
                    break;
            }
        }
}


/**
 * gpioRead(char Port, char Pin, char Value)
 * Used to Read from a pin which has been declared as an input.
 * Returns a 1 or 0 based on pin value.
 *
 * char Port: takes values from 1-6
 * char Pin: takes values from 0-7
 *
 * Example: Reading Pin 1.1
 * unsigned char PinState = gpioRead(1, 1);
 */
// ******Used to Read from a pin which has been declared as an input. Returns a 1 or 0 based on pin value.********
char gpioRead(char Port, char Pin){

   /*
    * char Port: takes values from 1-6
    * char Pin: takes values from 0-7
     */

 char TargetPin = BIT0 << Pin;    // Make out target pin value

    //temp variable to hold the returned value
    char Value;

    //switch statement to determine the port and assign value with either 1 or 0 based on whether the bit is on or off
    switch(Port){
        case 1:
            Value = P1IN & TargetPin;
            break;
        case 2:
            Value = P2IN & TargetPin;
            break;
        case 3:
            Value = P3IN & TargetPin;
            break;
        case 4:
            Value = P4IN & TargetPin;
            break;
        case 5:
            Value = P5IN & TargetPin;
            break;
        case 6:
            Value = P6IN & TargetPin;
            break;
    }
    return Value;
}
