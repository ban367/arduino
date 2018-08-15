/*
 * 超音波距離センサーのデモ
 * - 温度考慮
 */

#define ECHO_PIN 2
#define TRIG_PIN 3

const float temp = 22.4; // 気温

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN,INPUT);
  pinMode(TRIG_PIN,OUTPUT);
}

void loop() {
  // 超音波の出力終了
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(1);
  // 超音波を出力
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(11);
  // 超音波を出力終了
  digitalWrite(TRIG_PIN, LOW);

  // 出力した超音波が返って来る時間を計測
  int t = pulseIn(ECHO_PIN, HIGH);

  // マイナス値を省く
  if (t > 0) {
    // 計測した時間と音速(気温を考慮)から反射物までの距離を計算
    float v = (331.5 + 0.6 * temp) / 10000; // 音速
    float distance = v * (t / 2); // 距離

    // 計算結果をシリアル通信で出力
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}