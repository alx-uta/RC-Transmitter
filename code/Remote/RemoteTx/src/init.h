/**
 * Generic Pinout
 */
#define SCK_PIN   14
#define MISO_PIN  12
#define MOSI_PIN  13

/**
 * SX1280 Init
 */
#define SX1280_NSS  2
#define SX1280_DI01 26
#define SX1280_NRST 5
#define SX1280_BUSY 21

SX1280 radio = new Module(
  SX1280_NSS,
  SX1280_DI01,
  SX1280_NRST,
  SX1280_BUSY
);

// save transmission state between loops
int transmissionState = RADIOLIB_ERR_NONE;

/**
 * MCP3208 Init
 * 
 * This is used for reading the data 
 * from the Joysticks and Potentiometers
 */
// Potentiometers
#define MCP3208_CS_PIN_0 25
MCP3208 potentiometer;

// Joysticks
#define MCP3208_CS_PIN_1 27
MCP3208 joystick;

/**
 * MCP23S17T Init
 * 
 * This is used to read the switches,
 * the ON/OFF switch from the potentiometers
 * and the Ano Rotary Encoders
 * 
 */

// CS PIN and Address for the Switches
#define MCP23S17T_CS_PIN_0  22
#define MCP23S17T_ADDR_0    0x24
MCP23S17 MCP23S17T_SWITCHES(
  MCP23S17T_CS_PIN_0,
  MCP23S17T_ADDR_0
);

// CS PIN and Address for the Rotary Encoders
#define MCP23S17T_CS_PIN_1  4
#define MCP23S17T_ADDR_1    0x20
MCP23S17 MCP23S17T_ROTARY_ENCODERS(
  MCP23S17T_CS_PIN_1,
  MCP23S17T_ADDR_1
);

/**
 * Rotary encoder
 */
RotaryEncoder *left_encoder = nullptr;
RotaryEncoder *right_encoder = nullptr;

int16_t
  // Potentiometer Values
  pot1, pot2, pot3, pot4, pot5, pot6,
  
  // Potentiometer Current Value
  pot1Read, pot2Read, pot3Read, pot4Read, pot5Read, pot6Read,
  
  // Potentiometer Last Value
  pot1LastValue, pot2LastValue, pot3LastValue, pot4LastValue, pot5LastValue, pot6LastValue,
  
  // Potentiometer Switch Value
  potSwitch1, potSwitch2, potSwitch3, potSwitch4, potSwitch5, potSwitch6,
  
  // Switches
  switch1, switch2, switch3, switch4, switch5,
  
  // ANO Rotary Navigation - Left
  rotary1_up, rotary1_down, rotary1_left, rotary1_right, rotary1_center, rotary1_enc1, rotary1_enc2,
  
  // ANO Rotary Navigation - Right
  rotary2_up, rotary2_down, rotary2_left, rotary2_right, rotary2_center, rotary2_enc1, rotary2_enc2,

  // Joysticks
  joystick_x1, joystick_y1, joystick_x2, joystick_y2, joystick_x1_map, joystick_y1_map, joystick_x2_map, joystick_y2_map,
  
  // Encored pos
  left_encoder_pos  = 0,
  right_encoder_pos = 0;

/**
 * Define the tasks and cores
 */
static int taskCore1 = 0;
TaskHandle_t task_txReadData;

static int taskCore2 = 1;
TaskHandle_t task_txTransmitData;
