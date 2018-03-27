
#include <Arduino.h>
#include <pins_arduino.h>

#define PWR_ON_PIN PB0 // PB0
#define ENA_IN_PIN PB1 // PB1

#define HOLD_PERIOD 500
// depends on real board and fuses. set up via experiment
// on attiny2313 i used for test 1 = 8ms, so 200=1.6s
// didnt test it on attiny13 yet

unsigned long now = 0;
unsigned long last_on = 0;
unsigned char state = 0;
unsigned char ena_in = 0;

void setup() {
  //TODO: make vice versa - all unused pins shall be INPUT, pulled down! 
  PORTB = (1 << PWR_ON_PIN);
  DDRB = 0xFF & ~(1 << ENA_IN_PIN);
}

void loop() {
  now = millis();
  ena_in = PINB & (1 << ENA_IN_PIN);

  if (ena_in) {
    last_on = now;
    state = ena_in;
    PORTB &= ~(1 << PWR_ON_PIN); // active low
  } else if (now >= last_on + HOLD_PERIOD) {
    last_on = 0;
    state = 0;
    PORTB |= (1 << PWR_ON_PIN);
  }
  __asm__ __volatile__("nop");
}
