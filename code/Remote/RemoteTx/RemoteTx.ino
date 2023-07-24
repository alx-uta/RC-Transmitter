/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

// Libraries
#include <SPI.h>
#include <RadioLib.h>
#include <MCP_ADC.h>
#include <RotaryEncoder.h>
#include <MCP23S17.h>

// Config & Init Files
#include "config.h"
#include "src/package.h"
#include "src/default_package.h"
#include "src/init.h"
#include "src/utils.h"

SX1280 radio = new Module(
  SX1280_NSS,
  SX1280_DI01,
  SX1280_NRST,
  SX1280_BUSY
);

#include "src/setup.h"
#include "src/read_data.h"

static int taskCore1 = 0;
static int taskCore2 = 1;
TaskHandle_t task_txReadData;
TaskHandle_t task_txTransmitData;

// save transmission state between loops
int transmissionState = RADIOLIB_ERR_NONE;

/**
 * We'll use core:0 to read 
 * the data from MCP3208 and MCP23S17T
 */
void func_txReadData( void * pvParameters ){
    while(true){
      /**
       * Read and set the values for the joysticks
       */
      readJoysticks();

      /**
       * Read and set the values for the potentiometers
       */
      readPotentiometers();

      /**
       * Switches Read
       */
      readSwitches();

      /**
       * Read Rotary Encoders
       */
      readRotaryEncoders();

      /**
       * Feed the dog
       */
      feedTheDog();
    }
}

/**
* We'll use core:1 for payload transmission
*/
void func_txTransmitData( void * pvParameters ){
  while(true){
    // check if the previous transmission finished
    if(transmittedFlag) {
      // reset flag
      transmittedFlag = false;

      if (transmissionState == RADIOLIB_ERR_NONE) {
        // packet was successfully sent
        Serial.println(F("transmission finished!"));

      } else {
        Serial.print(F("failed, code "));
        Serial.println(transmissionState);
      }

      // clean up after transmission is finished
      // this will ensure transmitter is disabled,
      // RF switch is powered down etc.
      radio.finishTransmit();

      // send another one
      Serial.print(F("[SX1280] Sending another packet ... "));
      Serial.print(" (");
      Serial.print(sizeof(payload.byteArray));
      Serial.print(") ");

      // you can transmit C-string or Arduino string up to
      // 256 characters long
      // String str = "Hello World! #" + String(count++);
      // transmissionState = radio.startTransmit(str);
      transmissionState = radio.startTransmit(payload.byteArray, sizeof(payload.byteArray));
    }
  }
}

void setup() {
  if(enable_serial_print) {
    Serial.begin(115200);
  }

  /**
   * SX1280 setup
   */
  SX1280_setup();

  /**
   * Set the default values and 
   * create the structure for the payload
   */
  defaultValues();

  /**
   * MCP23S17T setup
   */
  MCP23S17T_setup();

  /**
   * MCP3208 Init
   */
  MCP3208_setup();

  xTaskCreatePinnedToCore(
    func_txReadData,
    "task_txReadData",
    10000,
    NULL,
    4,
    &task_txReadData,
    taskCore1
  );

  xTaskCreatePinnedToCore(
    func_txTransmitData,
    "task_txTransmitData",
    10000,
    NULL,
    3,
    &task_txTransmitData,
    taskCore2
  );
}

void loop() {
}
