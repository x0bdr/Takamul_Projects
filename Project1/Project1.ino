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

  pinMode(buttonPin, INPUT_PULLUP);  // ✅ إصلاح هنا
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // ✅ تم التعديل هنا: الزر مفعّل على LOW عند الضغط
  if (currentButtonState == LOW && previousButtonState == HIGH) {
    sweeping = !sweeping;

    if (sweeping) {
      sweepServos();  // Perform the sweep
    }
  }

  previousButtonState = currentButtonState;
  delay(50); // Debounce
}

void sweepServos() {
  for (int pos = 0; pos <= 180; pos++) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    delay(30);
  }

  for (int pos = 180; pos >= 0; pos--) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(pos);
    delay(30);
  }
}
