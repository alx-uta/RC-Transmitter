/**
 * Esp32 custom RC Transmitter
 * https://github.com/MicroKnot-dev/RC-Transmitter/
 * 
 * Alex Uta
 * microknot.dev
 */
// ESP32 specific files
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

// Libraries
#include <SPI.h>
#include <RadioLib.h>
#include <MCP_ADC.h>
#include <RotaryEncoder.h>
#include <MCP23S17.h>

// Config & Init Files
#include "user_config.h"
#include "src/config.h"
#include "src/utils.h"
#include "src/package.h"
#include "src/default_package.h"
#include "src/init.h"
#include "src/setup.h"
#include "src/read_data.h"

int numReadings = 100;

void setup() {
  Serial.begin(115200);

  /**
   * MCP3208 Init
   */
  MCP3208_setup();

  available_options();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case '1':
        joysticks_drift_middle_value();
        break;

      case '2':
        left_joystick_min();
        break;

      case '3':
        left_joystick_max();
        break;

      case '4':
        right_joystick_min();
        break;

      case '5':
        right_joystick_max();
        break;

      case '6':
        potentiometers_calibration();
        break;

      default:
        available_options();
        break;
    }
  }
}

void available_options() {
    Serial.println("....");

    Serial.println("1: Joysticks Drift & Center Value");
    Serial.println("2: Left Joystick: MIN Values");
    Serial.println("3: Left Joystick: MAX Values");
    Serial.println("4: Right Joystick: MIN Values");
    Serial.println("5: Right Joystick: MAX Values");
    Serial.println("6: Potentiometers Calibration");

    Serial.println("...");
}

void joysticks_drift_middle_value() {
  int max_value = joystick.maxValue();
  int x1_min=max_value,
      x1_max=0,
      y1_min=max_value,
      y1_max=0,
      x2_min=max_value,
      x2_max=0,
      y2_min=max_value,
      y2_max=0;

  long total_X1 = 0;
  long total_Y1 = 0;
  long total_X2 = 0;
  long total_Y2 = 0;
  for (int i = 0; i < numReadings; i++) {
    int reading_X1 = joystick.analogRead(LEFT_JOYSTICK_X);
    int reading_Y1 = joystick.analogRead(LEFT_JOYSTICK_Y);
    int reading_X2 = joystick.analogRead(RIGHT_JOYSTICK_X);
    int reading_Y2 = joystick.analogRead(RIGHT_JOYSTICK_Y);

    // Set the max
    x1_max = reading_X1>x1_max ? reading_X1 : x1_max;
    x2_max = reading_X2>x2_max ? reading_X2 : x2_max;
    y1_max = reading_Y1>y1_max ? reading_Y1 : y1_max;
    y2_max = reading_Y2>y2_max ? reading_Y2 : y2_max;
    
    x1_min = reading_X1 < x1_min ? reading_X1 : x1_min;
    x2_min = reading_X2 < x2_min ? reading_X2 : x2_min;
    y1_min = reading_Y1 < y1_min ? reading_Y1 : y1_min;
    y2_min = reading_Y2 < y2_min ? reading_Y2 : y2_min;

    total_X1 += reading_X1;
    total_Y1 += reading_Y1;
    total_X2 += reading_X2;
    total_Y2 += reading_Y2;
    feedTheDog();
  }
  int x1_drift = x1_max-x1_min;
  int x2_drift = x2_max-x2_min;
  int y1_drift = y1_max-y1_min;
  int y2_drift = y2_max-y2_min;

  Serial.println("\nJoysticks Drift & Center Value:");
  Serial.println("Middle Value:");
  Serial.print("X1: ");
  Serial.print(total_X1 / numReadings);
  Serial.print(": Y1: ");
  Serial.print(total_Y1 / numReadings);
  Serial.print(": X2: ");
  Serial.print(total_X2 / numReadings);
  Serial.print(": Y2: ");
  Serial.print(total_Y2 / numReadings);

  Serial.println("\n");
  Serial.println("Drift Values:");
  Serial.print("X1: ");
  Serial.print(x1_drift);
  Serial.print(": Y1: ");
  Serial.print(y1_drift);
  Serial.print(": X2: ");
  Serial.print(x2_drift);
  Serial.print(": Y2: ");
  Serial.print(y2_drift);

  Serial.println("\n");
}

