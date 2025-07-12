#define TRIG_PIN 10
#define ECHO_PIN 9
#define BUZZER_PIN 5
#define LED_PIN 13

long duration;
float distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // إرسال نبضة
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // قراءة النبضة الراجعة
  duration = pulseIn(ECHO_PIN, HIGH);

  // حساب المسافة بالسنتيمتر
  distance = duration * 0.034 / 2;

  // طباعة المسافة في Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // إذا المسافة أقل من أو تساوي 10 سم ➝ شغّل البازر والليد
  if (distance > 0 && distance <= 10) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  delay(200); // تحديث كل 0.2 ثانية
}
