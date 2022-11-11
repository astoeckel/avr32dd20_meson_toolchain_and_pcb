#include <stdbool.h>

#include <avr/io.h>

int main(void) {
    PORTA.DIR = 0b11000000;
    PORTA.OUT ^= 0b10000000;
    while (true) {
        PORTA.OUT ^= 0b11000000;
    }
}
