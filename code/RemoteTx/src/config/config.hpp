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

class Config {
	public:
		Config(
            // Joystick General
            uint8_t joystick_default_value,
            uint8_t joystick_min_out,
            uint8_t joystick_max_out,

            // Left Joystick
            uint8_t left_joystick_drift_value_x,
            int left_joystick_min_value_x,
            int left_joystick_max_value_x,
            int left_joystick_middle_value_x,

            uint8_t left_joystick_drift_value_y,
            int left_joystick_min_value_y,
            int left_joystick_max_value_y,
            int left_joystick_middle_value_y,

            // Right Joystick
            uint8_t right_joystick_drift_value_x,
            int right_joystick_min_value_x,
            int right_joystick_max_value_x,
            int right_joystick_middle_value_x,

            uint8_t right_joystick_drift_value_y,
            int right_joystick_min_value_y,
            int right_joystick_max_value_y,
            int right_joystick_middle_value_y,

            // Potentiometers
            uint8_t pot_drift_value,
            uint8_t pot_min,
            int pot_max,
            uint8_t pot_out_min,
            uint8_t pot_out_max
        );
        /**
         * Generic Pinout
         */
        uint8_t SCK_PIN     = 14;
        uint8_t MISO_PIN    = 12;
        uint8_t MOSI_PIN    = 13;

        /**
         * SX1280 Init
         */
        uint8_t SX1280_NSS  = 2;
        uint8_t SX1280_DI01 = 26;
        uint8_t SX1280_NRST = 5;
        uint8_t SX1280_BUSY = 21;

        /**
         * MCP23S17T
         */
        uint8_t MCP23S17T_CS_PIN_0  = 22;
        uint8_t MCP23S17T_ADDR_0    = 0x24;

        uint8_t MCP23S17T_CS_PIN_1 = 4;
        uint8_t MCP23S17T_ADDR_1 = 0x20;

        /**
         * MCP3208
         */
        uint8_t MCP3208_CS_PIN_0 = 25;
        uint8_t MCP3208_CS_PIN_1 = 27;

        // Switch Button
        uint8_t button_switch_1 = 0;
        uint8_t button_switch_2 = 1;
        uint8_t button_switch_3 = 2;
        uint8_t button_switch_4 = 3;
        uint8_t button_switch_5 = 4;

        // Pot Switch Button
        uint8_t button_switch_pot_1 = 8;
        uint8_t button_switch_pot_2 = 9;
        uint8_t button_switch_pot_3 = 10;
        uint8_t button_switch_pot_4 = 11;
        uint8_t button_switch_pot_5 = 12;
        uint8_t button_switch_pot_6 = 13;

        // ANO Rotary Encoder 1
        uint8_t rotary_encoder_1_left =   1;
        uint8_t rotary_encoder_1_up =     2;
        uint8_t rotary_encoder_1_right =  3;
        uint8_t rotary_encoder_1_down =   4;
        uint8_t rotary_encoder_1_center = 5;
        uint8_t rotary_encoder_1_enc_a =  7;
        uint8_t rotary_encoder_1_enc_b =  6;

        //ANO Rotary Encoder 2
        uint8_t rotary_encoder_2_left =   9;
        uint8_t rotary_encoder_2_up =     10;
        uint8_t rotary_encoder_2_right =  11;
        uint8_t rotary_encoder_2_down =   12;
        uint8_t rotary_encoder_2_center = 13;
        uint8_t rotary_encoder_2_enc_a =  15;
        uint8_t rotary_encoder_2_enc_b =  14;

        /**
         * Potentiometers
         */
        uint8_t POTENTIOMETER_1_ADC = 0;
        uint8_t POTENTIOMETER_2_ADC = 1;
        uint8_t POTENTIOMETER_3_ADC = 2;
        uint8_t POTENTIOMETER_4_ADC = 3;
        uint8_t POTENTIOMETER_5_ADC = 4;
        uint8_t POTENTIOMETER_6_ADC = 5;

        /**
         * Joysticks
         */
        uint8_t LEFT_JOYSTICK_X_1 =  0;
        uint8_t LEFT_JOYSTICK_X_2 =  1;

        uint8_t LEFT_JOYSTICK_Y_1 =  2;
        uint8_t LEFT_JOYSTICK_Y_2 =  3;

        uint8_t RIGHT_JOYSTICK_X_1 = 4;
        uint8_t RIGHT_JOYSTICK_X_2 = 5;

        uint8_t RIGHT_JOYSTICK_Y_1 = 6;
        uint8_t RIGHT_JOYSTICK_Y_2 = 7;

        // Joystick General
        uint8_t joystick_default_value;
        uint8_t joystick_min_out;
        uint8_t joystick_max_out;

        // Left Joystick
        uint8_t left_joystick_drift_value_x;
        int left_joystick_min_value_x;
        int left_joystick_max_value_x;
        int left_joystick_middle_value_x;

        uint8_t left_joystick_drift_value_y;
        int left_joystick_min_value_y;
        int left_joystick_max_value_y;
        int left_joystick_middle_value_y;

        // Right Joystick
        uint8_t right_joystick_drift_value_x;
        int right_joystick_min_value_x;
        int right_joystick_max_value_x;
        int right_joystick_middle_value_x;

        uint8_t right_joystick_drift_value_y;
        int right_joystick_min_value_y;
        int right_joystick_max_value_y;
        int right_joystick_middle_value_y;

        // Potentiometers
        uint8_t pot_drift_value;
        uint8_t pot_min;
        int pot_max;
        uint8_t pot_out_min;
        uint8_t pot_out_max;

        // Rotary encoders
        int encoder_min = -32768;
        int encoder_max = 32768;

        // @todo: allow a public function to change the config for: 
        // buttons, switches, rotary encoders, potentiometers, joysticks
	private:
};

#endif  // CONFIG_HPP
