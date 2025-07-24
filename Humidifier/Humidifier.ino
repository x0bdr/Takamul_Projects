#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int humidifierPin = 7;
const int threshold = 500; // قيمة التغير بين القراءات
int16_t prev_ax = 0, prev_ay = 0, prev_az = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  pinMode(humidifierPin, OUTPUT);
  digitalWrite(humidifierPin, LOW);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 تم الاتصال بنجاح");
  } else {
    Serial.println("فشل في الاتصال بـ MPU6050");
  }

  // أول قراءة للتأسيس
  mpu.getAcceleration(&prev_ax, &prev_ay, &prev_az);
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // نحسب الفرق بين القراءة الحالية والسابقة
  int delta = abs(ax - prev_ax) + abs(ay - prev_ay) + abs(az - prev_az);

  Serial.print("قيمة التغير في الحركة: ");
  Serial.println(delta);

  if (delta > threshold) {
    Serial.println("تم الكشف عن حركة! تشغيل المرش...");
    digitalWrite(humidifierPin, HIGH);
    delay(10000); // تشغيل 2 ثانية
    digitalWrite(humidifierPin, LOW);
  }

  // تحديث القراءات السابقة
  prev_ax = ax;
  prev_ay = ay;
  prev_az = az;

  delay(300);
}
