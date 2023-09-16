/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

Config _RX_CONFIG;

/**
 * RadioLib Init
 * 
 * This is used to transmit the data
 */
SX1280 radio = new Module(
  _RX_CONFIG.SX1280_NSS,
  _RX_CONFIG.SX1280_DI01,
  _RX_CONFIG.SX1280_NRST,
  _RX_CONFIG.SX1280_BUSY
);

// flag to indicate that a packet was received
volatile bool receivedFlag = false;

// disable interrupt when it's not needed
volatile bool enableInterrupt = true;

// this function is called when a complete packet
// is received by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  // check if the interrupt is enabled
  if(!enableInterrupt) {
    return;
  }

  // we got a packet, set the flag
  receivedFlag = true;
}

/**
 * Define the tasks and cores
 */
static int taskCore1 = 0;
TaskHandle_t task_txReceiveData;

static int taskCore2 = 1;
TaskHandle_t task_updateTFT;

/**
 * TFT init
 */
TFT_eSPI tft = TFT_eSPI();

// Battery Icons
BatteryIcon _TX_BATTERY(
    _RX_CONFIG, tft, 0, 0, 30
);
BatteryIcon _RX_BATTERY(
    _RX_CONFIG, tft, 290, 0, 30
);

// Rotary Encoder - Display Position
DisplayNumber _DISPLAY_POSITION_LEFT(
    _RX_CONFIG, tft, 25, 205
);
DisplayNumber _DISPLAY_POSITION_RIGHT(
    _RX_CONFIG, tft, 203, 205
);

// Joysticks
HorizontalSlider _LEFT_JOYSTICK_X(
    _RX_CONFIG, tft, 0, 0, 0, 255, 145
);
VerticalSlider _LEFT_JOYSTICK_Y(
    _RX_CONFIG, tft, 0, 0, 0, 255, 205, 40, 7, 5
);

HorizontalSlider _RIGHT_JOYSTICK_X(
    _RX_CONFIG, tft, 30 + 140, 0, 0, 255, 145
);
VerticalSlider _RIGHT_JOYSTICK_Y(
    _RX_CONFIG, tft, 313, 0, 0, 255, 205, 40, 7, 5
);

// Potentiometers
VerticalSlider _SLIDER_POT_1(
    _RX_CONFIG, tft, 30, 0, 255, 0, 90, 40, 7, 5
);
VerticalSlider _SLIDER_POT_2(
    _RX_CONFIG, tft, 45, 0, 255, 0, 90, 40, 7, 5
);
VerticalSlider _SLIDER_POT_3(
    _RX_CONFIG, tft, 60, 0, 255, 0, 90, 40, 7, 5
);
VerticalSlider _SLIDER_POT_4(
    _RX_CONFIG, tft, 75, 0, 255, 0, 90, 40, 7, 5
);
VerticalSlider _SLIDER_POT_5(
    _RX_CONFIG, tft, 147, 0, 255, 0, 190, 125, 7, 5
);
VerticalSlider _SLIDER_POT_6(
    _RX_CONFIG, tft, 162, 0, 255, 0, 190, 125, 7, 5
);

VerticalSlider pots[6] = {
    _SLIDER_POT_1,
    _SLIDER_POT_2,
    _SLIDER_POT_3,
    _SLIDER_POT_4,
    _SLIDER_POT_5,
    _SLIDER_POT_6
};

// Switches
Switch _S1(_RX_CONFIG, tft, 200, 40, 0);
Switch _S2(_RX_CONFIG, tft, 200, 40, 1);
Switch _S3(_RX_CONFIG, tft, 200, 40, 2);
Switch _S4(_RX_CONFIG, tft, 200, 40, 3);
Switch _S5(_RX_CONFIG, tft, 200, 40, 4);

Switch switches[5] = {
    _S1,
    _S2,
    _S3,
    _S4,
    _S5
};

// Rotary Encoder
RotaryEncoder _ENCODER_LEFT(_RX_CONFIG, tft, 72, 155);
RotaryEncoder _ENCODER_RIGHT(_RX_CONFIG, tft, 250, 155);

/**
 *
 * RX init
 */
Rx _RX(
    // Config
    _RX_CONFIG,
    
    // TFT Screen
    tft,
    
    // TX/RX Battery
    _TX_BATTERY,
    _RX_BATTERY,
    
    // Left Rotary Encoder
    _DISPLAY_POSITION_LEFT,
    _ENCODER_LEFT,

    // Right Rotary Encoder
    _DISPLAY_POSITION_RIGHT,
    _ENCODER_RIGHT,

    // Left Joystick
    _LEFT_JOYSTICK_X,
    _LEFT_JOYSTICK_Y,
    
    // Right Joystick
    _RIGHT_JOYSTICK_X,
    _RIGHT_JOYSTICK_Y,
    
    // Potentiometers
    _SLIDER_POT_1,
    _SLIDER_POT_2,
    _SLIDER_POT_3,
    _SLIDER_POT_4,
    _SLIDER_POT_5,
    _SLIDER_POT_6,

    // Switches
    _S1,
    _S2,
    _S3,
    _S4,
    _S5
);

const int _payload_size = 21;
uint8_t _payload[_payload_size];

/**
 * Frequency hopping settings
 */
float current_frequency;
unsigned long current_time;
unsigned long last_switch_time = millis();
