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
#define ENABLE_RADIO_LIB_DEBUG  true

// Calibration
uint8_t calibrationReadings     = 100;
#define ENABLE_CALIBRATION      true

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
int pot_max = 4092;
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
    left_joystick_drift_value_x = 20,//18,
    left_joystick_min_value_x = 718,
    left_joystick_max_value_x = 2995,
    left_joystick_middle_value_x = 1884,//1886,

    // Y
    left_joystick_drift_value_y = 20,//18,
    left_joystick_min_value_y = 495,
    left_joystick_max_value_y = 2920,//2940,
    left_joystick_middle_value_y = 1840,//1847,

    /**
     * Right Joystick
     */

    // X
    right_joystick_drift_value_x = 20,
    right_joystick_min_value_x = 225,
    right_joystick_max_value_x = 3320,
    right_joystick_middle_value_x = 1833, //1833,

    // Y
    right_joystick_drift_value_y = 20,
    right_joystick_min_value_y = 660,
    right_joystick_max_value_y = 3190,//3206,
    right_joystick_middle_value_y = 1963; //1963;

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


float   SX1280_FREQUENCY            = 2400.6;
float   SX1280_FREQUENCY_DEVIATION  = 800.0;
int     SX1280_BIT_RATE             = 250; //250;
int     SX1280_OUTPUT_POWER         = 12; // -18 to 13 dBm
int     SX1280_GAIN_CONTROL         = 12; // 1 - 13
uint8_t SX1280_DATA_SHAPING         = RADIOLIB_SHAPING_1_0;
uint8_t SX1280_SYNC_WORD[]          = {0x09, 0x07, 0x69, 0x01, 0x13};
int     SX1280_SYNC_WORD_LEN        = 5;
int     SX1280_CRC_VALUE            = 1;
int     SX1280_PREAMBLE_LENGTH      = 4;
#endif  // USER_CONFIG_HPP
