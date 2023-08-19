/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "tx.hpp"

void Tx::defaultValues() {
    // Joystick - Left
    this->_payload.structure.j1x = joystick_default_value; // left-right
    this->_payload.structure.j1y = joystick_default_value; // up-down

    // Joystick - Right
    this->_payload.structure.j2x = joystick_default_value; // left-right
    this->_payload.structure.j2y = joystick_default_value; // up-down

    // Potentiometers
    this->_payload.structure.p1 = 0;
    this->_payload.structure.p2 = 0;
    this->_payload.structure.p3 = 0;
    this->_payload.structure.p4 = 0;
    this->_payload.structure.p5 = 0;
    this->_payload.structure.p6 = 0;

    // Potentiometers - Switches
    this->_payload.structure.p1s = 0;
    this->_payload.structure.p2s = 0;
    this->_payload.structure.p3s = 0;
    this->_payload.structure.p4s = 0;
    this->_payload.structure.p5s = 0;
    this->_payload.structure.p6s = 0;

    // Switches
    this->_payload.structure.s1 = 0;
    this->_payload.structure.s2 = 0;
    this->_payload.structure.s3 = 0;
    this->_payload.structure.s4 = 0;
    this->_payload.structure.s5 = 0;

    // Ano Rotary Encoder - Left
    this->_payload.structure.re1_up = 0;
    this->_payload.structure.re1_down = 0;
    this->_payload.structure.re1_left = 0;
    this->_payload.structure.re1_right = 0;
    this->_payload.structure.re1_center = 0;

    this->_payload.structure.re1_pos_low = 0;
    this->_payload.structure.re1_pos_mid_low = 0;
    this->_payload.structure.re1_pos_mid_high = 0;
    this->_payload.structure.re1_pos_high = 0;

    // Ano Rotary Encoder - Right
    this->_payload.structure.re2_up = 0;
    this->_payload.structure.re2_down = 0;
    this->_payload.structure.re2_left = 0;
    this->_payload.structure.re2_right = 0;
    this->_payload.structure.re2_center = 0;

    this->_payload.structure.re2_pos_low = 0;
    this->_payload.structure.re2_pos_mid_low = 0;
    this->_payload.structure.re2_pos_mid_high = 0;
    this->_payload.structure.re2_pos_high = 0;
}


void Tx::setLeftJoystick(uint8_t x, uint8_t y) {
    this->_payload.structure.j1x = x;
    this->_payload.structure.j1y = y;
}

void Tx::setRightJoystick(uint8_t x, uint8_t y) {
    this->_payload.structure.j2x = x;
    this->_payload.structure.j2y = y;
}

void Tx::setPotentiometers(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6) {
    this->_payload.structure.p1 = p1;
    this->_payload.structure.p2 = p2;
    this->_payload.structure.p3 = p3;
    this->_payload.structure.p4 = p4;
    this->_payload.structure.p5 = p5;
    this->_payload.structure.p6 = p6;
}

void Tx::setPotentiometerSwitches(uint8_t p1s, uint8_t p2s, uint8_t p3s, uint8_t p4s, uint8_t p5s, uint8_t p6s) {
    this->_payload.structure.p1s = p1s;
    this->_payload.structure.p2s = p2s;
    this->_payload.structure.p3s = p3s;
    this->_payload.structure.p4s = p4s;
    this->_payload.structure.p5s = p5s;
    this->_payload.structure.p6s = p6s;
}

void Tx::setSwitches(uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4, uint8_t s5) {
    this->_payload.structure.s1 = s1;
    this->_payload.structure.s2 = s2;
    this->_payload.structure.s3 = s3;
    this->_payload.structure.s4 = s4;
    this->_payload.structure.s5 = s5;
}

void Tx::setAnoRotaryEncoderLeft(uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t center) {
    this->_payload.structure.re1_up = up;
    this->_payload.structure.re1_down = down;
    this->_payload.structure.re1_left = left;
    this->_payload.structure.re1_right = right;
    this->_payload.structure.re1_center = center;
}

void Tx::setAnoRotaryEncoderLeftPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high) {
    this->_payload.structure.re1_pos_low = low;
    this->_payload.structure.re1_pos_mid_low = mid_low;
    this->_payload.structure.re1_pos_mid_high = mid_high;
    this->_payload.structure.re1_pos_high = high;
}

void Tx::setAnoRotaryEncoderRight(uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t center) {
    this->_payload.structure.re2_up = up;
    this->_payload.structure.re2_down = down;
    this->_payload.structure.re2_left = left;
    this->_payload.structure.re2_right = right;
    this->_payload.structure.re2_center = center;
}

void Tx::setAnoRotaryEncoderRightPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high) {
    this->_payload.structure.re2_pos_low = low;
    this->_payload.structure.re2_pos_mid_low = mid_low;
    this->_payload.structure.re2_pos_mid_high = mid_high;
    this->_payload.structure.re2_pos_high = high;
}

int Tx::getAnoRotaryEncoderPosition(
    uint8_t high, uint8_t mid_high, uint8_t mid_low, uint8_t low
) {
    // Reconstruct the int value from the stored bytes
    return  (high << 24) | (mid_high << 16) | (mid_low << 8) | low;
}

int Tx::getLeftAnoRotaryEncoderPosition() {
    return Tx::getAnoRotaryEncoderPosition(
        this->_payload.structure.re1_pos_high,
        this->_payload.structure.re1_pos_mid_high,
        this->_payload.structure.re1_pos_mid_low,
        this->_payload.structure.re1_pos_low
    );
}

int Tx::getRightAnoRotaryEncoderPosition() {
    return Tx::getAnoRotaryEncoderPosition(
        this->_payload.structure.re2_pos_high,
        this->_payload.structure.re2_pos_mid_high,
        this->_payload.structure.re2_pos_mid_low,
        this->_payload.structure.re2_pos_low
    );
}

uint8_t* Tx::getByteArray() {
    return this->_payload.byteArray;
}
