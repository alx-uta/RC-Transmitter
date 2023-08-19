/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "tx.hpp"
#include <algorithm> // for std::min

/**
 * Read the data for the joysticks
 */
void Tx::joysticks() {
    int16_t
        joystick_x1,
        joystick_y1,
        joystick_x2,
        joystick_y2;
    uint8_t
        x1,
        y1,
        x2,
        y2,
        joystick_x1_map,
        joystick_y1_map,
        joystick_x2_map,
        joystick_y2_map;

    const uint8_t joysticks_num_channels = 4;
    uint8_t joysticks_channels[joysticks_num_channels] = {
        _config.LEFT_JOYSTICK_X,
        _config.LEFT_JOYSTICK_Y,
        _config.RIGHT_JOYSTICK_X,
        _config.RIGHT_JOYSTICK_Y
    };

    // Joysticks Values
    int16_t readings[joysticks_num_channels];
    _joystick.analogReadMultiple(joysticks_channels, joysticks_num_channels, readings);

    joystick_x1 = readings[_config.LEFT_JOYSTICK_X];
    joystick_y1 = readings[_config.LEFT_JOYSTICK_Y];
    joystick_x2 = readings[_config.RIGHT_JOYSTICK_X];
    joystick_y2 = readings[_config.RIGHT_JOYSTICK_Y];

    // Left joystick
    joystick_x1_map = Tx::joystickMap(
        joystick_x1,
        _config.left_joystick_min_value_x + _config.left_joystick_drift_value_x,
        _config.left_joystick_max_value_x - _config.left_joystick_drift_value_x,
        _config.left_joystick_middle_value_x,
        _config.joystick_default_value,
        _config.joystick_min_out,
        _config.joystick_max_out
    );
    joystick_y1_map = Tx::joystickMap(
        joystick_y1,
        _config.left_joystick_min_value_y + _config.left_joystick_drift_value_y,
        _config.left_joystick_max_value_y - _config.left_joystick_drift_value_y,
        _config.left_joystick_middle_value_y,
        _config.joystick_default_value,
        _config.joystick_min_out,
        _config.joystick_max_out
    );

    // Right Joystick
    joystick_x2_map = Tx::joystickMap(
        joystick_x2,
        _config.right_joystick_min_value_x + _config.right_joystick_drift_value_x,
        _config.right_joystick_max_value_x - _config.right_joystick_drift_value_x,
        _config.right_joystick_middle_value_x,
        _config.joystick_default_value,
        _config.joystick_min_out,
        _config.joystick_max_out
    );
    joystick_y2_map = Tx::joystickMap(
        joystick_y2,
        _config.right_joystick_min_value_y + _config.right_joystick_drift_value_y,
        _config.right_joystick_max_value_y - _config.right_joystick_drift_value_y,
        _config.right_joystick_middle_value_y,
        _config.joystick_default_value,
        _config.joystick_min_out,
        _config.joystick_max_out
    );

    /**
     * Set the payload accounting for the drift value
     */
    // Left Joystick
    x1 = Tx::applyJoystickThreshold(joystick_x1, _config.left_joystick_middle_value_x, _config.left_joystick_drift_value_x, joystick_x1_map);
    y1 = Tx::applyJoystickThreshold(joystick_y1, _config.left_joystick_middle_value_y, _config.left_joystick_drift_value_y, joystick_y1_map);

    // Right Joystick
    x2 = Tx::applyJoystickThreshold(joystick_x2, _config.right_joystick_middle_value_x, _config.right_joystick_drift_value_x, joystick_x2_map);
    y2 = Tx::applyJoystickThreshold(joystick_y2, _config.right_joystick_middle_value_y, _config.right_joystick_drift_value_y, joystick_y2_map);

    Tx::setLeftJoystick(x1, y1);
    Tx::setRightJoystick(x2, y2);
}


/**
 * Read the data for the potentiometers
 */
