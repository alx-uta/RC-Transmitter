/**
 * RC Transmitter – ESP32 / SX1280
 * https://github.com/alx-uta/RC-Transmitter
 * 
 * Alex Uta
 * microknot.dev
 */


/**
 * Current calibration options
 */
void availableCalibrationOptions() {
    Serial.println("....");

    Serial.println("1: Joysticks Drift & Center Value");
    Serial.println("2: Left Joystick: MIN Values");
    Serial.println("3: Left Joystick: MAX Values");
    Serial.println("4: Right Joystick: MIN Values");
    Serial.println("5: Right Joystick: MAX Values");
    Serial.println("6: Potentiometers Calibration");

    Serial.println("...");
}


/**
 * Joysticks Middle and Drift values
 */
void joysticksDriftMiddleValue() {
    const int numJoysticks = 2; // Number of joysticks

    // Define the pin configurations for each joystick [X, Y]
    int joystickPins_1[numJoysticks][2] = {
        {TX_CONFIG.LEFT_JOYSTICK_X_1, TX_CONFIG.LEFT_JOYSTICK_Y_1},
        {TX_CONFIG.RIGHT_JOYSTICK_X_1, TX_CONFIG.RIGHT_JOYSTICK_Y_1}
    };

    int joystickPins_2[numJoysticks][2] = {
        {TX_CONFIG.LEFT_JOYSTICK_X_2, TX_CONFIG.LEFT_JOYSTICK_Y_2},
        {TX_CONFIG.RIGHT_JOYSTICK_X_2, TX_CONFIG.RIGHT_JOYSTICK_Y_2}
    };

    long total_values[numJoysticks][2] = {}; // [total_X, total_Y]
    int min_values[numJoysticks][2] = {};    // [x_min, y_min]
    int max_values[numJoysticks][2] = {};    // [x_max, y_max]

    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        for (int j = 0; j < numJoysticks; j++) {
        int reading_X = (
            joystick.analogRead(joystickPins_1[j][0])+joystick.analogRead(joystickPins_2[j][0])
        ) / 2;
        int reading_Y = (
            joystick.analogRead(joystickPins_1[j][1])+joystick.analogRead(joystickPins_2[j][1])
        ) / 2;

        total_values[j][0] += reading_X;
        total_values[j][1] += reading_Y;

        min_values[j][0] = min(reading_X, min_values[j][0]);
        min_values[j][1] = min(reading_Y, min_values[j][1]);

        max_values[j][0] = max(reading_X, max_values[j][0]);
        max_values[j][1] = max(reading_Y, max_values[j][1]);
        }

        feedTheDog();
    }

    Serial.println("\nJoysticks Drift & Center Value:");
    Serial.println("Middle Value:");

    for (int j = 0; j < numJoysticks; j++) {
        Serial.print(j == 0 ? "Left Joystick:" : "Right Joystick:");
        Serial.print(" X: ");
        Serial.print(total_values[j][0] / CALIBRATION_READINGS);
        Serial.print(": Y: ");
        Serial.print(total_values[j][1] / CALIBRATION_READINGS);
        Serial.println();
    }

    Serial.println("\n");
    Serial.println("Drift Values:");

    for (int j = 0; j < numJoysticks; j++) {
        Serial.print(j == 0 ? "Left Joystick:" : "Right Joystick:");
        Serial.print(" X: ");
        Serial.print(max_values[j][0] - (total_values[j][0] / CALIBRATION_READINGS));
        Serial.print(": Y: ");
        Serial.print(max_values[j][1] - (total_values[j][1] / CALIBRATION_READINGS));
        Serial.println();
    }

    Serial.println("\n");
}

/**
 * Left Joystick - Min value
 */
void leftJoystickMin() {
    int max_value = joystick.maxValue();
    int x_min = max_value;
    int y_min = max_value;

    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        int reading_X = (
            joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_X_1) + joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_X_2)
        )/2;
        int reading_Y = (
            joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_Y_1) + joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_Y_2)
        )/2;

        x_min = min(x_min, reading_X);
        y_min = min(y_min, reading_Y);
    }

    Serial.println("\nLeft Joystick: MIN Values:");
    Serial.print("X: ");
    Serial.print(x_min);
    Serial.print(": Y: ");
    Serial.print(y_min);
    Serial.println("\n");
}

