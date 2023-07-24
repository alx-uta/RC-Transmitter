/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */

/**
 * Read the data for the joysticks
 */
void readJoysticks() {
  joystick_x1 = joystick.analogRead(LEFT_JOYSTICK_X); // x left
  joystick_y1 = joystick.analogRead(LEFT_JOYSTICK_Y); // y left
  joystick_x2 = joystick.analogRead(RIGHT_JOYSTICK_X); // x right
  joystick_y2 = joystick.analogRead(RIGHT_JOYSTICK_Y); // y right

  // Left joystick
  joystick_x1_map = joystickMap(
    joystick_x1,
    left_joystick_min_value_x,
    left_joystick_max_value_x,
    left_joystick_middle_value_x,
    joystick_default_value,
    joystick_min_out,
    joystick_max_out
  );
  joystick_y1_map = joystickMap(
    joystick_y1,
    left_joystick_min_value_y,
    left_joystick_max_value_y,
    left_joystick_middle_value_y,
    joystick_default_value,
    joystick_min_out,
    joystick_max_out
  );

  // Right Joystick
  joystick_x2_map = joystickMap(
    joystick_x2,
    right_joystick_min_value_x,
    right_joystick_max_value_x,
    right_joystick_middle_value_x,
    joystick_default_value,
    joystick_min_out,
    joystick_max_out
  );
  joystick_y2_map = joystickMap(
    joystick_y2,
    right_joystick_min_value_y,
    right_joystick_max_value_y,
    right_joystick_middle_value_y,
    joystick_default_value,
    joystick_min_out,
    joystick_max_out
  );

  // Set the payload accounting for the drift value
  // Left Joystick
  payload.structure.j1x = (
    joystick_x1 > left_joystick_middle_value_x + joystick_drift_value || joystick_x1 < left_joystick_middle_value_x - joystick_drift_value
  ) ? joystick_x1_map : joystick_default_value;

   payload.structure.j1y = (
    joystick_y1 > left_joystick_middle_value_y + joystick_drift_value || joystick_y1 < left_joystick_middle_value_y - joystick_drift_value
  ) ? joystick_y1_map : joystick_default_value;
  
  // Right Joystick
  payload.structure.j2x = (
    joystick_x2 > right_joystick_middle_value_x + joystick_drift_value || joystick_x2 < right_joystick_middle_value_x - joystick_drift_value
  ) ? joystick_x2_map : joystick_default_value;
  
  payload.structure.j2y = (
    joystick_y2 > right_joystick_middle_value_y + joystick_drift_value || joystick_y2 < right_joystick_middle_value_y - joystick_drift_value
  ) ? joystick_y2_map : joystick_default_value;
}

/**
 * Read the data for the potentiometers
 */
void readPotentiometers() {
  // Potentiometer Values
  pot1Read = potentiometer.analogRead(POTENTIOMETER_1_ADC);
  pot2Read = potentiometer.analogRead(POTENTIOMETER_2_ADC);
  pot3Read = potentiometer.analogRead(POTENTIOMETER_3_ADC);
  pot4Read = potentiometer.analogRead(POTENTIOMETER_4_ADC);
  pot5Read = potentiometer.analogRead(POTENTIOMETER_5_ADC);
  pot6Read = potentiometer.analogRead(POTENTIOMETER_6_ADC);
  
  // Prevent jumping values
  pot1LastValue = ((pot1LastValue > pot1Read + pot_drift_value) || (pot1LastValue < pot1Read - pot_drift_value)) ? pot1Read : pot1LastValue;
  pot2LastValue = ((pot2LastValue > pot2Read + pot_drift_value) || (pot2LastValue < pot2Read - pot_drift_value)) ? pot2Read : pot2LastValue;
  pot3LastValue = ((pot3LastValue > pot3Read + pot_drift_value) || (pot3LastValue < pot3Read - pot_drift_value)) ? pot3Read : pot3LastValue;
  pot4LastValue = ((pot4LastValue > pot4Read + pot_drift_value) || (pot4LastValue < pot4Read - pot_drift_value)) ? pot4Read : pot4LastValue;
  pot5LastValue = ((pot5LastValue > pot5Read + pot_drift_value) || (pot5LastValue < pot5Read - pot_drift_value)) ? pot5Read : pot5LastValue;
  pot6LastValue = ((pot6LastValue > pot6Read + pot_drift_value) || (pot6LastValue < pot6Read - pot_drift_value)) ? pot6Read : pot6LastValue;

  // Set the payload
  payload.structure.p1 = map(pot1LastValue, pot_min, pot_max, pot_min, pot_out_max);
  payload.structure.p2 = map(pot2LastValue, pot_min, pot_max, pot_min, pot_out_max);
  payload.structure.p3 = map(pot3LastValue, pot_min, pot_max, pot_min, pot_out_max);
  payload.structure.p4 = map(pot4LastValue, pot_min, pot_max, pot_min, pot_out_max);
  payload.structure.p5 = map(pot5LastValue, pot_min, pot_max, pot_min, pot_out_max);
  payload.structure.p6 = map(pot6LastValue, pot_min, pot_max, pot_min, pot_out_max);
}

