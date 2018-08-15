/*
 * 圧力センサーのデモ
 */

#define VOL_PIN 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int result = analogRead(VOL_PIN);
  Serial.println(result);
  delay(500);
}
