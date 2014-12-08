//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "lab7.h"
#include "ir_sensor/ir_sensor.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {



	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	initializeIRSensor();


	while(1) {

		  // Configure P1.4 to be the ADC input

		if(isRightActive() == true)
			RIGHT_LED_ON;
		else
			RIGHT_LED_OFF;

	} // end infinite loop

} // end main





