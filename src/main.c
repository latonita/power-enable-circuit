#include <avr/io.h>
#include "millis.h"

#define nop() {__asm__ __volatile__("nop");}

#define PWR_ON_PIN PB0
#define ENA_IN_PIN PB1

#define HOLD_PERIOD 1500 // ms - to hold load in ON state. to avoid ENABLE signal bounce and dropouts (I need 1500 ms for this)

uint32_t now = 0;
uint32_t last_on = 0;

int main(void) {
  millis_init();

  DDRB = 0xFF & ~(1 << ENA_IN_PIN);  // all pins out, excluding ENA_IN_PIN
  PORTB = 0xFF & ~(1 << ENA_IN_PIN); // all pins up, including PWR_ON_PIN - its low when active;
                                     //              excluding ENA_IN_PIN - its in tri state
  nop();

  while(1) {
    now = millis();
    if (PINB & (1 << ENA_IN_PIN)) {
      last_on = now;
      PORTB &= ~(1 << PWR_ON_PIN); // active low
    } else if (now >= last_on + HOLD_PERIOD) {
      last_on = 0;
      PORTB |= (1 << PWR_ON_PIN);
    }
    nop();
  }
}
