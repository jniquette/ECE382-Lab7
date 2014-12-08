//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "ir_sensor/ir_sensor.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	unsigned short sample[16];									// Just to analyze the values
	unsigned char i = 0;										// index into sample array

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	initializeIRSensor();


	while(1) {

		  // Configure P1.4 to be the ADC input
		ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
		ADC10AE0 = BIT4;		 								// Make P1.4 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

		ADC10CTL0 |= ADC10SC;									// Start a conversion
		while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
		sample[i] = ADC10MEM;									// collect that 10-bit value
		unsigned short average_three_sample = (sample[i] + sample[(i+15)%16] + sample[(i+14)%16])/3;
		if (average_three_sample > 0x0200)	RIGHT_LED_ON;
		else					RIGHT_LED_OFF;

		i = (i+1) & 0xF;							// This is a mod 16 increment
	} // end infinite loop

} // end main

