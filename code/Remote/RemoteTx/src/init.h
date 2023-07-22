/**
 * Generic Pinout
 */
#define SCK_PIN   14
#define MISO_PIN  12
#define MOSI_PIN  13

/**
 * CS Pinout
 */
#define MCP3208_CS_PIN_0 25     // Potentiometers
#define MCP3208_CS_PIN_1 27     // Joysticks

#define MCP23S17T_CS_PIN_0  22  // Switches
#define MCP23S17T_CS_PIN_1  4   // Rotary Encoders

/**
 * MCP3208 Init
 * 
 * This is used for reading the data 
 * from the Joysticks and Potentiometers
 */
MCP3208 * potentiometer;
MCP3208 MCP3208_CHIP_0(
    SCK_PIN,
    MOSI_PIN,
    MISO_PIN,
    MCP3208_CS_PIN_0
);

MCP3208 * joystick;
MCP3208 MCP3208_CHIP_1(
    SCK_PIN,
    MOSI_PIN,
    MISO_PIN,
    MCP3208_CS_PIN_1
);

/**
 * MCP23S17T Init
 * 
 * This is used to read the switches,
 * the ON/OFF switch from the potentiometers
 * and the Ano Rotary Encoders
 * 
 */

// Address for the Switches
#define MCP23S17T_ADDR_0    0x24
Adafruit_MCP23X17 MCP23S17T_SWITCHES;

// Address for the Rotary Encoders
#define MCP23S17T_ADDR_1    0x20
Adafruit_MCP23X17 MCP23S17T_ROTARY_ENCODERS;

// /**
//  * Rotary encoder
//  */
// RotaryEncoder *encoder1 = nullptr;
// RotaryEncoder *encoder2 = nullptr;

// /**
//  * MCP23S17T
//  */

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
  
  // Encored pos
  pos,

  // Joysticks
  joystick_x1, joystick_y1, joystick_x2, joystick_y2, joystick_x1_map, joystick_y1_map, joystick_x2_map, joystick_y2_map;

// /**
//  * SX1280
//  */

// // flag to indicate that a packet was sent
// volatile bool transmittedFlag = false;

// // disable interrupt when it's not needed
// volatile bool enableInterrupt = true;
