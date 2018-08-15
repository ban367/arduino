/*
 * ネオピクセルのデモ
 * - 単色発光
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6       // 信号端子のピン番号
#define LED_NUM 20  // LEDの数

// LEDテープの制御IC
// WS2812 -> NEO_KHZ800
// WS2811 -> NEO_KHZ400
Adafruit_NeoPixel ledtape = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ledtape.begin();
  ledtape.show();   // 一旦全てOFFの状態で反映
}

void loop() {
  for(uint16_t i=0; i<ledtape.numPixels(); i++) {
    // setPixelColor(n, red, green, blue);
    ledtape.setPixelColor(i, 255, 0, 220);
  }
  // ledtape.setBrightness(64); // 輝度
  ledtape.show();
  delay(20);
}
