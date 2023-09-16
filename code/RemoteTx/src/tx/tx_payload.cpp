/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "tx.hpp"

void Tx::defaultValues() {
    // Identifier
    this->_payload.structure.sender = 1;

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

    // Ano Rotary Encoder - Left
    this->_payload.structure.re1_pos_high = 0;
    this->_payload.structure.re1_pos_mid_high = 0;
    this->_payload.structure.re1_pos_mid_low = 0;
    this->_payload.structure.re1_pos_low = 0;

    // Ano Rotary Encoder - Right
    this->_payload.structure.re2_pos_low = 0;
    this->_payload.structure.re2_pos_mid_low = 0;
    this->_payload.structure.re2_pos_mid_high = 0;
    this->_payload.structure.re2_pos_high = 0;

    this->_payload.structure.switches_state_1 = 0;
    this->_payload.structure.switches_state_2 = 0;
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

void Tx::setSwitchesPushButtons(uint16_t pin_state_encoders, uint16_t pin_state_switches) {
    bool switchStatuses[15] = {
        // Store the current switches
        (pin_state_switches & (1 << _config.button_switch_1)) != 0,
        (pin_state_switches & (1 << _config.button_switch_2)) != 0,
        (pin_state_switches & (1 << _config.button_switch_3)) != 0,
        (pin_state_switches & (1 << _config.button_switch_4)) != 0,
        (pin_state_switches & (1 << _config.button_switch_5)) != 0,

        // Rotary Encoder - Left
        (pin_state_encoders & (1 << _config.rotary_encoder_1_up)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_1_down)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_1_left)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_1_right)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_1_center)) != 0,

        // Rotary Encoder - Right
        (pin_state_encoders & (1 << _config.rotary_encoder_2_up)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_2_down)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_2_left)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_2_right)) != 0,
        (pin_state_encoders & (1 << _config.rotary_encoder_2_center)) != 0
    };

    // Encode switch statuses into two bytes
    uint16_t switches_state = Tx::encodeSwitchStatusesToByte(switchStatuses, 15);

    // Extract the lower and upper bytes
    this->_payload.structure.switches_state_1 = (switches_state & 0xFF);
    this->_payload.structure.switches_state_2 = ((switches_state >> 8) & 0xFF);
}

void Tx::setAnoRotaryEncoderLeftPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high) {
    this->_payload.structure.re1_pos_high = high;
    this->_payload.structure.re1_pos_mid_high = mid_high;
    this->_payload.structure.re1_pos_mid_low = mid_low;
    this->_payload.structure.re1_pos_low = low;
}

void Tx::setAnoRotaryEncoderRightPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high) {
    this->_payload.structure.re2_pos_high = high;
    this->_payload.structure.re2_pos_mid_high = mid_high;
    this->_payload.structure.re2_pos_mid_low = mid_low;
    this->_payload.structure.re2_pos_low = low;
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
