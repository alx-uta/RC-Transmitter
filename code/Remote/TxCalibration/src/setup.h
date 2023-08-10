/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */

/**
 * MCP3208 setup
 */
void MCP3208_setup() {
  pinMode(MCP3208_CS_PIN_0, OUTPUT);
  pinMode(MCP3208_CS_PIN_1, OUTPUT);
  digitalWrite(MCP3208_CS_PIN_0, HIGH);
  digitalWrite(MCP3208_CS_PIN_1, HIGH);
  
  joystick.selectHSPI();
  joystick.setSPIspeed(MCP3208_SPI_SPEED);
  joystick.begin(MCP3208_CS_PIN_1);

  potentiometer.selectHSPI();
  potentiometer.setSPIspeed(MCP3208_SPI_SPEED);
  potentiometer.begin(MCP3208_CS_PIN_0);
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

  // Ano Rotary Encoder #1
  left_encoder = new RotaryEncoder(
    MCP23S17T_ROTARY_ENCODERS.digitalRead(rotary_encoder_1_enc_a),
    MCP23S17T_ROTARY_ENCODERS.digitalRead(rotary_encoder_1_enc_b),
    RotaryEncoder::LatchMode::TWO03,
    false,
    false
  );
  // Ano Rotary Encoder #2
  right_encoder = new RotaryEncoder(
    MCP23S17T_ROTARY_ENCODERS.digitalRead(rotary_encoder_2_enc_a),
    MCP23S17T_ROTARY_ENCODERS.digitalRead(rotary_encoder_2_enc_b),
    RotaryEncoder::LatchMode::TWO03,
    false,
    false
  );
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
  Serial.print(F("[SX1280] Initializing ... "));
  int state = radio.beginFLRC();

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  state = radio.setFrequency(SX1280_FREQUENCY);
  state = radio.setBitRate(SX1280_BIT_RATE);
  state = radio.setCodingRate(SX1280_CODING_RATE);
  state = radio.setOutputPower(SX1280_OUTPUT_POWER);
  state = radio.setDataShaping(SX1280_DATA_SHAPING);
  state = radio.setSyncWord(SX1280_SYNC_WORD, 4);

  /**
   * @todo validate each part of the config
   */
  if (state != RADIOLIB_ERR_NONE and enable_serial_print) {
    Serial.print(F("Unable to set configuration, code "));
    Serial.println(state);
    while (true);
  }

  radio.setPacketSentAction(setFlag);

  /**
   * Start the connexion and transmit the first package
   */
  state = radio.startTransmit(
    payload.byteArray, sizeof(payload.byteArray)
  );
}
