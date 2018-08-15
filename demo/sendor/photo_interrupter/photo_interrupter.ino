/*
 * フォトリフレクタのデモ
 */

#define REF_VAL 1000 // 反応させる閾値

void setup() {
  Serial.begin(9600);
}

void loop() {
  int ref_result = analogRead(A0);
  Serial.println(ref_result);

  if (REF_VAL > ref_result) {
    Serial.println("Hit");
  } else {
    Serial.println("No");
  }

  delay(50);
}
