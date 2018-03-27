#ifndef _MILLIS_H_
#define _MILLIS_H_

#include <avr/interrupt.h>
#include <avr/wdt.h>

uint32_t millis();
void millis_init();

#endif // _MILLIS_H_
