/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 *
 * Alex Uta
 * microknot.dev
 */

#include "rx.hpp"

Rx::Rx(
    Config& config,
    TFT_eSPI& tft,

    // TX/RX Battery
    BatteryIcon& TX_BATTERY,
    BatteryIcon& RX_BATTERY,

    // Left Rotary Encoder
    DisplayNumber& DISPLAY_POSITION_LEFT,
    RotaryEncoder& ENCODER_LEFT,

    // Right Rotary Encoder
    DisplayNumber& DISPLAY_POSITION_RIGHT,
    RotaryEncoder& ENCODER_RIGHT,

    // Left Joystick
    HorizontalSlider& LEFT_JOYSTICK_X,
    VerticalSlider& LEFT_JOYSTICK_Y,

    // Right Joystick
    HorizontalSlider& RIGHT_JOYSTICK_X,
    VerticalSlider& RIGHT_JOYSTICK_Y,

    // Potentiometers
    VerticalSlider& SLIDER_POT_1,
    VerticalSlider& SLIDER_POT_2,
    VerticalSlider& SLIDER_POT_3,
    VerticalSlider& SLIDER_POT_4,
    VerticalSlider& SLIDER_POT_5,
    VerticalSlider& SLIDER_POT_6,

    // Switches
    Switch& S1,
    Switch& S2,
    Switch& S3,
    Switch& S4,
    Switch& S5
)
    :   _config(config),
        _tft(tft),

        // TX/RX Battery
        _TX_BATTERY(TX_BATTERY),
        _RX_BATTERY(RX_BATTERY),

        // Left Rotary Encoder
        _DISPLAY_POSITION_LEFT(DISPLAY_POSITION_LEFT),
        _ENCODER_LEFT(ENCODER_LEFT),

        // Right Rotary Encoder
        _DISPLAY_POSITION_RIGHT(DISPLAY_POSITION_RIGHT),
        _ENCODER_RIGHT(ENCODER_RIGHT),

        // Left Joystick
        _LEFT_JOYSTICK_X(LEFT_JOYSTICK_X),
        _LEFT_JOYSTICK_Y(LEFT_JOYSTICK_Y),

        // Right Joystick
        _RIGHT_JOYSTICK_X(RIGHT_JOYSTICK_X),
        _RIGHT_JOYSTICK_Y(RIGHT_JOYSTICK_Y),

        // Potentiometers
        _SLIDER_POT_1(SLIDER_POT_1),
        _SLIDER_POT_2(SLIDER_POT_2),
        _SLIDER_POT_3(SLIDER_POT_3),
        _SLIDER_POT_4(SLIDER_POT_4),
        _SLIDER_POT_5(SLIDER_POT_5),
        _SLIDER_POT_6(SLIDER_POT_6),

        // Switches
        _S1(S1),
        _S2(S2),
        _S3(S3),
        _S4(S4),
        _S5(S5)

         {}

/**
 * Read and set the right values
 */
void Rx::setData(
    uint8_t* _payload
) {
    // Get the config from the next two bytes
    uint16_t config_combined_byte = this->combineBytes(
        _payload[0],
        _payload[1]
    );

    // Decode the uint16_t back into config and channels
    bool decoded_config[16];
    this->decodeByteToStatuses(config_combined_byte, decoded_config, 16);

    for (int i = 3; i < 16; i++) {
        this->payload_config[i] = decoded_config[i];
    }

    if(this->payload_config[0] == 0 and _config.CURRENT_FREQUENCY==_config.SX1280_FREQUENCY) {
        this->setTXpayload(_payload);
    }
}

void Rx::setTXpayload(uint8_t* _payload) {
    uint8_t current_position = 2;

    for (int i = 3; i < 16; i++) {
        uint8_t channel = i - 2;
        if (this->payload_config[i]) {
            uint8_t required_bytes = this->channels[channel-1].required_bytes;
            uint8_t first_byte = _payload[current_position++];
            uint8_t second_byte = (required_bytes == 2) ? _payload[current_position++] : 0;
            this->setChannel(channel, first_byte, second_byte);
        } else {
            uint8_t default_value = this->channels[channel-1].default_value;
            this->setChannel(channel, default_value, 0);
        }
    }
}

void Rx::setChannel(uint8_t channel, uint8_t first_byte, uint8_t second_byte) {
    switch (channel) {
        case 1:
            setCh1(first_byte);
            break;
        case 2:
            setCh2(first_byte);
            break;
        case 3:
            setCh3(first_byte);
            break;
        case 4:
            setCh4(first_byte);
            break;
        case 5:
            setCh5(first_byte, second_byte);
            break;
        case 6:
            setCh6(first_byte, second_byte);
            break;
        case 7:
            setCh7(first_byte, second_byte);
            break;
        case 8:
            setCh8(first_byte);
            break;
        case 9:
            setCh9(first_byte);
            break;
        case 10:
            setCh10(first_byte);
            break;
        case 11:
            setCh11(first_byte);
            break;
        case 12:
            setCh12(first_byte);
            break;
        case 13:
            setCh13(first_byte);
            break;
        default:
            // pass
            break;
    }
}

