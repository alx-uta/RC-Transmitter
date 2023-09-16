/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "rx.hpp"

int Rx::getAnoRotaryEncoderPosition(
    uint8_t high, uint8_t mid_high, uint8_t mid_low, uint8_t low
) {
    // Check if any of the input bytes are outside the valid range (0-255)
    if (high > 255 || mid_high > 255 || mid_low > 255 || low > 255) {
        return 0; // Data is corrupted, return 0
    }
    
    // Reconstruct the int value from the stored bytes
    return  (high << 24) | (mid_high << 16) | (mid_low << 8) | low;
}

void Rx::decodeByteToSwitchStatuses(uint16_t encodedByte, bool switchStatuses[], int numSwitches) {
  for (int i = 0; i < numSwitches; i++) {
    switchStatuses[i] = (encodedByte >> i) & 0x01;
  }
}

uint16_t Rx::combineBytes(uint8_t byte1, uint8_t byte2) {
  return ((uint16_t)byte2 << 8) | byte1;
}

float Rx::valRound(float val) {
  return round(val * 100.0) / 100.0;
}