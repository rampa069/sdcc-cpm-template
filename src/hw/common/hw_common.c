#include "hw_common.h"

#define VECTOR_ADDRESS_START 0x7F

void empty_ISR(void);

void hw_outp(uint8_t port, uint8_t data) __naked {
	port; data;

	__asm
		ld hl, #3
		add hl, sp
		ld a, (hl) // Load data from stack

		ld hl, #2
		add hl, sp

		push bc
		
		ld c, (hl) // Load port from stack
		out (c), a // Output to port

		pop bc

		ret
	__endasm;
}

uint8_t hw_inp(uint8_t port) __naked {
	port;

	__asm
		ld hl, #2
		add hl, sp

		push bc

		ld c, (hl)
		in l,(c)

		pop bc

		ret
	__endasm;
}

void hw_smallDelay(uint8_t delay) {
	while(delay--) {
		__asm
			nop
		__endasm;
	}
}

void hw_setupInterrupts(void) {
	uint16_t *vec_table = (uint16_t*)((uint16_t)(((uint16_t)VECTOR_ADDRESS_START) << 8));
	uint8_t idx = 0;

	__asm
		di	// Disable interrupts

		push af

		ld a,#VECTOR_ADDRESS_START // Load the address
		ld I,a

		pop af
	__endasm;

	// Fill the table with "empty" handlers...
	for(idx = 0; idx < 128; idx++) vec_table[idx] = (uint16_t)empty_ISR;
}

void hw_enableInterrupts(void) {
	__asm
		im 2 // Enable interrupt mode 2
		ei	// Enable interrupts
	__endasm;
}

void hw_addInterruptHandler(uint8_t handNo, uint16_t addr) {
	uint16_t *vec_table = (uint16_t*)(((uint16_t)(((uint16_t)VECTOR_ADDRESS_START) << 8)) & 0xFF00);

	vec_table[handNo >> 1] = addr;
}

void empty_ISR(void) __naked {
	__asm
		halt
	__endasm;
}

