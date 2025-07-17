#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const int buttonPin = 2;
bool previousButtonState = HIGH;
bool isRunning = false;
bool directionForward = true; // اتجاه الدوران
// const int buttonPin = 2;
// bool previousButtonState = HIGH;
// bool isRunning = false;
// bool directionBackord = true;
void setup() {
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);

  stopServos();
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == LOW && previousButtonState == HIGH) {
    if (!isRunning) {
      Serial.println(directionForward ? "Starting rotation forward..." : "Starting rotation backward...");
      rotate360(directionForward);
      directionForward = !directionForward; // تبديل الاتجاه للمرة القادمة
      Serial.println("Rotation done.");
    }
  }

  previousButtonState = currentButtonState;
  delay(50);
}

void rotate360(bool forward) {
  isRunning = true;

  int speed1 = forward ? 180 : 0; // 180 للدوران للأمام، 0 للخلف
  int speed2 = forward ? 0 : 180; // 180 للدوران للأمام، 0 للخلف

  servo1.write(speed2);
  servo2.write(speed2);
  servo3.write(speed1);
  servo4.write(speed1);

  delay(1500); // زمن الدوران لدورة كاملة (ضبط حسب سرعة السيرفو)

  stopServos();

  isRunning = false;
}

void stopServos() {
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
}
