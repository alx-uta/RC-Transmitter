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
#define ENABLE_DEBUG            false
#define ENABLE_RADIO_LIB_DEBUG  false

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


// This needs to be the same as the Remote TX
float   SX1280_FREQUENCY                    = 2410; // Remote TX
float   SX1280_TX_FREQUENCY                 = 2420; // External TX
int     SX1280_FREQUENCY_DEVIATION          = 1500;
int     SX1280_BIT_RATE                     = 250;
int     SX1280_CODING_RATE                  = 5;
int     SX1280_OUTPUT_POWER                 = 8; // -18 to 13 dBm
int     SX1280_GAIN_CONTROL                 = 8; // 1 - 13
uint8_t SX1280_DATA_SHAPING                 = RADIOLIB_SHAPING_0_5;
uint8_t SX1280_SYNC_WORD[]                  = {0x01, 0x23, 0x45, 0x67};
int     SX1280_CRC_VALUE                    = 1;
int     SX1280_PREAMBLE_LENGTH              = 4;

int SX1280_HOPPING_INTERNAL_MILLIS          = 3000;
int SX1280_TX_FREQUENCY_AVAILABILITY_MILLIS = 5;
#endif  // USER_CONFIG_HPP
