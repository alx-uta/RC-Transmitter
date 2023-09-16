/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */

#include "display_number.hpp"

DisplayNumber::DisplayNumber(Config & config, TFT_eSPI & tft, int x, int y)
    :   _config(config),
        _tft(tft) {
            _x = x;
            _y = y;
        }

void DisplayNumber::init() {
    DisplayNumber::update(0);
}

void DisplayNumber::update(int number) {
  // Set text color and size
  _tft.setTextColor(number != 0 ? TFT_LIGHTGREY : TFT_DARKGREY);
  _tft.setTextSize(2);

  if (number != DisplayNumber::_old_value or not DisplayNumber::_widget_created) {
    DisplayNumber::_widget_created = true;

    // Calculate the number of digits
    int numDigits = max(8, int(log10(abs(number)) + 1));

    // Determine the width of each digit display area
    int digitWidth = 12;

    // Calculate the total width of the display area
    int displayWidth = digitWidth * 8;

    // Calculate the X-coordinate to center the number
    int centerX = DisplayNumber::_x + (displayWidth - numDigits * digitWidth) / 2;

    // Clear the display area with the background color
    _tft.fillRect(centerX, DisplayNumber::_y, displayWidth, 24, TFT_BLACK);

    // Print the new number
    _tft.setCursor(centerX, DisplayNumber::_y);
    if (numDigits <= 8) {
      if (number < 0) {
        _tft.print("-"); // Print the minus sign
        _tft.printf("%07d", abs(number)); // Display the absolute value with leading zeros
      } else {
        _tft.printf("%08d", number); // Display with leading zeros
      }
    } else {
      _tft.printf("%d", number); // Display without leading zeros
    }

    // Update the previousNumber for this display
    DisplayNumber::_old_value = number;
  }
}