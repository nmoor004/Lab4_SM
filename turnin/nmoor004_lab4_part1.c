/*	Author: nmoor004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 4  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LED_States { LED_Start, LED_init, LED_0, LED_1 } LED_State;

void Tick_LED(unsigned char temp_val) {
	
	switch(LED_State) { //Transitional cases
		case LED_Start:
			LED_State = LED_init;
			break;
		
		case LED_init: //Initialize LED lights
			LED_State = LED_0;
			break;
		
		case LED_0:
			if (temp_val == 0x01) {
				LED_State = LED_1;
			}
			else {
				LED_State = LED_0;
			}
			break;

		case LED_1:
			if (temp_val == 0x01) {
				LED_State = LED_0;
			}
			else {
				LED_State = LED_1;
			}
			break;

	}

	switch(LED_State) { //State actions
		case LED_0: 
			PORTB = ((PORTB | 0x01) & 0x01);
			temp_val = 0x00;
			break;

		case LED_1:
			PORTB = ((PORTB | 0x02) & 0x02);
			temp_val = 0x00;
			break;
		

		case LED_init:
			PORTB = 0x01;
			break;

		default:
			break;
	}


}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;  //input
	DDRB = 0xFF; PORTB = 0x00; //output
    /* Insert your solution below */
	LED_State = LED_Start;
	unsigned char temp_val = PINA;
    while (1) {
	
		Tick_LED(temp_val);
		temp_val = PINA;    
	}
    return 1;
}
