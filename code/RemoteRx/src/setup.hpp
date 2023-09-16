/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

/**
 * SX1280
 */
void SX1280_setup() {
    int state = radio.beginGFSK();
    #if ENABLE_SERIAL_PRINT
        #if ENABLE_RADIO_LIB_DEBUG
            if (state == RADIOLIB_ERR_NONE) {
                Serial.println(F("success!"));
            } else {
                Serial.print(F("failed, code "));
                Serial.println(state);
                while (true);
            }
        #endif
    #endif

    // @todo: run a check for each state
    state = radio.setOutputPower(SX1280_OUTPUT_POWER);
    state = radio.setGainControl(SX1280_GAIN_CONTROL);
    state = radio.setFrequency(SX1280_FREQUENCY);
    state = radio.setFrequencyDeviation(SX1280_FREQUENCY_DEVIATION);
    state = radio.setBitRate(SX1280_BIT_RATE);
    state = radio.setCodingRate(SX1280_CODING_RATE);
    state = radio.setDataShaping(SX1280_DATA_SHAPING);
    state = radio.setCRC(SX1280_CRC_VALUE);
    state = radio.setSyncWord(SX1280_SYNC_WORD, 4);
    state = radio.setPreambleLength(SX1280_PREAMBLE_LENGTH);

    #if ENABLE_SERIAL_PRINT
        #if ENABLE_RADIO_LIB_DEBUG
            if (state != RADIOLIB_ERR_NONE) {
                Serial.print(F("Unable to set configuration, code "));
                Serial.println(state);
                while (true);
            }
        #endif
    #endif

    radio.setDio1Action(setFlag);
    // start listening for FSK packets
    state = radio.startReceive();

    #if ENABLE_SERIAL_PRINT
        #if ENABLE_RADIO_LIB_DEBUG
            Serial.print(F("[SX1280] Starting to listen ... "));
            if (state == RADIOLIB_ERR_NONE) {
                Serial.println(F("success!"));
            } else {
                Serial.print(F("failed, code "));
                Serial.println(state);
                while (true);
            }
        #endif
    #endif
}

/**
 * SX1280 Data Receive
 */
void receiveData() {
    if(receivedFlag) {
      enableInterrupt = false;
  
      // reset flag
      receivedFlag = false;

      int state = radio.readData(_payload, _payload_size);
      if (state == RADIOLIB_ERR_NONE) {
        _RX.setData(
            _payload
        );
      }

    #if ENABLE_SERIAL_PRINT
        #if ENABLE_RADIO_LIB_DEBUG
            if (state == RADIOLIB_ERR_CRC_MISMATCH) {
                // packet was received, but is malformed
                Serial.println(F("CRC error!"));
            } else if {
                // some other error occurred
                Serial.print(F("failed, code "));
                Serial.println(state);
            }
        #endif

        #if ENABLE_DEBUG
            // Debug the payload
            for(int i=0; i < _payload_size; i++)
            {
                Serial.print(_payload[i]);
                if(i < _payload_size - 1) {
                    Serial.print(" : "); 
                }
            }
            Serial.println();
        #endif
    #endif
      radio.startReceive();
      enableInterrupt = true;
    }
}

void rxHopping() {
    current_time = millis();

    if ((
        current_time - last_switch_time
    ) >= SX1280_HOPPING_INTERNAL_MILLIS and current_frequency!=SX1280_TX_FREQUENCY) {
        
        // Move to the External TX Frequency
        current_frequency = SX1280_TX_FREQUENCY;
        radio.setFrequency(current_frequency);

        // Update last_switch_time to the current time to mark the last switch time
        last_switch_time = current_time;
    }

    if ((
        current_time - last_switch_time
    ) >= SX1280_TX_FREQUENCY_AVAILABILITY_MILLIS and current_frequency!=SX1280_FREQUENCY) {
        
        // Move to the TX Frequency
        current_frequency = SX1280_FREQUENCY;
        radio.setFrequency(current_frequency);

        // Update last_switch_time to the current time to mark the last switch time
        last_switch_time = current_time;
    }
}

/**
 * TFT setup
 */
void tft_setup() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(
        _RX_CONFIG.TFT_BACKGROUND
    );

    // Battery
    _TX_BATTERY.init(-1);
    _RX_BATTERY.init(-1);

    // Rotary Encoders
    _ENCODER_LEFT.init();
    _DISPLAY_POSITION_LEFT.init();

    _ENCODER_RIGHT.init();
    _DISPLAY_POSITION_RIGHT.init();

    // Joysticks
    _LEFT_JOYSTICK_X.init();
    _LEFT_JOYSTICK_Y.init();

    _RIGHT_JOYSTICK_Y.init();
    _RIGHT_JOYSTICK_X.init();

    // Potentiometers
    for (int i = 0; i < 6; i++) {
        pots[i].init();
    }

    // Switches
    for (int i = 0; i < 5; i++) {
        switches[i].init();
    }
}

/**
 * Feed the dog
 */
void feedTheDog() {
  TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed = 1;
  TIMERG0.wdt_wprotect = 0;
}