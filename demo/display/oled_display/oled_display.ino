/*
 * OLEDディスプレイのデモ
 * - 任意の文字列を表示
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// RSTピンがない互換品を使用するので-1を指定
Adafruit_SSD1306 display(-1);

void setup() {
  // I2Cアドレスは使用するディスプレイに合わせて変更する
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  // 画面表示をクリア
  display.clearDisplay();

  // テキストサイズを設定
  display.setTextSize(3);
  // テキスト色を設定
  display.setTextColor(WHITE);
  // テキストの開始位置を設定
  display.setCursor(0, 10);
  // 表示テキスト
  display.println("Hello");

  // 描画バッファの内容を画面に表示
  display.display();

  delay(1000);
}
