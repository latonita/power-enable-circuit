#include "millis.h"

volatile uint32_t wdt_isr_counter = 0;

ISR(WDT_vect) {
  wdt_isr_counter++;
}

uint32_t millis() {
  return wdt_isr_counter * 16;
}

void millis_init() {
  cli();
  wdt_reset();
  WDTCR = _BV(WDTIE); // 16 ms prescaler
  sei();
}
