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
    uint8_t* getPayload();
    int getPayloadSize();
    int current_payload_size;

    int applyJoystickThreshold(int value, int middle, int driftValue, int mappedValue);
    void setLeftJoystick(uint8_t x, uint8_t y);
    void setRightJoystick(uint8_t x, uint8_t y);

    void setPotentiometers(uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6);
    void setSwitchesPushButtons(uint16_t pin_state_encoders, uint16_t pin_state_switches);
    void setAnoRotaryEncoderLeftPosition(uint8_t byte_1, uint8_t byte_2);
    void setAnoRotaryEncoderRightPosition(uint8_t byte_1, uint8_t byte_2);

    int leftAnoRotaryEncoderPosition = 0;
    int rightAnoRotaryEncoderPosition = 0;
    int16_t getAnoRotaryEncoderPosition(uint8_t byte_1, uint8_t byte_2);
    uint16_t encodeStatusToByte(bool statuses[], int num);
    void decodeByteToStatus(uint16_t encodedByte, bool statuses[], int num);
    uint16_t combineBytes(uint8_t byte1, uint8_t byte2);
    void increasePayloadSize(uint8_t bytes);

    uint16_t switches_state;
    uint8_t joystick_default_value;

    typedef struct Channel {
        uint8_t required_bytes;
        uint8_t first_byte;
        uint8_t second_byte;
    };

    uint8_t maximum_payload_size = 19;

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
        {1, joystick_default_value, 0},
        {1, joystick_default_value, 0},
        {1, joystick_default_value, 0},
        {1, joystick_default_value, 0},
        {2, 0, 0},
        {2, 0, 0},
        {2, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0}
    };
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
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

private:
    int payload_size;

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