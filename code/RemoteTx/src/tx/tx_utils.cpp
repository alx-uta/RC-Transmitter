/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "tx.hpp"

int Tx::applyJoystickThreshold(int value, int middle, int driftValue, int mappedValue) {
    return (value > middle + driftValue || value < middle - driftValue) ? mappedValue : _config.joystick_default_value;
}

int Tx::joystickMap(
  int current_value,
  int min_value,
  int max_value,
  int middle_value,
  int default_value,
  int out_min,
  int out_max
) {
  if (current_value < middle_value) {
    int clamped_value = current_value < min_value ? min_value : current_value;
    int output = map(clamped_value, min_value, middle_value, out_min, default_value);
    return (output < out_min) ? out_min : output;
  } else {
    int clamped_value = current_value > max_value ? max_value : current_value;
    int output = map(clamped_value, middle_value, max_value, default_value, out_max);
    return (output > out_max) ? out_max : output;
  }
}

uint16_t Tx::encodeSwitchStatusesToByte(bool switchStatuses[], int numSwitches) {
    uint16_t encodedByte = 0;

    for (int i = 0; i < numSwitches; i++) {
        encodedByte |= (switchStatuses[i] << i);
    }

    return encodedByte;
}

void Tx::decodeByteToSwitchStatuses(uint16_t encodedByte, bool switchStatuses[], int numSwitches) {
  for (int i = 0; i < numSwitches; i++) {
    switchStatuses[i] = (encodedByte >> i) & 0x01;
  }
}
