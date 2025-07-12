#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int buttonPin = 2;
bool previousButtonState = HIGH;
bool sweeping = false;

void setup() {
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == LOW && previousButtonState == HIGH) {
    sweeping = !sweeping;

    if (sweeping) {
      sweepServosForward();
    } else {
      sweepServosBackward();
    }
  }

  previousButtonState = currentButtonState;
  delay(50); // Debounce
}

void sweepServosForward() {
  for (int pos = 0; pos <= 180; pos++) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    delay(30);
  }
}

void sweepServosBackward() {
  for (int pos = 180; pos >= 0; pos--) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    delay(30);
  }
}
