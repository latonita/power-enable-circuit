#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

// Config
#define PWR_ON_PIN PB0
#define ENA_IN_PIN PB1
#define HOLD_PERIOD 1500 // ms
// HOLD_PERIOD - time to hold load in ON state. to avoid ENABLE signal bounce
// and dropouts (I need 1500 ms for this)

// Utilities
#define nop() __asm__ __volatile__("nop")

#ifdef _AVR_ATTINY13 // from platformio.ini
#define _WDT_INT_ENA_BIT WDTIE
#define _WDT_VECTOR WDT_vect
#endif

#ifdef _AVR_ATTINY2313 // from platformio.ini
#define _WDT_INT_ENA_BIT WDIE
#define _WDT_VECTOR WDT_OVERFLOW_vect
#endif

volatile uint32_t wdt_isr_counter = 0;
ISR(_WDT_VECTOR) { wdt_isr_counter++; }

int main(void) {
  /////////////////////////////////////////////////////////////////////////////
  //  init millis
  /////////////////////////////////////////////////////////////////////////////
  wdt_reset();
  // Start timed sequence
  _WD_CONTROL_REG |= (1 << WDCE) | (1 << WDE);
  // Set new prescaler(time-out) value = 2K (2048) cycles (16ms)
  _WD_CONTROL_REG = _BV(_WDT_INT_ENA_BIT);
  sei();

  /////////////////////////////////////////////////////////////////////////////
  //  init port
  /////////////////////////////////////////////////////////////////////////////
  // all pins out, excluding ENA_IN_PIN
  DDRB = 0xFF & ~(1 << ENA_IN_PIN);
  // all pins up, including PWR_ON_PIN - its low when active;
  //              excluding ENA_IN_PIN - its in tri state
  PORTB = 0xFF & ~(1 << ENA_IN_PIN);
  nop();

  /////////////////////////////////////////////////////////////////////////////
  //  main loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;) {
    if (PINB & (1 << ENA_IN_PIN)) {
      wdt_isr_counter = 0; // reset counter, we've got high enable signal
      PORTB &= ~(1 << PWR_ON_PIN); // active low, turn on high-side mosfet
    } else if (wdt_isr_counter << 4 > HOLD_PERIOD) {
      // no high signal for more than HOLD_PERIOD
      PORTB |= (1 << PWR_ON_PIN); // turn off mosfet
    }
    nop();
  }
}
