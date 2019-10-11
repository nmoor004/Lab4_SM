/*	Author: nmoor004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 4  Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum Inc_States { Inc_init, Inc_Idle, Inc_Add, Inc_Subtract, Inc_Reset} Inc_State;

void Tick_Inc(unsigned char temp_val) {

	unsigned char sum = PORTB; 
	unsigned char A0 = temp_val & 0x01;  // Get 0th bit
	unsigned char A1 = (temp_val & 0x02) >> 1; // Get 1st bit and right shift
	switch(Inc_State) {     //Transitions
		case Inc_init: 
			Inc_State = Inc_Idle;
			break;
		
		case Inc_Idle:
			if ((A0 == 0x01) && (A1 == 0x01)) {
				Inc_State = Inc_Reset;
			}
			else if ((A0 == 0x01) && (A1 == 0x00)) {
				Inc_State = Inc_Add;
			}
			else if ((A0 == 0x00) && (A1 == 0x01)) {
				Inc_State = Inc_Subtract;
			}
			break; 

		case Inc_Add: //Uses an Increment function from above to keep code clean
			Inc_State = Inc_Idle;
			break;

		case Inc_Subtract:
			Inc_State = Inc_Idle;
			break;
		case Inc_Reset:
			Inc_State = Inc_Idle;

	}

	switch(Inc_State) {
		case Inc_init:
			break;
		case Inc_Idle:
			break;
		case Inc_Add:
			if (PORTB != 0x09) {
				sum++;
				PORTB = sum;
			}
			break;
		case Inc_Subtract:
			if (PORTB != 0x00) {
				sum--;
				PORTB = sum;
			}
			break;
		case Inc_Reset:
			PORTB = 0x00;
			break;

	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;  //input
	DDRB = 0xFF; PORTB = 0x00; //output
    /* Insert your solution below */
	Inc_State = Inc_init;
	unsigned char temp_val = PINA;
	PORTB = 0x07;

    while (1) {
	
		Tick_Inc(temp_val);
		temp_val = PINA; 
	}
    return 1;
}
