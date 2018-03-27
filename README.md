# power-enable-circuit [![Build Status](https://api.travis-ci.org/latonita/power-enable-circuit.svg?branch=master)](https://travis-ci.org/latonita/power-enable-circuit)

Attiny13-based micro monitoring circuit which turns on power to load when external signal is high.
Initially it was made on discrete elements, but MCU solution takes less PCB space.
Turns power on instantly until signal is high and holds it on for specified amount of milliseconds before turning off to avoid signal bouncing and dropouts.
```
#define HOLD_PERIOD 1500 // delay in ms
```
## time diagram
![Signal analysis](https://raw.githubusercontent.com/latonita/power-enable-circuit/master/pic/analysis.JPG)

## schematic
![Circuit schematics](https://raw.githubusercontent.com/latonita/power-enable-circuit/master/pic/schematic.jpg)

## memory usage
| Device     | Program (.text + .data + .bootloader) | Data (.data + .bss + .noinit) |
|------------|---------------------------------------|-------------------------------|
| attiny13   |        216 bytes (21.3% Full)         |      4 bytes (6.3% Full)      |
| attiny2313 |        236 bytes (11.5% Full)         |      4 bytes (3.1% Full)      |
