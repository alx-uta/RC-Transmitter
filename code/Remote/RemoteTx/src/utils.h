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
    output = map(
      current_value, min_value, middle_value, out_min, default_value
    );
    if(output<out_min) {
      return out_min;
    }
  } else {
    output = map(
      current_value, middle_value, max_value, default_value, out_max
    );
    if(output>out_max) {
      return out_max;
    }
  }
  return output;
}

/**
 * Encoder direction
 * 0: NOROTATION
 * 1: COUNTERCLOCKWISE
 * 2: CLOCKWISE
 */
int encoderDirection(int direction) {
  return direction == 0 ? direction : (direction == 1 ? 2 : 1);
}

/**
 * Feed the dog
 */
void feedTheDog() {
  TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed = 1;
  TIMERG0.wdt_wprotect = 0;
}
