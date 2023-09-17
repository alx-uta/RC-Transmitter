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
    if(_payload[0] == 1 and _config.CURRENT_FREQUENCY==_config.SX1280_FREQUENCY) {
        Rx::setTXpayload(_payload);
    }
}

void Rx::setTXpayload(uint8_t* _payload) {
    memcpy(Rx::_payload.byteArray, _payload, sizeof(Rx::_payload.byteArray));
}

void Rx::updateTftRemoteTX() {
    /**
     * Joysticks
     */
    _LEFT_JOYSTICK_X.update(
        constrain(
            Rx::_payload.structure.j1x, _config.joystick_min, _config.joystick_max
        )
    );
    _LEFT_JOYSTICK_Y.update(
        constrain(
            Rx::_payload.structure.j1y, _config.joystick_min, _config.joystick_max
        )
    );
        
    _RIGHT_JOYSTICK_X.update(
        constrain(
            Rx::_payload.structure.j2x, _config.joystick_min, _config.joystick_max
        )
    );
    _RIGHT_JOYSTICK_Y.update(
        constrain(
            Rx::_payload.structure.j2y, _config.joystick_min, _config.joystick_max
        )
    );

    /**
     * Potentiometers
     */
    _SLIDER_POT_1.update(constrain(Rx::_payload.structure.p1,_config.pot_min,_config.pot_max));
    _SLIDER_POT_2.update(constrain(Rx::_payload.structure.p2,_config.pot_min,_config.pot_max));
    _SLIDER_POT_3.update(constrain(Rx::_payload.structure.p3,_config.pot_min,_config.pot_max));
    _SLIDER_POT_4.update(constrain(Rx::_payload.structure.p4,_config.pot_min,_config.pot_max));
    _SLIDER_POT_5.update(constrain(Rx::_payload.structure.p5,_config.pot_min,_config.pot_max));
    _SLIDER_POT_6.update(constrain(Rx::_payload.structure.p6,_config.pot_min,_config.pot_max));

    /**
     * Rotary Encoders
     */
    _DISPLAY_POSITION_LEFT.update(
        Rx::getAnoRotaryEncoderPosition(
            Rx::_payload.structure.re1_byte_1,
            Rx::_payload.structure.re1_byte_2
        )
    );

    _DISPLAY_POSITION_RIGHT.update(
        Rx::getAnoRotaryEncoderPosition(
            Rx::_payload.structure.re2_byte_1,
            Rx::_payload.structure.re2_byte_2
        )
    );

    uint16_t combined_byte = Rx::combineBytes(
        Rx::_payload.structure.switches_state_1, Rx::_payload.structure.switches_state_2
    );

    // Decode the uint16_t back into switch statuses
    bool decoded_switch_statuses[15];
    Rx::decodeByteToSwitchStatuses(combined_byte, decoded_switch_statuses, 15);

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
