/*
 * 丁半システム
 * - 超音波距離センサーでカップの開け閉めを検知
 * - ダイスの目をOLEDディスプレイに表示
 */

/* OLEDディスプレイ設定 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1); // RSTピンがないので-1を指定

/* 超音波距離センサー設定 */
#define ECHO_PIN 3 // 入力ピン
#define TRIG_PIN 2 // 出力ピン

const float temp = 24; // 気温
const float v = (331.5 + 0.6 * temp) / 10000; // 音速

const int distance_tl = 11; // 最大検出距離[cm]
int distance; // 距離[cm]

// 余剰検出を省く
int scanCount = 0;
int scanCheckCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN,INPUT);
  pinMode(TRIG_PIN,OUTPUT);

  // 使用するディスプレイに応じて設定を変更
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  // OLED設定
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(15, 10);

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
    distance = v * t;

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
      // 表示テキスト
      display.println(String(random(1, 7)) + " | " + String(random(1, 7)));
      // 描画バッファの内容を画面に表示
      display.display();
    }
  }

  delay(5);
}