void Rx::setCh1(uint8_t byte_1) {
    this->_payload.data.j1x = byte_1;
}
void Rx::setCh2(uint8_t byte_1) {
    this->_payload.data.j1y = byte_1;
}
void Rx::setCh3(uint8_t byte_1) {
    this->_payload.data.j2x = byte_1;
}
void Rx::setCh4(uint8_t byte_1) {
    this->_payload.data.j2y = byte_1;
}
void Rx::setCh5(uint8_t byte_1, uint8_t byte_2) {
    this->_payload.data.switches_state_1 = byte_1;
    this->_payload.data.switches_state_2 = byte_2;
}
void Rx::setCh6(uint8_t byte_1, uint8_t byte_2) {
    this->_payload.data.re1_byte_1 = byte_1;
    this->_payload.data.re1_byte_2 = byte_2;
}
void Rx::setCh7(uint8_t byte_1, uint8_t byte_2) {
    this->_payload.data.re2_byte_1 = byte_1;
    this->_payload.data.re2_byte_2 = byte_2;
}
void Rx::setCh8(uint8_t byte_1) {
    this->_payload.data.p1 = byte_1;
}
void Rx::setCh9(uint8_t byte_1) {
    this->_payload.data.p2 = byte_1;
}
void Rx::setCh10(uint8_t byte_1) {
    this->_payload.data.p3 = byte_1;
}
void Rx::setCh11(uint8_t byte_1) {
    this->_payload.data.p4 = byte_1;
}
void Rx::setCh12(uint8_t byte_1) {
    this->_payload.data.p5 = byte_1;
}
void Rx::setCh13(uint8_t byte_1) {
    this->_payload.data.p6 = byte_1;
}

void Rx::updateTftRemoteTX() {
    /**
     * Joysticks
     */
    _LEFT_JOYSTICK_X.update(
        constrain(
            this->_payload.data.j1x, _config.joystick_min, _config.joystick_max
        )
    );
    _LEFT_JOYSTICK_Y.update(
        constrain(
            this->_payload.data.j1y, _config.joystick_min, _config.joystick_max
        )
    );

    _RIGHT_JOYSTICK_X.update(
        constrain(
            this->_payload.data.j2x, _config.joystick_min, _config.joystick_max
        )
    );
    _RIGHT_JOYSTICK_Y.update(
        constrain(
            this->_payload.data.j2y, _config.joystick_min, _config.joystick_max
        )
    );

    /**
     * Potentiometers
     */
    _SLIDER_POT_1.update(constrain(this->_payload.data.p1,_config.pot_min,_config.pot_max));
    _SLIDER_POT_2.update(constrain(this->_payload.data.p2,_config.pot_min,_config.pot_max));
    _SLIDER_POT_3.update(constrain(this->_payload.data.p3,_config.pot_min,_config.pot_max));
    _SLIDER_POT_4.update(constrain(this->_payload.data.p4,_config.pot_min,_config.pot_max));
    _SLIDER_POT_5.update(constrain(this->_payload.data.p5,_config.pot_min,_config.pot_max));
    _SLIDER_POT_6.update(constrain(this->_payload.data.p6,_config.pot_min,_config.pot_max));

    /**
     * Rotary Encoders
     */
    _DISPLAY_POSITION_LEFT.update(
        this->getAnoRotaryEncoderPosition(
            this->_payload.data.re1_byte_1,
            this->_payload.data.re1_byte_2
        )
    );

    _DISPLAY_POSITION_RIGHT.update(
        this->getAnoRotaryEncoderPosition(
            this->_payload.data.re2_byte_1,
            this->_payload.data.re2_byte_2
        )
    );

    uint16_t combined_byte = this->combineBytes(
        this->_payload.data.switches_state_1, this->_payload.data.switches_state_2
    );

    // Decode the uint16_t back into switch statuses
    bool decoded_switch_statuses[15];
    this->decodeByteToStatuses(combined_byte, decoded_switch_statuses, 15);

    /**
     * Switches
     */
    _S1.update(decoded_switch_statuses[0]);
    _S2.update(decoded_switch_statuses[1]);
    _S3.update(decoded_switch_statuses[2]);
    _S4.update(decoded_switch_statuses[3]);
    _S5.update(decoded_switch_statuses[4]);

    /**
     * Encoders
     */
    _ENCODER_LEFT.update(
        decoded_switch_statuses[5],
        decoded_switch_statuses[6],
        decoded_switch_statuses[7],
        decoded_switch_statuses[8],
        decoded_switch_statuses[9]
    );

    _ENCODER_RIGHT.update(
        decoded_switch_statuses[10],
        decoded_switch_statuses[11],
        decoded_switch_statuses[12],
        decoded_switch_statuses[13],
        decoded_switch_statuses[14]
    );
}

void Rx::readBatteryPercentage(float BATTERY_MIN, float BATTERY_MAX) {
    /**
     * Improve the ADC Reading
     * https://github.com/G6EJD/ESP32-ADC-Accuracy-Improvement-function/
     */
    int num_readings = 30;
    float smoothing_factor = 0.1;

    int filtered_reading = analogRead(_config.VOLTAGE_MONITOR_PIN);

    for (int i = 1; i < num_readings; i++) {
        int current_reading = analogRead(_config.VOLTAGE_MONITOR_PIN);
        filtered_reading = (smoothing_factor * current_reading) + ((1 - smoothing_factor) * filtered_reading);
    }

    int voltage_reading = filtered_reading;

    float battery_voltage = -0.000000000009824 * pow(
        voltage_reading, 3
    ) + 0.000000016557283 * pow(
        voltage_reading, 2
    ) + 0.000854596860691 * voltage_reading + 0.065440348345433;

    if(voltage_reading < 4095 || voltage_reading > 1) {
        _TX_BATTERY.update(
            constrain(
                map(
                    battery_voltage * 100, BATTERY_MIN * 100, BATTERY_MAX * 100, 0, 100
                ), 0, 100
            )
        );
    }
}
