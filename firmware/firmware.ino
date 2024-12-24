#include <Joystick.h>

// Joystick object
Joystick_ Joystick;
// If true, disables the joystick and sends the input data to the serial monitor instead
const bool DEBUG_MODE = false;

void setup() {
  // Initialize objects
  if (DEBUG_MODE) {
    Serial.begin(9600);
  } else {
    Joystick.begin();
  }
}

void loop() {
  // Read the analog inputs and map the raw values to acceptable values for the Joystick object
  int accelerator = analogRead(A0);
  accelerator = log(accelerator - 45) * 50;
  accelerator = constrain(accelerator, 120, 330);
  accelerator = map(accelerator, 120, 330, 0, 1023);

  int brake = analogRead(A2);
  brake = log(brake - 45) * 50;
  brake = constrain(brake, 120, 330);
  brake = map(brake, 120, 330, 0, 1023);

  if (DEBUG_MODE) {
    // Print the raw input values in the serial monitor
    Serial.println();
    Serial.println("Raw analog inputs values:");
    Serial.println("Accelerator: " + (String)(analogRead(A0)));
    Serial.println("Brake: " + (String)(analogRead(A2)));
    delay(200);
  } else {
    // Set the mapped input values to the Joystick axes
    Joystick.setRxAxis(accelerator);
    Joystick.setRyAxis(brake);
  }
}
