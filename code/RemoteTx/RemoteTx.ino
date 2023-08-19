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
        // check if the previous transmission finished
        if(transmittedFlag) {
            // reset flag
            transmittedFlag = false;

            #if ENABLE_SERIAL_PRINT
                #if ENABLE_RADIO_LIB_DEBUG
                    if (transmissionState == RADIOLIB_ERR_NONE) {
                        // Serial.println(F("[SX1280] Packet transmitted successfully!"));
                    } else if (transmissionState == RADIOLIB_ERR_PACKET_TOO_LONG) {
                        Serial.println(F("[SX1280] Packet too long!"));
                    } else if (transmissionState == RADIOLIB_ERR_TX_TIMEOUT) {
                        Serial.println(F("[SX1280] Timed out while transmitting!"));
                    } else {
                        Serial.println(F("[SX1280] Failed to transmit packet, code "));
                        Serial.println(transmissionState);
                    }
                #endif

                #if ENABLE_DEBUG
                    // Debug the payload
                    _payload = _TX.getByteArray();
                    array_size = sizeof(_TX._payload.byteArray);
                    for(int i=0; i < array_size; i++)
                    {
                        Serial.print(_payload[i]);
                        if(i < array_size - 1) {
                            Serial.print(" : "); 
                        }
                    }
                    Serial.println();
                #endif
            #endif

            _payload = _TX.getByteArray();
            array_size = sizeof(_TX._payload.byteArray);
            transmissionState = radio.startTransmit(
                _payload, array_size
            );

        }
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
     * Set the default values and 
     * create the structure for the payload
     */
    _TX.defaultValues();

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
            0,
            &task_txReadData,
            taskCore1
        );

        xTaskCreatePinnedToCore(
            func_txTransmitData,
            "task_txTransmitData",
            100 * 1024,
            NULL,
            1,
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
