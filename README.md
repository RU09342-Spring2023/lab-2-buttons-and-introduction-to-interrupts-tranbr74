README:

Author: Brandon Tran

Version: 2/6/2023

Purpose: Create a security system using the MSP430 Board and the infrared sensor

How does it work?

****
Using two inputs and outputs:
Inputs:
	Port 1.3 - Input pin to get a signal from the sensor
	Port 4.1 - Input button to reset state of alarm system

Outputs:
	Port 1.0 - Output Red LED
	Port 6.6 - Output Green LED


**Using three states**

ARMED:
	Green LED blinks on and off every 3 seconds.
	IF the sensor detects motion:
 The ARMED state switches to WARNING state. 
The green LED will stop blinking.

WARNING:
	The Red LED blinks on and off every 1 second.
	A timer is implemented to count up to 10 seconds
	IF:
10 seconds passed and motion is still detected, switch to ALERT state.
10 seconds passed and motion has not been detected, switch to ARMED state and turn off the Red LED.
	Timer will go back to 0.

ALERT:
	Red LED stays on.


****
P4.1 (Button), at any state, will reset the alarm system to ARMED. All LEDS are turned off once the button is pressed.