/**
 * Rotary Encoders
 */
void readRotaryEncoders() {
  uint16_t pinState = MCP23S17T_ROTARY_ENCODERS.read16();
  int left_encoder_direction  = 0;
  int right_encoder_direction = 0;
  payload.structure.re1_dir = 0;
  payload.structure.re2_dir = 0;

  // Get the direction and current position

  // Left
  left_encoder->tick(
    true,
    (pinState & (1 << rotary_encoder_1_enc_b)) != 0,
    (pinState & (1 << rotary_encoder_1_enc_a)) != 0
  );
  int left_encoder_new_pos = left_encoder->getPosition();

  if (left_encoder_pos != left_encoder_new_pos) {
    left_encoder_pos = left_encoder_new_pos;
    left_encoder_direction = (int)left_encoder->getDirection();
  }

  // Right
  right_encoder->tick(
    true,
    (pinState & (1 << rotary_encoder_2_enc_b)) != 0,
    (pinState & (1 << rotary_encoder_2_enc_a)) != 0
  );
  int right_encoder_new_pos = right_encoder->getPosition();

  if (right_encoder_pos != right_encoder_new_pos) {
    right_encoder_pos = right_encoder_new_pos;
    right_encoder_direction = (int)right_encoder->getDirection();
  }

  // Left
  payload.structure.re1_dir     = encoderDirection(left_encoder_direction);

  payload.structure.re1_pos_low = (byte)(left_encoder_new_pos);
  payload.structure.re1_pos_mid_low = (byte)(left_encoder_new_pos >> 8);
  payload.structure.re1_pos_mid_high = (byte)(left_encoder_new_pos >> 16);
  payload.structure.re1_pos_high = (byte)(left_encoder_new_pos >> 24);

  payload.structure.re1_left    = (pinState & (1 << rotary_encoder_1_left)) != 0;
  payload.structure.re1_up      = (pinState & (1 << rotary_encoder_1_up)) != 0;
  payload.structure.re1_right   = (pinState & (1 << rotary_encoder_1_right)) != 0;
  payload.structure.re1_down    = (pinState & (1 << rotary_encoder_1_down)) != 0;
  payload.structure.re1_center  = (pinState & (1 << rotary_encoder_1_center)) != 0;

  // Right
  payload.structure.re2_dir     = encoderDirection(right_encoder_direction);

  payload.structure.re2_pos_low = (byte)(right_encoder_new_pos);
  payload.structure.re2_pos_mid_low = (byte)(right_encoder_new_pos >> 8);
  payload.structure.re2_pos_mid_high = (byte)(right_encoder_new_pos >> 16);
  payload.structure.re2_pos_high = (byte)(right_encoder_new_pos >> 24);

  payload.structure.re2_left    = (pinState & (1 << rotary_encoder_2_left)) != 0;
  payload.structure.re2_up      = (pinState & (1 << rotary_encoder_2_up)) != 0;
  payload.structure.re2_right   = (pinState & (1 << rotary_encoder_2_right)) != 0;
  payload.structure.re2_down    = (pinState & (1 << rotary_encoder_2_down)) != 0;
  payload.structure.re2_center  = (pinState & (1 << rotary_encoder_2_center)) != 0;
}

/**
 * Switches
 */

void readSwitches() {
  uint16_t pinState = MCP23S17T_SWITCHES.read16();
  /**
   * Potentiometer Switch Button
   */
  payload.structure.p1s = (pinState & (1 << button_switch_pot_1)) != 0;
  payload.structure.p2s = (pinState & (1 << button_switch_pot_2)) != 0;
  payload.structure.p3s = (pinState & (1 << button_switch_pot_3)) != 0;
  payload.structure.p4s = (pinState & (1 << button_switch_pot_4)) != 0;
  payload.structure.p5s = (pinState & (1 << button_switch_pot_5)) != 0;
  payload.structure.p6s = (pinState & (1 << button_switch_pot_6)) != 0;

  /**
   * Switch Button
   */
  payload.structure.s1 = (pinState & (1 << button_switch_1)) != 0;
  payload.structure.s2 = (pinState & (1 << button_switch_2)) != 0;
  payload.structure.s3 = (pinState & (1 << button_switch_3)) != 0;
  payload.structure.s4 = (pinState & (1 << button_switch_4)) != 0;
  payload.structure.s5 = (pinState & (1 << button_switch_5)) != 0;
}
