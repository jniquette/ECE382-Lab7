/**
 * 	File: 		ir_sensor.c
 * 	Author:		C2C Justin Niquette
 * 	Date:		8 Dec 14
 * 	Purpose:	This package contains the methods needed to use the ECE382 IR Sensor Boards
 * 				with an MSP430 having an Analog to Digital (ADC) Converter. It is calibrated
 * 				to robot #47.
 */
#include "msp430g2553.h"
#include "ir_sensor.h"

bool lastRightStatus = false;

void initializeIRSensor(){

	P1DIR |= BIT0;	// Set the red (left) LED as output
	P1DIR |= BIT6;	// Set the green (right) LED as output


}

bool isRightActive(unsigned int threshold){
	unsigned short sample[16];									// Just to analyze the values
	unsigned char i = 0;										// index into sample array
	ADC10CTL0 = 0;											// Turn off ADC subsystem
	ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
	ADC10AE0 = BIT4;		 								// Make P1.4 analog input
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

	for(i = 0; i <= 15; i++){
		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		sample[i] = ADC10MEM;									// collect that 10-bit value
	}

	//If last check was true, then we'll allow this check to be a slight threshold lower and still be true
	if(lastRightStatus == true & getRunningAverage(sample) > (threshold-CHANGE_THRESHOLD)){
		return true;
	}

	//Otherwise it must make it to the actual threshold
	if (getRunningAverage(sample) > threshold){
		lastRightStatus = true;
		return true;
	}
	else{
		lastRightStatus = false;
		return false;
	}
}


unsigned int getRunningAverage(unsigned short values[]){
	int size_of_values = sizeof(values) / sizeof(values[0]);
	int sum = 0;
	unsigned int i = 0;
	for(i = 0; i<size_of_values; i++){
		sum += values[i];
	}
	return (sum/size_of_values);
}
