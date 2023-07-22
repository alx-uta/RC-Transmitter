/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */

//#include <RadioLib.h>
#include <RotaryEncoder.h>
#include <Adafruit_MCP23X17.h>
#include <MCP3208.h>

// #include <Wire.h>

#include "config.h"
#include "src/utils.h"
#include "src/init.h"
#include "src/setup.h"
#include "src/package.h"
#include "src/default_package.h"
#include "src/read_data.h"

 static int taskCore1 = 0;
 static int taskCore2 = 1;
 TaskHandle_t task_txReadData;
 TaskHandle_t task_txTransmitData;

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
       * Read Rotary Encoders
       */
      readRotaryEncoders();

      /**
       * Switches Read
       */
      readSwitches();
    }
}

/**
* We'll use core:1 for payload transmission
*/
void func_txTransmitData( void * pvParameters ){
  while(true){
    
//     /*
//       Radio Transmit
//     */
//     if(transmittedFlag) {
//       enableInterrupt = false;
//       transmittedFlag = false;
//       radio.finishTransmit();
//       int state = radio.startTransmit(
//         payload.byteArray,
//         sizeof(
//           payload.byteArray
//         )
//       );
//       enableInterrupt = true;
//     }

//     if (enable_serial_print) {
//       Serial.print("[SX1280] Transmitting packet ( ");
//       Serial.print(
//         sizeof(
//           payload.byteArray
//         )
//       );
//       Serial.print(" ) ... ");
//       Serial.println("");
//     }
  }
}

void setup() {
  if(enable_serial_print) {
    Serial.begin(115200);
  }

  /**
   * Set the default values and 
   * create the structure for the payload
   */
  defaultValues();

  /**
   * MCP3208 Init
   */
  MCP3208_setup();

  /**
   * MCP23S17T setup
   */
  MCP23S17T_setup();

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
//
void loop() {
  // pass
}
