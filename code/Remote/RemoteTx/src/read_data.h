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
  joystick_x1 = joystick->readADC(0); // x left
  joystick_y1 = joystick->readADC(1); // y left
  joystick_x2 = joystick->readADC(2); // x right
  joystick_y2 = joystick->readADC(3); // y right

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

 Serial.println(payload.structure.j1x);

}

/**
 * Read the data for the potentiometers
 */
void readPotentiometers() {
  // Potentiometer Values
  pot1Read = potentiometer->readADC(POTENTIOMETER_1_ADC);
  pot2Read = potentiometer->readADC(POTENTIOMETER_2_ADC);
  pot3Read = potentiometer->readADC(POTENTIOMETER_3_ADC);
  pot4Read = potentiometer->readADC(POTENTIOMETER_4_ADC);
  pot5Read = potentiometer->readADC(POTENTIOMETER_5_ADC);
  pot6Read = potentiometer->readADC(POTENTIOMETER_6_ADC);
  
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

// void potentiometersSetData() {



//   /*
//     Potentiometer Switches
//   */
//   payload.structure.p1s = !mcp2.digitalRead(buttonSwitchPot_1);
//   payload.structure.p2s = !mcp2.digitalRead(buttonSwitchPot_2);
//   payload.structure.p3s = !mcp2.digitalRead(buttonSwitchPot_3);
//   payload.structure.p4s = !mcp2.digitalRead(buttonSwitchPot_4);
//   payload.structure.p5s = !mcp2.digitalRead(buttonSwitchPot_5);
//   payload.structure.p6s = !mcp2.digitalRead(buttonSwitchPot_6);
// }

// void switchesSetData() {
//   payload.structure.s1 = mcp1.digitalRead(buttonSwitch_1);
//   payload.structure.s2 = mcp1.digitalRead(buttonSwitch_2);
//   payload.structure.s3 = mcp1.digitalRead(buttonSwitch_3);
//   payload.structure.s4 = mcp1.digitalRead(buttonSwitch_4);
//   payload.structure.s5 = mcp1.digitalRead(buttonSwitch_5);
// }

// void anoRotaryEncoder2SetData() {
//   int encoder_direction = 0;

//   payload.structure.re2_up      = !mcp1.digitalRead(rotary2_2);
//   payload.structure.re2_down    = !mcp1.digitalRead(rotary2_4);
//   payload.structure.re2_left    = !mcp1.digitalRead(rotary2_3);
//   payload.structure.re2_right   = !mcp1.digitalRead(rotary2_5);
//   payload.structure.re2_center  = !mcp1.digitalRead(rotary2_1);

//   encoder2->tick(
//     mcp1.digitalRead(rotary2_enc_1),
//     mcp1.digitalRead(rotary2_enc_2)
//   );

//   int newPos = encoder2->getPosition();

//   payload.structure.re2_dir = 0;
//   if (pos != newPos) {
//     pos = newPos;
//     encoder_direction = (int)encoder2->getDirection();
//   }
//   payload.structure.re2_dir = encoder_direction;
// }

// void anoRotaryEncoder1SetData() {
//   int encoder_direction = 0;

//   encoder1->tick(
//     mcp2.digitalRead(rotary1_enc_1),
//     mcp2.digitalRead(rotary1_enc_2)
//   );
//   int newPos = encoder1->getPosition();

//   payload.structure.re1_dir = 0;
//   if (pos != newPos) {
//     pos = newPos;
//     encoder_direction = (int)encoder1->getDirection();
//   }
  
//   payload.structure.re1_dir     = encoder_direction;
//   payload.structure.re1_up      = !mcp2.digitalRead(rotary1_4);
//   payload.structure.re1_down    = !mcp2.digitalRead(rotary1_2);
//   payload.structure.re1_left    = !mcp2.digitalRead(rotary1_3);
//   payload.structure.re1_right   = !mcp2.digitalRead(rotary1_1);
//   payload.structure.re1_center  = !mcp2.digitalRead(rotary1_5);
// }
