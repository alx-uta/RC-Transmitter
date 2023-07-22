// Debug
bool enable_serial_print = false;

// // MCP23S17T
// // #define MCP23X17_addr1 0x25
// // #define MCP23X17_addr2 0x26

// // // ads1115
// // #define ADS1115_addr1 0x48

// // //Switch Button
// // #define buttonSwitch_1 15
// // #define buttonSwitch_2 14
// // #define buttonSwitch_3 13
// // #define buttonSwitch_4 12
// // #define buttonSwitch_5 11

// // //Pot Switch Button
// // #define buttonSwitchPot_1 3
// // #define buttonSwitchPot_2 2
// // #define buttonSwitchPot_3 1
// // #define buttonSwitchPot_4 0
// // #define buttonSwitchPot_5 4
// // #define buttonSwitchPot_6 5

// // //Rotary 1 Buttons
// // #define rotary1_1 11
// // #define rotary1_2 12
// // #define rotary1_3 13
// // #define rotary1_4 14
// // #define rotary1_5 15
// // #define rotary1_enc_1 9
// // #define rotary1_enc_2 10

// // //Rotary 2 Buttons
// // #define rotary2_1 0
// // #define rotary2_2 1
// // #define rotary2_3 2
// // #define rotary2_4 3
// // #define rotary2_5 4
// // #define rotary2_enc_1 6
// // #define rotary2_enc_2 5

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
