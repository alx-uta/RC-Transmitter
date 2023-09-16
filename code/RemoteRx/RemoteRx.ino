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
#include <TFT_eSPI.h>
#include <SPI.h>
#include <RadioLib.h>

// Custom Files
#include "src/rx/rx.hpp"
#include "src/tft/widgets/display_number/display_number.hpp"
#include "src/tft/widgets/vertical_slider/vertical_slider.hpp"
#include "src/tft/widgets/horizontal_slider/horizontal_slider.hpp"
#include "src/tft/widgets/switch/switch.hpp"
#include "src/tft/widgets/rotary_encoder/rotary_encoder.hpp"
#include "src/tft/widgets/battery_icon/battery_icon.hpp"

// Init and other files
#include "src/init.hpp"
#include "src/setup.hpp"


/**
* We'll use core:0 for TFT update and RX hopping
*/
void func_updateTFT( void * pvParameters ){
    while(true){
        // TFT Update
        _RX.updateTftRemoteTX();

        /**
         * Radio Hopping
         */
        rxHopping();

        feedTheDog();
    }
}

/**
 * We'll use core:1 to receive the data
 */
void func_txReceiveData( void * pvParameters ){
    while(true){
        /**
         * Receive the data
         */
        receiveData();

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
     * TFT setup
     */
    tft_setup();

    /**
     * SX1280 setup
     */
    SX1280_setup();

    xTaskCreatePinnedToCore(
        func_txReceiveData,
        "task_txReceiveData",
        100 * 1024,
        NULL,
        20,
        &task_txReceiveData,
        taskCore1
    );

    xTaskCreatePinnedToCore(
        func_updateTFT,
        "task_updateTFT",
        100 * 1024,
        NULL,
        19,
        &task_updateTFT,
        taskCore2
    );

}


void loop() {
}
