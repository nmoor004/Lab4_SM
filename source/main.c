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

unsigned char Incrementer(unsigned char input_val, int op_type) {
	
	if ((input_val == 0x00) || (input_val == 0x09)) { // The program stops at 0x00 and 0x09. This
		return sum; 				 //checks for those values.
	}	

	unsigned char one = 0x01;
	unsigned char temp_value = input_val;
	if (op_type == 0) { // Add

		}
	}
	else if (op_type == 1) { // Subtract

	}


return sum;
}



enum Inc_States { Inc_Start, Inc_init, Inc_Idle, Inc_Add, Inc_Subtract, Inc_Reset} Inc_State;

void Tick_Inc(unsigned char temp_val) {

	unsigned char sum = PORTB; 
	unsigned char A0 = temp_val & 0x01;  // Get 0th bit
	unsigned char A1 = (temp_val & 0x02) >> 1; // Get 1st bit
	switch(Inc_State) {     //Transitions 
		case Inc_Start: // Machine Start Transition
			Inc_State = Inc_init;
			
			break;

		case Inc_init: 
			Inc_State = Inc_Idle;
			break;
		
		case Inc_Idle:
			if ((A0) && (A1)) {
				Inc_State = Inc_Reset;
			}
			else if ((A0) && (!A1)) {
				Inc_State = Inc_Add;
			}
			else if ((!A0) && (A1)) {
				Inc_State = Inc_Subtract;
			}
			break; 

		case Inc_Add: //Uses an Increment function from above to keep code clean
			PORTB = Incrementer(sum, 0);
			Inc_State = Inc_Idle;
			break;

		case Inc_Subtract:
			PORTB = Incrementer(sum, 1);
			Inc_State = Inc_Idle;
			break;
		case Inc_Reset:
			PORTB = 0x00;
			Inc_State = Inc_Idle;

	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;  //input
	DDRB = 0xFF; PORTB = 0x00; //output
    /* Insert your solution below */
	Inc_State = Inc_Start;
	unsigned char temp_val = PINA;
	PORTB = 0x07;

    while (1) {
	
		Tick_Inc(temp_val);
		temp_val = PINA; 
	}
    return 1;
}
