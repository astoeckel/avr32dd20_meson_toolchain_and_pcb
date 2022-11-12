#include <stdbool.h>

#include <avr/io.h>

int main(void) {
    /* This program repeatedly toggles pins PA6 and PA7 with a 180° phase-shift */
    PORTA.DIR = 0b11000000;
    PORTA.OUT = 0b10000000;
    while (true) {
        PORTA.OUT ^= 0b11000000;
    }
}
