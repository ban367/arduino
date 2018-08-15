/*
 * ネオピクセルのデモ
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6 // 信号端子のピン番号
#define LED_NUM 20  // LEDの数

// LEDテープの制御IC
// WS2812 -> NEO_KHZ800
// WS2811 -> NEO_KHZ400
Adafruit_NeoPixel ledtape = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ledtape.begin();
  ledtape.show(); // 一旦全てOFFの状態で反映
}

void loop() {
  uint16_t i, j;

  // 順次色を変化させる
  for(j=0; j<256; j++) {
    // setPixelColor(n, red, green, blue);
    for(i=0; i<ledtape.numPixels(); i++) {
      ledtape.setPixelColor(i, rotateColor((((i) * 256 / ledtape.numPixels()) + j) & 255));
    }
    ledtape.show();
    delay(20);
  }
}

// RGBの色の移り変わり関数
uint32_t rotateColor(byte WheelPos) {
  if(WheelPos < 85) {
    return ledtape.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return ledtape.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return ledtape.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
