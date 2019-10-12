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


unsigned char One_Button(unsigned char input_val) {
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

enum Door_States { Door_init, Door_Check, Door_Hash, Door_Lock, Door_Unlock } Door_State;

void Tick_Door(unsigned char temp_val) {			//The only way for the machine to progress is by
	unsigned char button_check = One_Button(temp_val);     //pressing #, else it'll just return to its idle state
	switch(Door_State) {				      // very linear, no storage needed
		case Door_init: 
			Door_State = Door_Check;
			break;
		case Door_Check: //This is basically the idle state
			if ((temp_val & 0x80) == 0x80) {
				Door_State = Door_Lock;
			} 
			else if (button_check == 0x01) { //Now we can move on to checking what button is being pressed
				if (temp_val == 0x04) {
					Door_State = Door_Hash;
				}
				else {
					Door_State = Door_Check;
				}
			}

			break;
		case Door_Lock:
			Door_State = Door_Check;
			break;
		case Door_Unlock:
			Door_State = Door_Check;
		case Door_Hash: 
			if ((temp_val & 0x80) == 0x80) {
				Door_State = Door_Lock;
			} 
			else if (button_check == 0x01) { //Now we can move on to checking what button is being pressed
				if (temp_val == 0x02) {
					Door_State = Door_Unlock;
				}
				else {
					Door_State = Door_Check;
				}
			}

			
			break;

	}

	switch(Door_State) {
		case Door_init: 
			Door_State = Door_Check;
			PORTC = 0x00; //We are somehow in State 0
			break;
		case Door_Check: 
			PORTC = 0x01; //We are in State 1
				     //This should not lock the door
			break;
		case Door_Lock:
			PORTB = 0x00;
			PORTC = 0x02; //We are in State 2
			break;
		case Door_Unlock:
			PORTB = 0x01;
			PORTC = 0x03; //We are in State 3
			break;
		case Door_Hash:
			PORTC = 0x04; //We are in State 4
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
	Door_State = Door_init;

	
    while (1) {
	
		Tick_Door(temp_val);
		temp_val = PINA; 
	}
    return 1;
}
