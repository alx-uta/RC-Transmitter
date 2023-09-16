/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef RX_HPP
#define RX_HPP

#include "../config/config.hpp"
#include "../tft/widgets/battery_icon/battery_icon.hpp"
#include "../tft/widgets/display_number/display_number.hpp"
#include "../tft/widgets/rotary_encoder/rotary_encoder.hpp"
#include "../tft/widgets/vertical_slider/vertical_slider.hpp"
#include "../tft/widgets/horizontal_slider/horizontal_slider.hpp"
#include "../tft/widgets/switch/switch.hpp"

#include <TFT_eSPI.h>

class Rx {
 public:
    Rx(
        Config& config,
        TFT_eSPI& tft,

        // TX/RX Battery
        BatteryIcon& _TX_BATTERY,
        BatteryIcon& _RX_BATTERY,
        
        // Left Rotary Encoder
        DisplayNumber& _DISPLAY_POSITION_LEFT,
        RotaryEncoder& _ENCODER_LEFT,

        // Right Rotary Encoder
        DisplayNumber& _DISPLAY_POSITION_RIGHT,
        RotaryEncoder& _ENCODER_RIGHT,

        // Left Joystick
        HorizontalSlider& _LEFT_JOYSTICK_X,
        VerticalSlider& _LEFT_JOYSTICK_Y,
        
        // Right Joystick
        HorizontalSlider& _RIGHT_JOYSTICK_X,
        VerticalSlider& _RIGHT_JOYSTICK_Y,
        
        // Potentiometers
        VerticalSlider& _SLIDER_POT_1,
        VerticalSlider& _SLIDER_POT_2,
        VerticalSlider& _SLIDER_POT_3,
        VerticalSlider& _SLIDER_POT_4,
        VerticalSlider& _SLIDER_POT_5,
        VerticalSlider& _SLIDER_POT_6,

        // Switches
        Switch& _S1,
        Switch& _S2,
        Switch& _S3,
        Switch& _S4,
        Switch& _S5
    );

    void setData(uint8_t* _payload);
    void setTXpayload(uint8_t* _payload);

    void updateTftRemoteTX();

    // Utils
    int getAnoRotaryEncoderPosition(uint8_t high, uint8_t mid_high, uint8_t mid_low, uint8_t low);
    void decodeByteToSwitchStatuses(uint16_t encodedByte, bool switchStatuses[], int numSwitches);
    uint16_t combineBytes(uint8_t byte1, uint8_t byte2);

    float valRound(float val);

    // Payload
    typedef struct package {
        // Set the sender identifier
        uint8_t sender; // left-right

        // Left Joystick
        uint8_t j1x; // left-right
        uint8_t j1y; // up-down

        // Right Joystick
        uint8_t j2x; // left-right
        uint8_t j2y; // up-down

        // Potentiometers - Values
        uint8_t p1;
        uint8_t p2;
        uint8_t p3;
        uint8_t p4;
        uint8_t p5;
        uint8_t p6;

        // Split re1_pos into individual bytes
        uint8_t re1_pos_high;
        uint8_t re1_pos_mid_high;
        uint8_t re1_pos_mid_low;
        uint8_t re1_pos_low;

        // Split re2_pos into individual bytes
        uint8_t re2_pos_high;
        uint8_t re2_pos_mid_high;
        uint8_t re2_pos_mid_low;
        uint8_t re2_pos_low;

        uint8_t switches_state_1;
        uint8_t switches_state_2;
    };

    typedef union btPacket_t {
        package structure;
        uint8_t byteArray[21];
    };
    package payload;

    btPacket_t _payload;

 private:
    Config& _config;
    TFT_eSPI& _tft;

    // TX/RX Battery
    BatteryIcon& _TX_BATTERY;
    BatteryIcon& _RX_BATTERY;
    
    // Left Rotary Encoder
    DisplayNumber& _DISPLAY_POSITION_LEFT;
    RotaryEncoder& _ENCODER_LEFT;

    // Right Rotary Encoder
    DisplayNumber& _DISPLAY_POSITION_RIGHT;
    RotaryEncoder& _ENCODER_RIGHT;

    // Left Joystick
    HorizontalSlider& _LEFT_JOYSTICK_X;
    VerticalSlider& _LEFT_JOYSTICK_Y;
    
    // Right Joystick
    HorizontalSlider& _RIGHT_JOYSTICK_X;
    VerticalSlider& _RIGHT_JOYSTICK_Y;
    
    // Potentiometers
    VerticalSlider& _SLIDER_POT_1;
    VerticalSlider& _SLIDER_POT_2;
    VerticalSlider& _SLIDER_POT_3;
    VerticalSlider& _SLIDER_POT_4;
    VerticalSlider& _SLIDER_POT_5;
    VerticalSlider& _SLIDER_POT_6;

    // Switches
    Switch& _S1;
    Switch& _S2;
    Switch& _S3;
    Switch& _S4;
    Switch& _S5;
};

#endif  // RX_HPP
