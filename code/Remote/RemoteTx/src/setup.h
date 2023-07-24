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
  joystick.setSPIspeed(5000000);
  joystick.begin(MCP3208_CS_PIN_1);

  potentiometer.selectHSPI();
  potentiometer.setSPIspeed(5000000);
  potentiometer.begin(MCP3208_CS_PIN_0);
}

/**
 * MCP23S17T setup
 */
void MCP23S17T_setup() {
  MCP23S17T_SWITCHES.selectHSPI();
  MCP23S17T_SWITCHES.setSPIspeed(10000000);
  MCP23S17T_SWITCHES.begin();
  MCP23S17T_SWITCHES.pinMode16(0xFFFF);
  MCP23S17T_SWITCHES.setPullup16(0xFFFF);
  MCP23S17T_SWITCHES.setPolarity16(0xFFFF);


  MCP23S17T_ROTARY_ENCODERS.selectHSPI();
  MCP23S17T_ROTARY_ENCODERS.setSPIspeed(10000000);
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

// counter to keep track of transmitted packets
int count = 0;


/**
 * SX1280
 */
void SX1280_setup() {

  // initialize SX1280 with default settings
  Serial.print(F("[SX1280] Initializing ... "));
  int state = radio.beginFLRC();

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  state = radio.setFrequency(2410.5);
  state = radio.setBitRate(520);
  state = radio.setCodingRate(2);
  state = radio.setOutputPower(5);
  state = radio.setDataShaping(1.0);
  uint8_t syncWord[] = {0x01, 0x23, 0x45, 0x67};
  state = radio.setSyncWord(syncWord, 4);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print(F("Unable to set configuration, code "));
    Serial.println(state);
    while (true);
  }

  // set the function that will be called
  // when packet transmission is finished
  radio.setPacketSentAction(setFlag);

  // start transmitting the first packet
  Serial.print(F("[SX1280] Sending first packet ... "));
  // you can also transmit byte array up to 256 bytes long
  // byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
  //                   0x89, 0xAB, 0xCD, 0xEF};
  // state = radio.startTransmit(byteArr, 8);
  state = radio.startTransmit(payload.byteArray, sizeof(payload.byteArray));
    
}
