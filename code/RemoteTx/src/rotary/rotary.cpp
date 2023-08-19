/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "rotary.hpp"

// Use the half-step state table (emits a code at 00 and 11)
const unsigned char ttable[6][4] = {
    // R_START (00)
    {0x0, 0x1, 0x2, 0x3},
    // 0x1
    {0x0, 0x1, 0x0, 0x3 | 0x20},
    // 0x2
    {0x0, 0x0, 0x2, 0x3 | 0x10},
    // 0x3 (11)
    {0x0, 0x4, 0x5, 0x3},
    // 0x4
    {0x0 | 0x10, 0x4, 0x3, 0x3},
    // 0x5
    {0x0 | 0x20, 0x3, 0x5, 0x3},
};

unsigned char Rotary::process(int pin1, int pin2) {
    // Grab state of input pins.
    unsigned char pinstate = (pin2 << 1) | pin1;
    // Determine new state from the pins and state table.
    state = ttable[state & 0xf][pinstate];
    // Return emit bits, ie the generated event.
    return state & 0x30;
}

int Rotary::encoderDirection(int pin1, int pin2) {
    unsigned char direction = Rotary::process(
        pin1, pin2
    );
    return (
        direction == 0x0 ? 0 : (direction == 0x10) ? -1 : 1
    );
}