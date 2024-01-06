/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

/**
 * MCP3208 setup
 */
void MCP3208_setup() {
    pinMode(TX_CONFIG.MCP3208_CS_PIN_0, OUTPUT);
    pinMode(TX_CONFIG.MCP3208_CS_PIN_1, OUTPUT);
    digitalWrite(TX_CONFIG.MCP3208_CS_PIN_0, HIGH);
    digitalWrite(TX_CONFIG.MCP3208_CS_PIN_1, HIGH);

    joystick.selectHSPI();
    joystick.setSPIspeed(MCP3208_SPI_SPEED);
    joystick.begin(TX_CONFIG.MCP3208_CS_PIN_1);

    potentiometer.selectHSPI();
    potentiometer.setSPIspeed(MCP3208_SPI_SPEED);
    potentiometer.begin(TX_CONFIG.MCP3208_CS_PIN_0);
}


/**
 * MCP23S17T setup
 */
void MCP23S17T_setup() {
    MCP23S17T_SWITCHES.selectHSPI();
    MCP23S17T_SWITCHES.setSPIspeed(MCP23S17T_SPI_SPEED);
    MCP23S17T_SWITCHES.begin();
    MCP23S17T_SWITCHES.pinMode16(0xFFFF);
    MCP23S17T_SWITCHES.setPullup16(0xFFFF);
    MCP23S17T_SWITCHES.setPolarity16(0xFFFF);


    MCP23S17T_ROTARY_ENCODERS.selectHSPI();
    MCP23S17T_ROTARY_ENCODERS.setSPIspeed(MCP23S17T_SPI_SPEED);
    MCP23S17T_ROTARY_ENCODERS.begin();
    MCP23S17T_ROTARY_ENCODERS.pinMode16(0xFFFF);
    MCP23S17T_ROTARY_ENCODERS.setPullup16(0xFFFF);
    MCP23S17T_ROTARY_ENCODERS.setPolarity16(0xFFFF);
}


// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;


// this function is called when a complete packet
// is transmitted by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif


void setFlag(void) {
  // we sent a packet, set the flag
  transmittedFlag = true;
}


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

    state = radio.setOutputPower(SX1280_OUTPUT_POWER);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setOutputPower:");Serial.println(state);
    #endif

    state = radio.setGainControl(SX1280_GAIN_CONTROL);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setGainControl:");Serial.println(state);
    #endif

    state = radio.setFrequency(SX1280_FREQUENCY);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setFrequency:");Serial.println(state);
    #endif

    state = radio.setFrequencyDeviation(SX1280_FREQUENCY_DEVIATION);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setFrequencyDeviation:");Serial.println(state);
    #endif

    state = radio.setBitRate(SX1280_BIT_RATE);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setBitRate:");Serial.println(state);
    #endif

    state = radio.setDataShaping(SX1280_DATA_SHAPING);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setDataShaping:");Serial.println(state);
    #endif

    state = radio.setCRC(SX1280_CRC_VALUE);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setCRC:");Serial.println(state);
    #endif

    state = radio.setSyncWord(SX1280_SYNC_WORD, SX1280_SYNC_WORD_LEN);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setSyncWord:");Serial.println(state);
    #endif

    state = radio.setPreambleLength(SX1280_PREAMBLE_LENGTH);
    #if ENABLE_RADIO_LIB_DEBUG
        Serial.print("setPreambleLength:");Serial.println(state);
    #endif

    #if ENABLE_SERIAL_PRINT
        #if ENABLE_RADIO_LIB_DEBUG
            if (state != RADIOLIB_ERR_NONE) {
                Serial.print(F("Unable to set configuration, code "));
                Serial.println(state);
                while (true);
            }
        #endif
    #endif

    radio.setPacketSentAction(setFlag);

    /**
     * Start the connexion and transmit the first package
     */
    uint8_t* payload_data = (uint8_t*)malloc(2);

    // Add the current config to the payload
    uint16_t config_encode = _TX.encodeStatusToByte(
        _TX.payload_config,
        16
    );
    payload_data[0] = (config_encode & 0xFF);
    payload_data[1] = (config_encode >> 8);

    transmissionState = radio.startTransmit(
        payload_data, 2
    );
    free(payload_data);
}

/**
 * SX1280 Data Transmit
 */
void transmitData() {
    // Check if the previous transmission finished
    if(transmittedFlag) {
        // reset flag
        transmittedFlag = false;
        _payload = _TX.getPayload();

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
                // Debug the new payload
                for(int i=0; i < _TX.current_payload_size; i++)
                {
                    Serial.print(_payload[i]);
                    if(i < _TX.current_payload_size - 1) {
                        Serial.print(" : "); 
                    }
                }
                Serial.print(" (");
                Serial.print(ESP.getFreeHeap());
                Serial.println(" bytes free)"); 

            #endif
        #endif

        transmissionState = radio.startTransmit(
            _payload, _TX.current_payload_size
        );
        // Free the memory
        free(_payload);
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