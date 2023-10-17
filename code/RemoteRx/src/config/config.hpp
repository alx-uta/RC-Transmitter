/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Arduino.h"
#include <TFT_eSPI.h>

class Config {
	public:
		Config();
        /**
         * Generic Pinout
         */
        uint8_t SCK_PIN     = 14;
        uint8_t MISO_PIN    = 12;
        uint8_t MOSI_PIN    = 13;

        /**
         * Battery Voltage Monitor
         */
        uint8_t VOLTAGE_MONITOR_PIN  = 35;

        /**
         * SX1280 Init
         */
        uint8_t SX1280_NSS  = 2;
        uint8_t SX1280_DI01 = 26;
        uint8_t SX1280_NRST = 5;
        uint8_t SX1280_BUSY = 21;

        /**
         * TFT
         */
        uint16_t TFT_BACKGROUND      = TFT_BLACK;
        uint16_t TFT_SWITCH_ON       = TFT_GREEN;
        uint16_t TFT_SWITCH_OFF      = TFT_RED;
        uint16_t TFT_SWITCH_DISABLED = TFT_DARKGREY;

        uint16_t TFT_ENCODER_BORDER_COLOUR = TFT_DARKGREY;
        uint16_t TFT_ENCODER_FILL_COLOUR   = TFT_DARKGREY;
        uint16_t TFT_ENCODER_ACTIV_COLOUR  = TFT_GREEN;

        uint8_t pot_min = 0;
        uint8_t pot_max = 255;
        uint8_t joystick_min = 0;
        uint8_t joystick_max = 255;

        float SX1280_FREQUENCY;
        float CURRENT_FREQUENCY;
	private:
};

#endif  // CONFIG_HPP
