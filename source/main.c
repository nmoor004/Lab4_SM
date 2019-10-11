/*	Author: nmoor004
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab # 4  Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

}



unsigned char button_check(unsigned char input_val) {
	int counter = 0;
	while (input_val != 0x00) {
		if ((input_val & 0x01) == 0x01) {
			counter++;
		}
		input_val >>= 1;
	}

	if (counter > 1) {
		return 0x00;
	}
	else {
		return 0x01;
	}
}

enum Door_States { Door_init, Door_Check, Door_Hash, Door_Y, Door_Lock, Door_Unlock, Door_Reset } Door_State;

void Tick_Door(unsigned char temp_val) {
	unsigned char button_check = One_Button(temp_val);
	switch(Door_State) {
		case Door_init: 
			Door_State = Door_Check;
			break;
		case Door_Check:
			if ((temp_val & 0x80) == 0x80) {
				Door_State = Door_Lock;
			} 

			}
			else if (button_check == 0x01) { //Now we can move on to checking what button is being pressed
				if (temp_val == 0x02) {
					Door_State = Door_Hash;
				}
				else if (temp_val == 0x04) {
					Door_State = Door_Y;
				}
				else {
					Door_State = Door_Reset;
			}

			break;
		case Door_Lock:
			Door_State = Door_Check;
			break;
		case Door_Unlock:
			Door_State = Door_Check;
		case Door_#: 
			if ((temp_val &
			Door_State = Door_Check;
			break;

			break;
		case Door_Reset:
			Door_State = Door_Check;
	}

	switch(Door_State) {
		case Door_init: 
			Door_State = Door_Check;
			break;
		case Door_Check: 
			PORTC = 0x01;

			break;
		case Door_Lock:
			PORTB = 0x00;
			PORTC = 0x02;
			break;
		case Door_Unlock:
			PORTB = 0x01;
			PORTC = 0x03;
			break;
		case Door_Y:
			break;
		case Door_Hash:
			break;
		case Door_Reset:
			break;

	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;   //input
	DDRB = 0xFF; PORTB = 0x00;  //output
	DDRC = 0xFF; PORTC = 0x00; //output
    /* Insert your solution below */
	unsigned temp_val = PINA; 

	
    while (1) {
	
		Tick_Door(temp_val);
		temp_val = PINA; 
	}
    return 1;
}
