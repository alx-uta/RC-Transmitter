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

    void setChannel(uint8_t channel, uint8_t first_byte, uint8_t second_byte);

    // Set each channel
    void setCh1(uint8_t byte_1);
    void setCh2(uint8_t byte_1);
    void setCh3(uint8_t byte_1);
    void setCh4(uint8_t byte_1);
    void setCh5(uint8_t byte_1, uint8_t byte_2);
    void setCh6(uint8_t byte_1, uint8_t byte_2);
    void setCh7(uint8_t byte_1, uint8_t byte_2);
    void setCh8(uint8_t byte_1);
    void setCh9(uint8_t byte_1);
    void setCh10(uint8_t byte_1);
    void setCh11(uint8_t byte_1);
    void setCh12(uint8_t byte_1);
    void setCh13(uint8_t byte_1);

    void updateTftRemoteTX();

    // Utils
    int16_t getAnoRotaryEncoderPosition(uint8_t byte_1, uint8_t byte_2);
    void decodeByteToStatuses(uint16_t encodedByte, bool statuses[], int num);
    uint16_t combineBytes(uint8_t byte1, uint8_t byte2);

    float valRound(float val);

    void readBatteryPercentage(float BATTERY_MIN, float BATTERY_MAX);

    // Payload
    typedef struct package {
        // Config
        uint8_t config_first_byte;
        uint8_t config_second_byte;

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
        uint8_t re1_byte_1;
        uint8_t re1_byte_2;

        // Split re2_pos into individual bytes
        uint8_t re2_byte_1;
        uint8_t re2_byte_2;

        uint8_t switches_state_1;
        uint8_t switches_state_2;
    };

    typedef union btPacket_t {
        package data;
        uint8_t byteArray[18];
    };
    package payload;
    btPacket_t _payload;

    /**
     * TX Payload Config
     * TX0 : Remote TX
     * TX1 : Sensors 1
     * TX2 : Sensors 2
     * 
     * CH1  : j1y - Left Joystick Up/Down
     * CH2  : j1x - Left Joystick Left/Right
     * CH3  : j2y - Right Joystick Up/Down
     * CH4  : j2x - Right Joystick Left/Right
     * CH5  : switches_state_1 + switches_state_2
     * CH6  : re1_byte_1 + re1_byte_2
     * CH7  : re2_byte_1 + re2_byte_2
     * CH8  : p1
     * CH9  : p2
     * CH10 : p3
     * CH11 : p4
     * CH12 : p5
     * CH13 : p6
     */
    bool payload_config[16] = {
        0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    typedef struct Channel {
        uint8_t required_bytes;
        uint8_t default_value;
    };

    /**
     * CH1  : j1y - Left Joystick Up/Down
     * CH2  : j1x - Left Joystick Left/Right
     * CH3  : j2y - Right Joystick Up/Down
     * CH4  : j2x - Right Joystick Left/Right
     * CH5  : switches_state_1 + switches_state_2
     * CH6  : re1_byte_1 + re1_byte_2
     * CH7  : re2_byte_1 + re2_byte_2
     * CH8  : p1
     * CH9  : p2
     * CH10 : p3
     * CH11 : p4
     * CH12 : p5
     * CH13 : p6
     */
    Channel channels[13] = {
        {1, 127},
        {1, 127},
        {1, 127},
        {1, 127},
        {2, 0},
        {2, 0},
        {2, 0},
        {1, 0},
        {1, 0},
        {1, 0},
        {1, 0},
        {1, 0},
        {1, 0}
    };

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

    // Rotary Encoders
    int rotary_min = -32768;
    int rotary_max = 32768;
};

#endif  // RX_HPP
