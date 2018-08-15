/*
 * 超音波距離センサーのデモ
 * - 検出範囲内に来た場合に一回のみ検出
 */

#define ECHO_PIN 2 // 入力ピン
#define TRIG_PIN 50 // 出力ピン

const float temp = 24; // 気温
const float v = (331.5 + 0.6 * temp) / 10000; // 音速

const int distance_tl = 81; // 最大検出距離[cm]
int distance; // 距離[cm]

// 余分に検出しないように
int scanCount = 0;
int scanCheckCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
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
  int t = pulseIn(ECHO_PIN, HIGH) / 2;

  // マイナス値を省く
  if (t > 0) {
    // 計測した時間と音速(気温を考慮)から反射物までの距離を計算
    distance = v * t; // 距離[cm]

    if (distance_tl > distance) {
      scanCount++;
      scanCheckCount = 0;
    } else {
      scanCheckCount++;
      if (scanCheckCount > 20) {
        scanCount = 0;
      }
    }

    if (scanCount == 2) {
      Serial.print(distance);
      Serial.println(" cm");
    }
  }

  delay(5);
}
