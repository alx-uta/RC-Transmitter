/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

// ESP32 specific files
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

// User Custom Config
#include "user_config.hpp"

// Libraries
#include <SPI.h>
#include <RadioLib.h>
#include <MCP_ADC.h>
#include <MCP23S17.h>

// Local files
#include "src/rotary/rotary.hpp"
#include "src/tx/tx.hpp"
#include "src/init.hpp"
#include "src/setup.hpp"

#if ENABLE_CALIBRATION
    #include "src/calibration.hpp"
#endif

/**
* We'll use core:0 for payload transmission
*/
void func_txTransmitData( void * pvParameters ){
    while(true){
        transmitData();
        feedTheDog();
    }
}

/**
 * We'll use core:1 to read 
 * the data from MCP3208 and MCP23S17T
 */
void func_txReadData( void * pvParameters ){
    while(true){
        /**
         * Read the data
         */
        _TX.readData();

        /**
         * Feed the dog
         */
        feedTheDog();
    }
}

void setup() {
    #if ENABLE_SERIAL_PRINT
        Serial.begin(115200);
    #endif

    /**
     * SX1280 setup
     */
    SX1280_setup();

    /**
     * MCP23S17T setup
     */
    MCP23S17T_setup();

    /**
     * MCP3208 Init
     */
    MCP3208_setup();

    #if ENABLE_CALIBRATION
        availableCalibrationOptions();
    #else
        xTaskCreatePinnedToCore(
            func_txReadData,
            "task_txReadData",
            100 * 1024,
            NULL,
            20,
            &task_txReadData,
            taskCore1
        );

        xTaskCreatePinnedToCore(
            func_txTransmitData,
            "task_txTransmitData",
            100 * 1024,
            NULL,
            19,
            &task_txTransmitData,
            taskCore2
        );
    #endif
}

void loop() {
  #if ENABLE_CALIBRATION
    calibrationCheckOption();
  #endif
}
