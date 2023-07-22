/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */

void defaultValues() {
  // Joystick - Left
  payload.structure.j1x = 127; // left-right
  payload.structure.j1y = 127; // up-down

  // Joystick - Right
  payload.structure.j2x = 127; // left-right
  payload.structure.j2y = 127; // up-down

  // Potentiometers
  payload.structure.p1 = 0;
  payload.structure.p2 = 0;
  payload.structure.p3 = 0;
  payload.structure.p4 = 0;
  payload.structure.p5 = 0;
  payload.structure.p6 = 0;

  // Potentiometers - Switches
  payload.structure.p1s = 0;
  payload.structure.p2s = 0;
  payload.structure.p3s = 0;
  payload.structure.p4s = 0;
  payload.structure.p5s = 0;
  payload.structure.p6s = 0;

  // Switches
  payload.structure.s1 = 0;
  payload.structure.s2 = 0;
  payload.structure.s3 = 0;
  payload.structure.s4 = 0;
  payload.structure.s5 = 0;

  // Ano Rotary Encoder - Left
  payload.structure.re1_up = 0;
  payload.structure.re1_down = 0;
  payload.structure.re1_left = 0;
  payload.structure.re1_right = 0;
  payload.structure.re1_center = 0;
  payload.structure.re1_dir = 0;

  // Ano Rotary Encoder - Right
  payload.structure.re2_up = 0;
  payload.structure.re2_down = 0;
  payload.structure.re2_left = 0;
  payload.structure.re2_right = 0;
  payload.structure.re2_center = 0;
  payload.structure.re2_dir = 0;
}
