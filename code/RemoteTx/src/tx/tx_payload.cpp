/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "tx.hpp"

void Tx::setLeftJoystick(uint8_t x, uint8_t y) {
    // Enable or disable this channel
    payload_config[3] = (x == joystick_default_value) ? 0 : 1;
    if (payload_config[3]) {
        this->channels[0].first_byte = x;
    }

    // Enable or disable this channel
    payload_config[4] = (y == joystick_default_value) ? 0 : 1;
    if (payload_config[4]) {
        this->channels[1].first_byte = y;
    }
}

void Tx::setRightJoystick(uint8_t x, uint8_t y) {
    // Enable or disable this channel
    payload_config[5] = (x == joystick_default_value) ? 0 : 1;
    if(payload_config[5]) {
        this->channels[2].first_byte = x;
    }

    // Enable or disable this channel
    payload_config[6] = (y == joystick_default_value) ? 0 : 1;
    if(payload_config[6]) {
        this->channels[3].first_byte = y;
    }
}

void Tx::setPotentiometers(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6) {
    uint8_t p_values[] = {p1, p2, p3, p4, p5, p6};
    uint8_t payload_config_offset = 10;

    for (int i = 0; i < 6; i++) {
        // Update the payload_config and channels
        payload_config[payload_config_offset + i] = (p_values[i] == 0) ? 0 : 1;

        if (payload_config[payload_config_offset + i]) {
            this->channels[7 + i].first_byte = p_values[i];
        }
    }
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
    this->switches_state = this->encodeStatusToByte(switchStatuses, 15);

    // Enable or disable this channel
    payload_config[7] = (0 == this->switches_state) ? 0 : 1;
    if(payload_config[7]) {
        // Update the channel for the switches
        // Extract the lower and upper bytes
        this->channels[4].first_byte = (this->switches_state & 0xFF);
        this->channels[4].second_byte = ((this->switches_state >> 8) & 0xFF);
    }

}

void Tx::setAnoRotaryEncoderLeftPosition(uint8_t byte_1, uint8_t byte_2) {
    // Enable or disable this channel
    payload_config[8] = ((0 == byte_1) and (0 == byte_2)) ? 0 : 1;
    if(payload_config[8]) {
        this->channels[5].first_byte = byte_1;
        this->channels[5].second_byte = byte_2;
    }
}

void Tx::setAnoRotaryEncoderRightPosition(uint8_t byte_1, uint8_t byte_2) {
    // Enable or disable this channel
    payload_config[9] = ((0 == byte_1) and (0 == byte_2)) ? 0 : 1;
    if(payload_config[9]) {
        this->channels[6].first_byte = byte_1;
        this->channels[6].second_byte = byte_2;
    }
}

int16_t Tx::getAnoRotaryEncoderPosition(
    uint8_t byte_1, uint8_t byte_2
) {
    // Reconstruct the int value from the stored bytes
    return (int16_t)((byte_1 << 8) | byte_2);
}

int Tx::getPayloadSize() {
    this->payload_size = 2;
    for (int i = 3; i < 16; i++) {
        if (payload_config[i]) {
            this->increasePayloadSize(this->channels[i - 3].required_bytes);
        }
    }
    return this->payload_size;
}

uint8_t* Tx::getPayload() {
    int payload_size = this->getPayloadSize();
    this->current_payload_size = payload_size;

    uint8_t* payload_data = (uint8_t*)malloc(this->maximum_payload_size);

    if (payload_data == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    uint8_t current_position = 0;

    // Add the current config to the payload
    uint16_t config_encode = this->encodeStatusToByte(this->payload_config, 16);
    payload_data[current_position++] = (config_encode & 0xFF);
    payload_data[current_position++] = (config_encode >> 8);

    for (int i = 3; i < 16; i++) {
        if (this->payload_config[i]) {
            uint8_t first_byte = this->channels[i - 3].first_byte;
            payload_data[current_position++] = first_byte;

            if (this->channels[i - 3].required_bytes == 2) {
                uint8_t second_byte = this->channels[i - 3].second_byte;
                payload_data[current_position++] = second_byte;
            }
        }
    }
    return payload_data;
}