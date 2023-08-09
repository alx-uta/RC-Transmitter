// Debug
bool enable_serial_print = true;
bool enable_debug = true;

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
