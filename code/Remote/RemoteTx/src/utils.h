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
