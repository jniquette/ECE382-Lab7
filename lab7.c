//-----------------------------------------------------------------
// Name:	Coulston
// File:	lab7.c
// Date:	Fall 2014
// Purp:	Collect analog samples from P1.3 and P1.4
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "lab7.h"
#include "ir_sensor/ir_sensor.h"
#include "movements.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {


	initMotors();


	P1DIR |= BIT0;	// Set the red (left) LED as output
	P1DIR |= BIT6;	// Set the green (right) LED as output

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;


	while(1) {


		doMazeMovements();

		if(isFrontActive(512) == true){
			LEFT_LED_ON;
			RIGHT_LED_ON;
		}
		else{
			RIGHT_LED_OFF;
			LEFT_LED_OFF;
		}

		//Max value = 1023(dec)
		if(isRightActive(512) == true)
			RIGHT_LED_ON;
		else
			RIGHT_LED_OFF;


		if(isLeftActive(512) == true)
			LEFT_LED_ON;
		else
			LEFT_LED_OFF;


	} // end infinite loop

} // end main

void doMazeMovements(){
	goForward();

	while(isFrontActive(700) == false);
	stop();
	while(isFrontActive(700) == true);

}



