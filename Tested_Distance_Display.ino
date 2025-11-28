#include <LiquidCrystal.h>

// LCD: rs, en, d4, d5, d6, d7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  delay(800);
}

void loop() {
  // 触发一次测量
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 最多等 30ms
  float distance_cm = duration * 0.0343 / 2.0;

  // 串口方便对比
  Serial.print("Dist: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // LCD 显示
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist:");

  lcd.setCursor(6, 0);
  lcd.print(distance_cm, 1);   // 一位小数

  lcd.setCursor(0, 1);
  lcd.print("cm");

  delay(200);
}
