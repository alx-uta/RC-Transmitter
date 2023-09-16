/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef TX_HPP
#define TX_HPP

#include <MCP_ADC.h>
#include <MCP23S17.h>
#include "../config/config.hpp"
#include "../rotary/rotary.hpp"

class Tx {
public:
    Tx(
        MCP3208& joystick,
        MCP3208& potentiometer,
        MCP23S17& rotaryRead,
        MCP23S17& switches,
        Rotary& leftRotary,
        Rotary& rightRotary,
        Config& config
    );

    // Data Read
    void readData();
    void joysticks();
    void potentiometers();
    void readMCP23S17();
    
    // Payload
    uint8_t* getByteArray();
    void defaultValues();

    int applyJoystickThreshold(int value, int middle, int driftValue, int mappedValue);
    void setLeftJoystick(uint8_t x, uint8_t y);
    void setRightJoystick(uint8_t x, uint8_t y);

    void setPotentiometers(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6);
    void setSwitchesPushButtons(uint16_t pin_state_encoders, uint16_t pin_state_switches);
    void setAnoRotaryEncoderLeftPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high);
    void setAnoRotaryEncoderRightPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high);
    
    int leftAnoRotaryEncoderPosition = 0;
    int rightAnoRotaryEncoderPosition = 0;
    int getAnoRotaryEncoderPosition(uint8_t high, uint8_t mid_high, uint8_t mid_low, uint8_t low);
    int getLeftAnoRotaryEncoderPosition();
    int getRightAnoRotaryEncoderPosition();
    uint16_t encodeSwitchStatusesToByte(bool switchStatuses[], int numSwitches);
    void decodeByteToSwitchStatuses(uint16_t encodedByte, bool switchStatuses[], int numSwitches);

    typedef struct package {
        // Set the sender identifier number
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

    btPacket_t _payload;

    uint8_t joystick_default_value;

private:
    int joystickMap(
        int current_value,
        int min_value,
        int max_value,
        int middle_value,
        int default_value,
        int out_min,
        int out_max
    );

    MCP3208& _joystick;
    MCP3208& _potentiometer;
    MCP23S17& _rotaryRead;
    MCP23S17& _switches;
    Rotary& _leftRotary;
    Rotary& _rightRotary;
    Config& _config;
};

#endif // TX_HPP