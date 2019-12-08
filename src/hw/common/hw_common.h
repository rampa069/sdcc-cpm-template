#ifndef _HWLIB_COMMON_HEADER_
#define _HWLIB_COMMON_HEADER_

#include "common_datatypes.h"

void hw_outp(uint8_t port, uint8_t data);
uint8_t hw_inp(uint8_t port) __naked;

void hw_smallDelay(uint8_t delay);

void hw_setupInterrupts(void);
void hw_addInterruptHandler(uint8_t handNo, uint16_t addr);
void hw_enableInterrupts(void);

#endif /* _HWLIB_COMMON_HEADER_ */
