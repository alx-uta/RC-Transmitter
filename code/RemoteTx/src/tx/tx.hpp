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
    void switches();
    void rotaryEncoders();
    
    // Payload
    uint8_t* getByteArray();
    void defaultValues();

    int applyJoystickThreshold(int value, int middle, int driftValue, int mappedValue);
    void setLeftJoystick(uint8_t x, uint8_t y);
    void setRightJoystick(uint8_t x, uint8_t y);

    void setPotentiometers(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6);
    void setPotentiometerSwitches(uint8_t p1s, uint8_t p2s, uint8_t p3s, uint8_t p4s, uint8_t p5s, uint8_t p6s);
    void setSwitches(uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4, uint8_t s5);
    void setAnoRotaryEncoderLeft(uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t center);
    void setAnoRotaryEncoderLeftPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high);
    void setAnoRotaryEncoderRight(uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t center);
    void setAnoRotaryEncoderRightPosition(uint8_t low, uint8_t mid_low, uint8_t mid_high, uint8_t high);
    
    int leftAnoRotaryEncoderPosition = 0;
    int rightAnoRotaryEncoderPosition = 0;
    int getAnoRotaryEncoderPosition(uint8_t high, uint8_t mid_high, uint8_t mid_low, uint8_t low);
    int getLeftAnoRotaryEncoderPosition();
    int getRightAnoRotaryEncoderPosition();

    typedef struct package {
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

        // Potentiometers - Switches
        uint8_t p1s;
        uint8_t p2s;
        uint8_t p3s;
        uint8_t p4s;
        uint8_t p5s;
        uint8_t p6s;
        
        // Switches
        uint8_t s1;
        uint8_t s2;
        uint8_t s3;
        uint8_t s4;
        uint8_t s5;

        // Ano Rotary Encoder - Left
        uint8_t re1_up;
        uint8_t re1_down;
        uint8_t re1_left;
        uint8_t re1_right;
        uint8_t re1_center;

        // Split re1_pos into individual bytes
        uint8_t re1_pos_low;
        uint8_t re1_pos_mid_low;
        uint8_t re1_pos_mid_high;
        uint8_t re1_pos_high;

        // Ano Rotary Encoder - Right
        uint8_t re2_up;
        uint8_t re2_down;
        uint8_t re2_left;
        uint8_t re2_right;
        uint8_t re2_center;

        // Split re2_pos into individual bytes
        uint8_t re2_pos_low;
        uint8_t re2_pos_mid_low;
        uint8_t re2_pos_mid_high;
        uint8_t re2_pos_high;
    };

    typedef union btPacket_t {
        package structure;
        uint8_t byteArray[39];
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
    int encoderDirection(unsigned char direction);
    int encoderPosition(int current_position, int direction);

    MCP3208& _joystick;
    MCP3208& _potentiometer;
    MCP23S17& _rotaryRead;
    MCP23S17& _switches;
    Rotary& _leftRotary;
    Rotary& _rightRotary;
    Config& _config;
};

#endif // TX_HPP