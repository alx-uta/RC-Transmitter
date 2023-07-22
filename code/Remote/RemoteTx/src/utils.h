/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */

int joystickMap(
  int current_value,
  int min_value,
  int max_value,
  int middle_value,
  int default_value,
  int out_min,
  int out_max
) {
  int output;
  if (current_value < middle_value) {
    output = map(current_value, min_value, middle_value, out_min, default_value);
    if(output<out_min) {
      return out_min;
    }
  } else {
    output = map(current_value, middle_value, max_value, default_value, out_max);
    if(output>out_max) {
      return out_max;
    }
  }
  return output;
}

// // Enable the INPUT_PULLUP for the Potentiometers
// // void potentiometersInit() {
// //   pinMode(POTENTIOMETER_PIN1, INPUT_PULLUP);
// //   pinMode(POTENTIOMETER_PIN2, INPUT_PULLUP);
// //   pinMode(POTENTIOMETER_PIN3, INPUT_PULLUP);
// //   pinMode(POTENTIOMETER_PIN4, INPUT_PULLUP);
// //   pinMode(POTENTIOMETER_PIN5, INPUT_PULLUP);
// //   pinMode(POTENTIOMETER_PIN6, INPUT_PULLUP);
// // }

// // // Enable the INPUT_PULLUP for the MCP1
// // void mcp1Init() {
// //   mcp1.begin_I2C(MCP23X17_addr1);

// //   //  Switches
// //   mcp1.pinMode(buttonSwitch_1, INPUT_PULLUP);
// //   mcp1.pinMode(buttonSwitch_2, INPUT_PULLUP);
// //   mcp1.pinMode(buttonSwitch_3, INPUT_PULLUP);
// //   mcp1.pinMode(buttonSwitch_4, INPUT_PULLUP);
// //   mcp1.pinMode(buttonSwitch_5, INPUT_PULLUP);

// //   //  Rotary Switch 2 - Buttons
// //   mcp1.pinMode(rotary2_1, INPUT_PULLUP);
// //   mcp1.pinMode(rotary2_2, INPUT_PULLUP);
// //   mcp1.pinMode(rotary2_3, INPUT_PULLUP);
// //   mcp1.pinMode(rotary2_4, INPUT_PULLUP);
// //   mcp1.pinMode(rotary2_5, INPUT_PULLUP);

// //   //  Rotary Switch 2 - Encoder
// //   mcp1.pinMode(rotary2_enc_1, INPUT_PULLUP);
// //   mcp1.pinMode(rotary2_enc_2, INPUT_PULLUP);

// //   // Ano Rotary Encoder #2
// //   encoder2 = new RotaryEncoder(
// //     mcp1.digitalRead(rotary2_enc_1),
// //     mcp1.digitalRead(rotary2_enc_2),
// //     RotaryEncoder::LatchMode::TWO03,
// //     false,
// //     false
// //   );
// // }

// // // Enable the INPUT_PULLUP for the MCP2
// // void mcp2Init() {
// //   mcp2.begin_I2C(MCP23X17_addr2);

// //   mcp2.pinMode(buttonSwitchPot_1, INPUT_PULLUP);
// //   mcp2.pinMode(buttonSwitchPot_2, INPUT_PULLUP);
// //   mcp2.pinMode(buttonSwitchPot_3, INPUT_PULLUP);
// //   mcp2.pinMode(buttonSwitchPot_4, INPUT_PULLUP);
// //   mcp2.pinMode(buttonSwitchPot_5, INPUT_PULLUP);
// //   mcp2.pinMode(buttonSwitchPot_6, INPUT_PULLUP);

// //   // Rotary Switch 1 - Buttons
// //   mcp2.pinMode(rotary1_1, INPUT_PULLUP);
// //   mcp2.pinMode(rotary1_2, INPUT_PULLUP);
// //   mcp2.pinMode(rotary1_3, INPUT_PULLUP);
// //   mcp2.pinMode(rotary1_4, INPUT_PULLUP);
// //   mcp2.pinMode(rotary1_5, INPUT_PULLUP);

// //   // Rotary Switch 1 - Encoder
// //   mcp2.pinMode(rotary1_enc_1, INPUT_PULLUP);
// //   mcp2.pinMode(rotary1_enc_2, INPUT_PULLUP);

// //   // Ano Rotary Encoder #1
// //   encoder1 = new RotaryEncoder(
// //     mcp2.digitalRead(rotary1_enc_1),
// //     mcp2.digitalRead(rotary1_enc_2),
// //     RotaryEncoder::LatchMode::TWO03,
// //     false,
// //     false
// //   );
// // }

// #if defined(ESP8266) || defined(ESP32)
//   ICACHE_RAM_ATTR
// #endif
// void setFlag(void) {
//   // check if the interrupt is enabled
//   if(!enableInterrupt) {
//     return;
//   }

//   // we sent a packet, set the flag
//   transmittedFlag = true;
// }

// // sx1280 init
// void sx1280Init() {
// //   if(enable_serial_print) {
// //     Serial.print(F("[SX1280] Initializing ... ")); 
// //   }

// //   int state = radio.beginFLRC();

// //   state = radio.setFrequency(frequency);
// //   state = radio.setBitRate(bitRate);
// //   state = radio.setCodingRate(codingRate);
// //   state = radio.setOutputPower(outputPower);
// //   state = radio.setDataShaping(dataShaping);
// //   state = radio.setSyncWord(syncWord, 4);
// //   state = radio.setCRC(crcValue);

// //   radio.setDio1Action(setFlag);
// //   radio.startTransmit(payload.byteArray, sizeof(payload.byteArray));


// //   if(enable_serial_print) {
// //     if (state == RADIOLIB_ERR_NONE) {
// //       Serial.println(F("success!"));
// //     } else {
// //       Serial.print(F("failed, code "));
// //       Serial.println(state);
// //       while (true);
// //     }
// //   }
// }

// // // ads1115 init
// // void ads1115Init() {
// //   ads.setDataRate(RATE_ADS1115_860SPS);
// //   ads.setGain(GAIN_ONE);
// //   ads.begin(ADS1115_addr1);
// // }