void left_joystick_min() {
  int max_value = joystick.maxValue();
  int x_min=max_value,
      y_min=max_value;

  for (int i = 0; i < numReadings; i++) {
    int reading_X = joystick.analogRead(LEFT_JOYSTICK_X);
    int reading_Y = joystick.analogRead(LEFT_JOYSTICK_Y);

    x_min = reading_X < x_min ? reading_X : x_min;
    y_min = reading_Y < y_min ? reading_Y : y_min;
  }

  Serial.println("\nLeft Joystick: MIN Values:");
  Serial.print("X: ");
  Serial.print(x_min);
  Serial.print(": Y: ");
  Serial.print(y_min);
  Serial.println("\n");
}

void left_joystick_max() {
  int x_max=0,
      y_max=0;

  for (int i = 0; i < numReadings; i++) {
    int reading_X = joystick.analogRead(LEFT_JOYSTICK_X);
    int reading_Y = joystick.analogRead(LEFT_JOYSTICK_Y);

    x_max = reading_X > x_max ? reading_X : x_max;
    y_max = reading_Y > y_max ? reading_Y : y_max;
  }

  Serial.println("\nLeft Joystick: MAX Values:");
  Serial.print("X: ");
  Serial.print(x_max);
  Serial.print(": Y: ");
  Serial.print(y_max);
  Serial.println("\n");
}

void right_joystick_min() {
  int max_value = joystick.maxValue();
  int x_min=max_value,
      y_min=max_value;

  for (int i = 0; i < numReadings; i++) {
    int reading_X = joystick.analogRead(RIGHT_JOYSTICK_X);
    int reading_Y = joystick.analogRead(RIGHT_JOYSTICK_Y);

    x_min = reading_X < x_min ? reading_X : x_min;
    y_min = reading_Y < y_min ? reading_Y : y_min;
  }

  Serial.println("\nRight Joystick: MIN Values:");
  Serial.print("X: ");
  Serial.print(x_min);
  Serial.print(": Y: ");
  Serial.print(y_min);
  Serial.println("\n");
}

void right_joystick_max() {
  int x_max=0,
      y_max=0;

  for (int i = 0; i < numReadings; i++) {
    int reading_X = joystick.analogRead(RIGHT_JOYSTICK_X);
    int reading_Y = joystick.analogRead(RIGHT_JOYSTICK_Y);

    x_max = reading_X > x_max ? reading_X : x_max;
    y_max = reading_Y > y_max ? reading_Y : y_max;
  }

  Serial.println("\nRight Joystick: MAX Values:");
  Serial.print("X: ");
  Serial.print(x_max);
  Serial.print(": Y: ");
  Serial.print(y_max);
  Serial.println("\n");
}

/**
 * Simple Potentiometers Calibration
 */
void potentiometers_calibration() {
  int maxPotOverall = 0;
  int maxPotIteration = 0;

  for (int iteration = 0; iteration < numReadings; iteration++) {
    pot1Read = potentiometer.analogRead(POTENTIOMETER_1_ADC);
    pot2Read = potentiometer.analogRead(POTENTIOMETER_2_ADC);
    pot3Read = potentiometer.analogRead(POTENTIOMETER_3_ADC);
    pot4Read = potentiometer.analogRead(POTENTIOMETER_4_ADC);
    pot5Read = potentiometer.analogRead(POTENTIOMETER_5_ADC);
    pot6Read = potentiometer.analogRead(POTENTIOMETER_6_ADC);

    maxPotIteration = max(max(max(max(max(pot1Read, pot2Read), pot3Read), pot4Read), pot5Read), pot6Read);
    if (maxPotIteration > maxPotOverall) {
        maxPotOverall = maxPotIteration;
    }

    feedTheDog();
  }
  Serial.println("\nPotetiometers Calibration:");
  Serial.print("Max Value: ");
  Serial.print(maxPotOverall);
  Serial.println("\n");
}
