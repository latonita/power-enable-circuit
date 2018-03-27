
#include <Arduino.h>
#include <pins_arduino.h>

#define __no_operation() {__asm__ __volatile__("nop");}

#define PWR_ON_PIN PB0 // PB0
#define ENA_IN_PIN PB1 // PB1

#define HOLD_PERIOD 500
// depends on real board and fuses. set up via experiment
// on attiny2313 i used for test 1 = 8ms, so 200=1.6s
// didnt test it on attiny13 yet

unsigned long now = 0;
unsigned long last_on = 0;

void setup() {
  DDRB = 0xFF & ~(1 << ENA_IN_PIN); // all pins out, excluding ENA_IN_PIN
  PORTB = 0xFF & ~(1 << ENA_IN_PIN); // all pins up, including PWR_ON_PIN, excluding ENA_IN_PIN - its in tri state
  __no_operation(); // sync
}

void loop() {
  now = millis();
  if (PINB & (1 << ENA_IN_PIN)) {
    last_on = now;
    PORTB &= ~(1 << PWR_ON_PIN); // active low
  } else if (now >= last_on + HOLD_PERIOD) {
    last_on = 0;
    PORTB |= (1 << PWR_ON_PIN);
  }
  __no_operation(); //sync
}
