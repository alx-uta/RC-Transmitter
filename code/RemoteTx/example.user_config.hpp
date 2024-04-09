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
uint8_t CALIBRATION_READINGS     = 1000;
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
int pot_max = 4093; // pot_max - pot_drift_value
uint8_t pot_out_min = 0;
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

/*!
  \brief No shaping.
*/
#define RADIOLIB_SHAPING_NONE                                   (0x00)

/*!
  \brief Gaussian shaping filter, BT = 0.5
*/
#define RADIOLIB_SHAPING_0_5                                    (0x02)

/*!
  \brief Gaussian shaping filter, BT = 1.0
*/
#define RADIOLIB_SHAPING_1_0                                    (0x04)

float   SX1280_FREQUENCY            = 2410;
int     SX1280_BIT_RATE             = 260; // 260, 325, 520, 650, 1000 and 1300
int     SX1280_CODING_RATE          = 2;
int     SX1280_OUTPUT_POWER         = 8; // -18 to 13 dBm
int     SX1280_GAIN_CONTROL         = 8; // 1 - 13

uint8_t SX1280_DATA_SHAPING         = RADIOLIB_SHAPING_0_5;
uint8_t SX1280_SYNC_WORD[]          = {0x01, 0x23, 0x45, 0x67};

#endif  // USER_CONFIG_HPP
