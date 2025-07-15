const int moisturePin = A0;  // حساس الرطوبة
const int relayPin = 7;      // ريليه المضخة
int dryThreshold = 500;      // عتبة الجفاف (اضبطها حسب تجربتك)

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // طفي المضخة بالبداية
  Serial.begin(9600);
}

void loop() {
  int moistureValue = analogRead(moisturePin);
  Serial.print("Moisture Value: ");
  Serial.println(moistureValue);

  // عكسنا الشرط هنا 👇
  if (moistureValue > dryThreshold) {
    digitalWrite(relayPin, HIGH);  // التربة جافة -> شغل المضخة
    Serial.println("Soil is dry, pump ON");
  } else {
    digitalWrite(relayPin, LOW);   // التربة رطبة -> طفي المضخة
    Serial.println("Soil is wet, pump OFF");
  }

  delay(500);
}
