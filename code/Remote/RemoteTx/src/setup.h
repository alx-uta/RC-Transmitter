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
  potentiometer = &MCP3208_CHIP_0; 
  joystick = &MCP3208_CHIP_1;
}

/**
 * MCP23S17T setup
 */
void MCP23S17T_setup() {
  // Switches Init
  MCP23S17T_SWITCHES.begin_SPI(MCP23S17T_CS_PIN_0, SCK_PIN, MISO_PIN, MOSI_PIN, MCP23S17T_ADDR_0);

  for (uint8_t i = 0; i < 16; i++) {
    MCP23S17T_SWITCHES.pinMode(i, INPUT_PULLUP);
  }

  // Rotary encoders Init
  MCP23S17T_ROTARY_ENCODERS.begin_SPI(MCP23S17T_CS_PIN_1, SCK_PIN, MISO_PIN, MOSI_PIN, MCP23S17T_ADDR_1);
  for (uint8_t i = 0; i < 16; i++) {
    MCP23S17T_ROTARY_ENCODERS.pinMode(i, INPUT_PULLUP);
  }

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
