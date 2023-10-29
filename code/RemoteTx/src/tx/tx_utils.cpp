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

uint16_t Tx::combineBytes(uint8_t byte1, uint8_t byte2) {
  return ((uint16_t)byte2 << 8) | byte1;
}

void Tx::increasePayloadSize(uint8_t bytes) {
    this->payload_size += bytes;
}

uint16_t Tx::encodeStatusToByte(bool statuses[], int num) {
    uint16_t encodedByte = 0;

    for (int i = 0; i < num; i++) {
        encodedByte |= (statuses[i] << i);
    }

    return encodedByte;
}

void Tx::decodeByteToStatus(uint16_t encodedByte, bool statuses[], int num) {
  for (int i = 0; i < num; i++) {
    statuses[i] = (encodedByte >> i) & 0x01;
  }
}
