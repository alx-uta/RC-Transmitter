// Debug
bool enable_serial_print = true;
bool enable_debug = true;

/**
 * MCP3208
 */
#define MCP3208_SPI_SPEED 4000000

/**
 * MCP23S17T
 */
#define MCP23S17T_SPI_SPEED 10000000

// Set the sensitivity value
int pot_drift_value = 2;
int pot_min = 0;

int pot_max = 4095 - pot_drift_value;
int pot_out_max = 255;

/**
 * Joysticks
 */

int
    // General values
    joystick_min_out = 0,
    joystick_max_out = 255,
    joystick_default_value = 127,

    /**
     * Left Joystick
     */

    // X
    left_joystick_drift_value_x = 0,
    left_joystick_min_value_x = 0,
    left_joystick_max_value_x = 0,
    left_joystick_middle_value_x = 0,
    
    // Y
    left_joystick_drift_value_y = 0,
    left_joystick_min_value_y = 0,
    left_joystick_max_value_y = 0,
    left_joystick_middle_value_y = 0,

    /**
     * Right Joystick
     */

    // Y
    right_joystick_drift_value_x = 0,
    right_joystick_min_value_x = 0,
    right_joystick_max_value_x = 0,
    right_joystick_middle_value_x = 0,
    
    // Max value X/Y
    right_joystick_drift_value_y = 0,
    right_joystick_min_value_y = 0,
    right_joystick_max_value_y = 0,
    right_joystick_middle_value_y = 0;

/**
 * SX1280
 */

float   SX1280_FREQUENCY        = 2410.5;
int     SX1280_BIT_RATE         = 520;
int     SX1280_CODING_RATE      = 2;
int     SX1280_OUTPUT_POWER     = 6;
float   SX1280_DATA_SHAPING     = 1.0;
uint8_t SX1280_SYNC_WORD[]      = {0x01, 0x23, 0x45, 0x67};
