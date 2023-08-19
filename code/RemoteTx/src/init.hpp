/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

Config TX_CONFIG(
    // Joystick General
    joystick_default_value,
    joystick_min_out,
    joystick_max_out,

    // Left Joystick
    left_joystick_drift_value_x,
    left_joystick_min_value_x,
    left_joystick_max_value_x,
    left_joystick_middle_value_x,

    left_joystick_drift_value_y,
    left_joystick_min_value_y,
    left_joystick_max_value_y,
    left_joystick_middle_value_y,

    // Right Joystick
    right_joystick_drift_value_x,
    right_joystick_min_value_x,
    right_joystick_max_value_x,
    right_joystick_middle_value_x,

    right_joystick_drift_value_y,
    right_joystick_min_value_y,
    right_joystick_max_value_y,
    right_joystick_middle_value_y,

    // Potentiometers
    pot_drift_value,
    pot_min,
    pot_max,
    pot_out_max
);

/**
 * RadioLib Init
 * 
 * This is used to transmit the data
 */
SX1280 radio = new Module(
  TX_CONFIG.SX1280_NSS,
  TX_CONFIG.SX1280_DI01,
  TX_CONFIG.SX1280_NRST,
  TX_CONFIG.SX1280_BUSY
);


/**
 * MCP3208 Init
 * 
 * This is used for reading the data 
 * from the Joysticks and Potentiometers
 */
MCP3208 potentiometer;
MCP3208 joystick;


// save transmission state between loops
int transmissionState = RADIOLIB_ERR_NONE;


/**
 * MCP23S17T Init
 * 
 * This is used to read the switches,
 * the ON/OFF switch from the potentiometers
 * and the Ano Rotary Encoders
 * 
 */

// Switches
MCP23S17 MCP23S17T_SWITCHES(
  TX_CONFIG.MCP23S17T_CS_PIN_0,
  TX_CONFIG.MCP23S17T_ADDR_0
);

// Rotary Encoders
MCP23S17 MCP23S17T_ROTARY_ENCODERS(
  TX_CONFIG.MCP23S17T_CS_PIN_1,
  TX_CONFIG.MCP23S17T_ADDR_1
);

/**
 * Rotary encoder
 */
Rotary LEFT_ROTARY_ENCODER;
Rotary RIGHT_ROTARY_ENCODER;

/**
 * Define the tasks and cores
 */
static int taskCore1 = 0;
TaskHandle_t task_txReadData;

static int taskCore2 = 1;
TaskHandle_t task_txTransmitData;

Tx _TX(
    joystick,
    potentiometer,
    MCP23S17T_ROTARY_ENCODERS,
    MCP23S17T_SWITCHES,
    LEFT_ROTARY_ENCODER,
    RIGHT_ROTARY_ENCODER,
    TX_CONFIG
);

uint8_t* _payload;
int array_size;