/**
 * Left Joystick - Max value
 */
void leftJoystickMax() {
    int x_max = 0;
    int y_max = 0;

    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        int reading_X = (
            joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_X_1)+joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_X_2)
        )/2;
        int reading_Y = (
            joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_Y_1)+joystick.analogRead(TX_CONFIG.LEFT_JOYSTICK_Y_2)
        )/2;

        x_max = max(x_max, reading_X);
        y_max = max(y_max, reading_Y);
    }

    Serial.println("\nLeft Joystick: MAX Values:");
    Serial.print("X: ");
    Serial.print(x_max);
    Serial.print(": Y: ");
    Serial.print(y_max);
    Serial.println("\n");
}

/**
 * Right Joystick - Min value
 */
void rightJoystickMin() {
    int max_value = joystick.maxValue();
    int x_min = max_value;
    int y_min = max_value;

    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        int reading_X = (
            joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_X_1)+joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_X_2)
        )/2;
        int reading_Y = (
            joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_Y_1)+joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_Y_2)
        )/2;

        x_min = min(x_min, reading_X);
        y_min = min(y_min, reading_Y);
    }

    Serial.println("\nRight Joystick: MIN Values:");
    Serial.print("X: ");
    Serial.print(x_min);
    Serial.print(": Y: ");
    Serial.print(y_min);
    Serial.println("\n");
}

/**
 * Right Joystick - Max value
 */
void rightJoystickMax() {
    int x_max = 0;
    int y_max = 0;

    for (int i = 0; i < CALIBRATION_READINGS; i++) {
        int reading_X = (
            joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_X_1)+joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_X_2)
        )/2;
        int reading_Y = (
            joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_Y_1)+joystick.analogRead(TX_CONFIG.RIGHT_JOYSTICK_Y_2)
        )/2;

        x_max = max(x_max, reading_X);
        y_max = max(y_max, reading_Y);
    }

    Serial.println("\nRight Joystick: MAX Values:");
    Serial.print("X: ");
    Serial.print(x_max);
    Serial.print(": Y: ");
    Serial.print(y_max);
    Serial.println("\n");
}


/**
 * Potentiometers Calibration
 */
void potentiometersCalibration() {
    int potentiometerPins[] = {
        TX_CONFIG.POTENTIOMETER_1_ADC,
        TX_CONFIG.POTENTIOMETER_2_ADC,
        TX_CONFIG.POTENTIOMETER_3_ADC,
        TX_CONFIG.POTENTIOMETER_4_ADC,
        TX_CONFIG.POTENTIOMETER_5_ADC,
        TX_CONFIG.POTENTIOMETER_6_ADC
    };

    int minPotOverall = INT_MAX; // Initialize with a large value

    for (int iteration = 0; iteration < CALIBRATION_READINGS; iteration++) {
        int minPotIteration = INT_MAX;

        for (int i = 0; i < 6; i++) {
            int potRead = potentiometer.analogRead(potentiometerPins[i]);
            minPotIteration = min(minPotIteration, potRead);
        }

        if (minPotIteration < minPotOverall) {
            minPotOverall = minPotIteration;
        }

        feedTheDog();
    }

    Serial.println("Potentiometers Calibration:");
    Serial.print("Min Value: ");
    Serial.println(minPotOverall);
    Serial.println();
}


void calibrationCheckOption() {
    if (Serial.available()) {
        char command = Serial.read();

        switch (command) {
            case '1':
            joysticksDriftMiddleValue();
            break;

            case '2':
            leftJoystickMin();
            break;

            case '3':
            leftJoystickMax();
            break;

            case '4':
            rightJoystickMin();
            break;

            case '5':
            rightJoystickMax();
            break;

            case '6':
            potentiometersCalibration();
            break;

            default:
            availableCalibrationOptions();
            break;
        }
    }
}
