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
    int state = radio.beginFLRC();

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
    state = radio.setFrequency(SX1280_FREQUENCY);
    state = radio.setBitRate(SX1280_BIT_RATE);
    state = radio.setCodingRate(SX1280_CODING_RATE);
    state = radio.setOutputPower(SX1280_OUTPUT_POWER);
    state = radio.setDataShaping(SX1280_DATA_SHAPING);
    state = radio.setSyncWord(SX1280_SYNC_WORD, 4);

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
    _payload = _TX.getByteArray();
    array_size = sizeof(_TX._payload.byteArray);
    state = radio.startTransmit(
        _payload, array_size
    );
}


/**
 * Feed the dog
 */
void feedTheDog() {
  TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed = 1;
  TIMERG0.wdt_wprotect = 0;
}