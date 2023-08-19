/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#ifndef ROTARY_HPP
#define ROTARY_HPP

#define DIR_NONE 0x0

class Rotary
{
  public:
    // Process pin(s)
    unsigned char process(int, int);
    int encoderDirection(int pin1, int pin2);
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
};

#endif
