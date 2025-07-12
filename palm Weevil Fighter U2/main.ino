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

  // قراءة مدة النبضة الراجعة
  duration = pulseIn(ECHO_PIN, HIGH);

  // حساب المسافة بالسنتيمتر
  distance = duration * 0.034 / 2;

  // طباعة المسافة في السيريال
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // إذا الجسم على بعد أقل من أو يساوي 1 متر
  if (distance > 0 && distance <= 20) {
    digitalWrite(LED_PIN, HIGH);  // تشغيل الليد

    // تشغيل نغمة متقطعة لمدة 5 ثواني (5 مرات × 1 ثانية)
    for (int i = 0; i < 5; i++) {
      tone(BUZZER_PIN, 1000);     // نغمة 1000 هرتز
      delay(500);                 // نصف ثانية صوت
      noTone(BUZZER_PIN);         // إيقاف الصوت
      delay(500);                 // نصف ثانية صمت
    }
  } else {
    // لا يوجد جسم قريب ➝ إطفاء الكل
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
  }

  delay(300); // وقت بسيط بين كل قراءة
}
