# power-enable-circuit

Attiny13-based micro monitoring circuit which turns on power to load when external signal is high.
Initially it was made on discrete elements, but MCU solution takes less PCB space.
Turns power on instantly until signal is high and holds it on for specified amount of milliseconds before turning off to avoid signal bouncing and dropouts.
```
#define HOLD_PERIOD 1500 // delay in ms
```
Program: 270 bytes; Data: 12 bytes

![Signal analysis](https://raw.githubusercontent.com/latonita/power-enable-circuit/master/pic/analysis.JPG)

![Circuit schematics](https://raw.githubusercontent.com/latonita/power-enable-circuit/master/pic/schematic.jpg)
