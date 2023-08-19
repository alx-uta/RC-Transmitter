/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef USER_CONFIG_HPP
#define USER_CONFIG_HPP

// Debug
#define ENABLE_SERIAL_PRINT     true
#define ENABLE_DEBUG            true
#define ENABLE_RADIO_LIB_DEBUG  false

// Calibration
uint8_t calibrationReadings     = 100;
#define ENABLE_CALIBRATION      false

/**
 * MCP3208
 */
#define MCP3208_SPI_SPEED 4000000

/**
 * MCP23S17T
 */
#define MCP23S17T_SPI_SPEED 10000000

// Set the sensitivity value
uint8_t pot_drift_value = 2;
uint8_t pot_min = 0;
int pot_max = 4093 // pot_max - pot_drift_value;
uint8_t pot_out_max = 255;

/**
 * Joysticks
 */
int
    // General values
    joystick_min_out        = 0,
    joystick_max_out        = 255,
    joystick_default_value  = 127,

    /**
     * Left Joystick
     */

    // X
    left_joystick_drift_value_x     = 0,
    left_joystick_min_value_x       = 0,
    left_joystick_max_value_x       = 0,
    left_joystick_middle_value_x    = 0,
    
    // Y
    left_joystick_drift_value_y     = 0,
    left_joystick_min_value_y       = 0,
    left_joystick_max_value_y       = 0,
    left_joystick_middle_value_y    = 0,

    /**
     * Right Joystick
     */

    // X
    right_joystick_drift_value_x    = 0,
    right_joystick_min_value_x      = 0,
    right_joystick_max_value_x      = 0,
    right_joystick_middle_value_x   = 0,
    
    // Y
    right_joystick_drift_value_y    = 0,
    right_joystick_min_value_y      = 0,
    right_joystick_max_value_y      = 0,
    right_joystick_middle_value_y   = 0;

/**
 * SX1280
 */

float   SX1280_FREQUENCY        = 2410.5;
int     SX1280_BIT_RATE         = 520;
int     SX1280_CODING_RATE      = 2;
int     SX1280_OUTPUT_POWER     = 5;
float   SX1280_DATA_SHAPING     = 1.0;
uint8_t SX1280_SYNC_WORD[]      = {0x01, 0x23, 0x45, 0x67};
int     SX1280_CRC_VALUE        = 1;

#endif  // USER_CONFIG_HPP