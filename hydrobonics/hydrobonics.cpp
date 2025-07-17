#define TdsSensorPin A0        // TDS على A0
#define WaterLevelPin A1       // مستوى الماء على A1
#define PhSensorPin A2         // pH على A2
#define PumpRelayPin 7         // ريليه المضخة على D7
#define TdsPowerPin 8          // نغذي حساس TDS من D8

float phOffset = 2.4;            // تعويض pH
int waterLevelThreshold = 300;   // عتبة المضخة

void setup() {
  Serial.begin(9600);
  pinMode(TdsSensorPin, INPUT);
  pinMode(WaterLevelPin, INPUT);
  pinMode(PhSensorPin, INPUT);
  pinMode(PumpRelayPin, OUTPUT);
  pinMode(TdsPowerPin, OUTPUT);
  digitalWrite(PumpRelayPin, LOW); // المضخة طافية بالبداية
}

void loop() {
  // ✅ تشغيل حساس TDS مؤقتًا
  digitalWrite(TdsPowerPin, HIGH);  // شغل TDS
  delay(500);  // انتظر يستقر
  int tdsAnalog = analogRead(TdsSensorPin);
  digitalWrite(TdsPowerPin, LOW);   // طفي TDS بعد القراءة

  float tdsVoltage = tdsAnalog * (5.0 / 1024.0);
  float tdsValue = (133.42 * tdsVoltage * tdsVoltage * tdsVoltage
                    - 255.86 * tdsVoltage * tdsVoltage
                    + 857.39 * tdsVoltage) * 0.5;

  delay(300); // فصل بين القراءات

  // قراءة pH بدون تداخل
  int phRaw = analogRead(PhSensorPin);
  float phVoltage = phRaw * (5.0 / 1023.0);
  float pH = 7 + ((2.5 - phVoltage) / 0.18) + phOffset;

  delay(200);

  // قراءة مستوى الماء
  int waterLevelRaw = analogRead(WaterLevelPin);

  // تحكم في المضخة
  bool pumpOn = waterLevelRaw < waterLevelThreshold;
  digitalWrite(PumpRelayPin, pumpOn ? LOW : HIGH);

  // الطباعة
  Serial.print("TDS: ");
  Serial.print(tdsValue, 0);
  Serial.print(" ppm | Water Level: ");
  Serial.print(waterLevelRaw);
  Serial.print(" | pH: ");
  Serial.print(pH, 2);
  Serial.print(" | Pump: ");
  Serial.println(pumpOn ? "ON" : "OFF");

  delay(500);
}