void Tx::potentiometers() {
    int
        // Potentiometer Last Value
        pot1LastValue, pot2LastValue, pot3LastValue, pot4LastValue, pot5LastValue, pot6LastValue,
        potLastValue;
        
        const uint8_t potentiometers_num_channels = 6;
        uint8_t potentiometers_channels[potentiometers_num_channels] = {
            _config.POTENTIOMETER_1_ADC,
            _config.POTENTIOMETER_2_ADC,
            _config.POTENTIOMETER_3_ADC,
            _config.POTENTIOMETER_4_ADC,
            _config.POTENTIOMETER_5_ADC,
            _config.POTENTIOMETER_6_ADC
        };

    // Potentiometer Values
    int16_t readings[potentiometers_num_channels];
    _potentiometer.analogReadMultiple(potentiometers_channels, potentiometers_num_channels, readings);

    // Prevent jumping values
    const int numPots = 6;

    int potValues[numPots] = {
        readings[_config.POTENTIOMETER_1_ADC],
        readings[_config.POTENTIOMETER_2_ADC],
        readings[_config.POTENTIOMETER_3_ADC],
        readings[_config.POTENTIOMETER_4_ADC],
        readings[_config.POTENTIOMETER_5_ADC],
        readings[_config.POTENTIOMETER_6_ADC]
    };
    int potLastValues[numPots] = {pot1LastValue, pot2LastValue, pot3LastValue, pot4LastValue, pot5LastValue, pot6LastValue};

    for (int i = 0; i < numPots; ++i) {
        int diff = abs(potLastValues[i] - potValues[i]);
        if (diff > _config.pot_drift_value) {
            if (potValues[i] > _config.pot_max) {
                potLastValues[i] = _config.pot_max;
            } else {
                potLastValues[i] = potValues[i];
            }
        }
    }

    // Set the payload
    for (int i = 0; i < 6; ++i) {
        potLastValues[i] = map(potLastValues[i], _config.pot_min, _config.pot_max, _config.pot_min, _config.pot_out_max);
    }

    Tx::setPotentiometers(
        potLastValues[0],
        potLastValues[1],
        potLastValues[2],
        potLastValues[3],
        potLastValues[4],
        potLastValues[5]
    );
}


/**
 * Read the data for the rotary encoders
 */
void Tx::rotaryEncoders() {
    uint16_t pinState = _rotaryRead.read16();

    // Get the encoder position
    Tx::leftAnoRotaryEncoderPosition -= _leftRotary.encoderDirection(
        (pinState & (1 << _config.rotary_encoder_1_enc_b)) != 0,
        (pinState & (1 << _config.rotary_encoder_1_enc_a)) != 0
    );

    Tx::rightAnoRotaryEncoderPosition -= _rightRotary.encoderDirection(
        (pinState & (1 << _config.rotary_encoder_2_enc_b)) != 0,
        (pinState & (1 << _config.rotary_encoder_2_enc_a)) != 0
    );

    // Update the encoder position
    Tx::setAnoRotaryEncoderLeftPosition(
        (uint8_t)(Tx::leftAnoRotaryEncoderPosition),
        (uint8_t)(Tx::leftAnoRotaryEncoderPosition >> 8),
        (uint8_t)(Tx::leftAnoRotaryEncoderPosition >> 16),
        (uint8_t)(Tx::leftAnoRotaryEncoderPosition >> 24)
    );

    Tx::setAnoRotaryEncoderRightPosition(
        (uint8_t)(Tx::rightAnoRotaryEncoderPosition),
        (uint8_t)(Tx::rightAnoRotaryEncoderPosition >> 8),
        (uint8_t)(Tx::rightAnoRotaryEncoderPosition >> 16),
        (uint8_t)(Tx::rightAnoRotaryEncoderPosition >> 24)
    );

    // Update the push buttons
    Tx::setAnoRotaryEncoderLeft(
        (pinState & (1 << _config.rotary_encoder_1_up)) != 0,
        (pinState & (1 << _config.rotary_encoder_1_down)) != 0,
        (pinState & (1 << _config.rotary_encoder_1_left)) != 0,
        (pinState & (1 << _config.rotary_encoder_1_right)) != 0,
        (pinState & (1 << _config.rotary_encoder_1_center)) != 0
    );

    Tx::setAnoRotaryEncoderRight(
        (pinState & (1 << _config.rotary_encoder_2_up)) != 0,
        (pinState & (1 << _config.rotary_encoder_2_down)) != 0,
        (pinState & (1 << _config.rotary_encoder_2_left)) != 0,
        (pinState & (1 << _config.rotary_encoder_2_right)) != 0,
        (pinState & (1 << _config.rotary_encoder_2_center)) != 0
    );
}


/**
 * Read the data for the switches
 */
void Tx::switches() {

    uint16_t pinState = _switches.read16();
    /**
     * Potentiometer Switch Button
     */
    Tx::setPotentiometerSwitches(
        (pinState & (1 << _config.button_switch_pot_1)) != 0,
        (pinState & (1 << _config.button_switch_pot_2)) != 0,
        (pinState & (1 << _config.button_switch_pot_3)) != 0,
        (pinState & (1 << _config.button_switch_pot_4)) != 0,
        (pinState & (1 << _config.button_switch_pot_5)) != 0,
        (pinState & (1 << _config.button_switch_pot_6)) != 0
    );

    /**
     * Switch Button
     */
    Tx::setSwitches(
        (pinState & (1 << _config.button_switch_1)) != 0,
        (pinState & (1 << _config.button_switch_2)) != 0,
        (pinState & (1 << _config.button_switch_3)) != 0,
        (pinState & (1 << _config.button_switch_4)) != 0,
        (pinState & (1 << _config.button_switch_5)) != 0
    );
}
