// Debug
bool enable_serial_print = true;
bool enable_debug = true;

// Switch Button
#define button_switch_1 0
#define button_switch_2 1
#define button_switch_3 2
#define button_switch_4 3
#define button_switch_5 4

// Pot Switch Button
#define button_switch_pot_1 8
#define button_switch_pot_2 9
#define button_switch_pot_3 10
#define button_switch_pot_4 11
#define button_switch_pot_5 12
#define button_switch_pot_6 13

// ANO Rotary Encoder 1
#define rotary_encoder_1_left   1
#define rotary_encoder_1_up     2
#define rotary_encoder_1_right  3
#define rotary_encoder_1_down   4
#define rotary_encoder_1_center 5
#define rotary_encoder_1_enc_a  7
#define rotary_encoder_1_enc_b  6

//ANO Rotary Encoder 2
#define rotary_encoder_2_left   9
#define rotary_encoder_2_up     10
#define rotary_encoder_2_right  11
#define rotary_encoder_2_down   12
#define rotary_encoder_2_center 13
#define rotary_encoder_2_enc_a  15
#define rotary_encoder_2_enc_b  14

/**
 * Potentiometers
 */
#define POTENTIOMETER_1_ADC 0
#define POTENTIOMETER_2_ADC 1
#define POTENTIOMETER_3_ADC 2
#define POTENTIOMETER_4_ADC 3
#define POTENTIOMETER_5_ADC 4
#define POTENTIOMETER_6_ADC 5

/**
 * MCP3208
 */
#define MCP3208_SPI_SPEED 5000000

/**
 * MCP23S17T
 */
#define MCP23S17T_SPI_SPEED 10000000

// Set the sensitivity value
int pot_drift_value = 2;
int pot_min = 0;

// due to the speed we're losing some data
int pot_max = 4086;
int pot_out_max = 255;

/**
 * Joysticks
 */
#define LEFT_JOYSTICK_X  0
#define LEFT_JOYSTICK_Y  1
#define RIGHT_JOYSTICK_X 2
#define RIGHT_JOYSTICK_Y 3

int
    // General values
    joystick_drift_value = 20,
    joystick_min_out = 0,
    joystick_max_out = 255,
    joystick_default_value = 127,
    
    /**
     * Left Joystick
     */

    // Set the middle value
    left_joystick_middle_value_x = 0,
    left_joystick_middle_value_y = 0,

    // X1
    left_joystick_min_value_x = 0,
    left_joystick_max_value_x = 0,
    
    // Y1
    left_joystick_min_value_y = 0,
    left_joystick_max_value_y = 0,

    /**
     * Right Joystick
     */
    // X2
    right_joystick_middle_value_x = 0,
    right_joystick_middle_value_y = 0,

    // Y2
    right_joystick_min_value_x = 0,
    right_joystick_max_value_x = 0,
    
    // Max value X/Y
    right_joystick_min_value_y = 0,
    right_joystick_max_value_y = 0;

/**
 * SX1280
 */

float   SX1280_FREQUENCY        = 2410.5;
int     SX1280_BIT_RATE         = 520;
int     SX1280_CODING_RATE      = 2;
int     SX1280_OUTPUT_POWER     = 6;
float   SX1280_DATA_SHAPING     = 1.0;
uint8_t SX1280_SYNC_WORD[]      = {0x01, 0x23, 0x45, 0x67};
int     SX1280_CRC_VALUE        = 1;
