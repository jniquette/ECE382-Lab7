/**
 * 	File: 		ir_sensor.c
 * 	Author:		C2C Justin Niquette
 * 	Date:		8 Dec 14
 * 	Purpose:	This package contains the methods needed to use the ECE382 IR Sensor Boards
 * 				with an MSP430 having an Analog to Digital (ADC) Converter. It is calibrated
 * 				to robot #47.
 */
#include "msp430g2553.h"

void initializeIRSensor(){

	P1DIR |= BIT0;	// Set the red (left) LED as output
	P1DIR |= BIT6;	// Set the green (right) LED as output


}
