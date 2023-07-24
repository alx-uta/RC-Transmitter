/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */

typedef struct package {
  // Left Joystick
  byte j1x; // left-right
  byte j1y; // up-down

  // Right Joystick
  byte j2x; // left-right
  byte j2y; // up-down

  // Potentiometers - Values
  byte p1;
  byte p2;
  byte p3;
  byte p4;
  byte p5;
  byte p6;

  // Potentiometers - Switches
  byte p1s;
  byte p2s;
  byte p3s;
  byte p4s;
  byte p5s;
  byte p6s;
  
  // Switches
  byte s1;
  byte s2;
  byte s3;
  byte s4;
  byte s5;

  // Ano Rotary Encoder - Left
  byte re1_up;
  byte re1_down;
  byte re1_left;
  byte re1_right;
  byte re1_center;

  // Split re1_pos into individual bytes
  byte re1_pos_low;
  byte re1_pos_mid_low;
  byte re1_pos_mid_high;
  byte re1_pos_high;

  byte re1_dir;

  // Ano Rotary Encoder - Right
  byte re2_up;
  byte re2_down;
  byte re2_left;
  byte re2_right;
  byte re2_center;

  // Split re2_pos into individual bytes
  byte re2_pos_low;
  byte re2_pos_mid_low;
  byte re2_pos_mid_high;
  byte re2_pos_high;

  byte re2_dir;
};
const int union_size = sizeof(package);

typedef union btPacket_t{
    package structure;
    byte byteArray[union_size];
};

// Create a variable with the current structure
btPacket_t payload;
