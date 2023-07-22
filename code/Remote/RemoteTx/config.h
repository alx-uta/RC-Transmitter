// Debug
bool enable_serial_print = true;

// Switch Button
#define button_switch_1 8
#define button_switch_2 9
#define button_switch_3 10
#define button_switch_4 11
#define button_switch_5 12

// Pot Switch Button
#define button_switch_pot_1 0
#define button_switch_pot_2 1
#define button_switch_pot_3 2
#define button_switch_pot_4 3
#define button_switch_pot_5 4
#define button_switch_pot_6 5

// ANO Rotary Encoder 1
#define rotary_encoder_1_left   9
#define rotary_encoder_1_up     10
#define rotary_encoder_1_right  11
#define rotary_encoder_1_down   12
#define rotary_encoder_1_center 13
#define rotary_encoder_1_enc_a  15
#define rotary_encoder_1_enc_b  14

//ANO Rotary Encoder 2
#define rotary_encoder_2_left   1
#define rotary_encoder_2_up     2
#define rotary_encoder_2_right  3
#define rotary_encoder_2_down   4
#define rotary_encoder_2_center 5
#define rotary_encoder_2_enc_a  7
#define rotary_encoder_2_enc_b  6

/**
 * Potentiometers
 */
#define POTENTIOMETER_1_ADC 0
#define POTENTIOMETER_2_ADC 1
#define POTENTIOMETER_3_ADC 2
#define POTENTIOMETER_4_ADC 3
#define POTENTIOMETER_5_ADC 4
#define POTENTIOMETER_6_ADC 5

// Set the sensitivity value
int pot_drift_value = 2;
int pot_min = 0;
int pot_max = 4093;
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
    joystick_drift_value = 10,
    joystick_min_out = 0,
    joystick_max_out = 255,
    joystick_default_value = 127,
    
    /**
     * Left Joystick
     */
    // Set the middle value
    left_joystick_middle_value_x = 1993,
    left_joystick_middle_value_y = 2134,

    // X1
    left_joystick_min_value_x = 231, //216
    left_joystick_max_value_x = 3757, //3772
    
    // Y1
    left_joystick_min_value_y = 683, //668
    left_joystick_max_value_y = 3589, //3604

    /**
     * Right Joystick
     */
    // X2
    right_joystick_middle_value_x = 2045,
    right_joystick_middle_value_y = 2004,

    // Y2
    right_joystick_min_value_x = 753, //738
    right_joystick_max_value_x = 3390, //3405
    
    // Max value X/Y
    right_joystick_min_value_y = 521, //506
    right_joystick_max_value_y = 3312; // 3327

// /*
//   SX1280 has the following connections:
//   NSS pin:   2
//   DIO1 pin:  26
//   NRST pin:  14
//   BUSY pin:  21
// */
 
// SX1280 radio = new Module(
//     2, 26, 14, 21
// );

// float frequency     = 2400.0;
// int bitRate         = 520;
// int codingRate      = 2;
// int outputPower     = 8;
// float dataShaping   = 1.0;
// uint8_t syncWord[]  = {
//     0x01,
//     0x01,
//     0x01,
//     0x01
// };
// int crcValue        = 0;
