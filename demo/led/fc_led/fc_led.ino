/*
 * フルカラーLEDのデモ
 * - ランダムに色を変化させる
 */

#define FADE_TIME 10

// LEDをつなぐピンを定義
int led_pins[] = {9, 10, 11};

void setup(){
  // 未使用のアナログで乱数の種を初期化
  randomSeed(analogRead(0));

  // LEDのピンを出力に
  int i;
  for (i=0; i<3; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {
  int i, j;

  // 乱数で使用するピンをデタラメにする
  for (j=0; j<3; j++) {
    led_pins[j] = random(9, 11);
  }

  // LEDを明から暗へフェード
  for (j=0; j<3; j++) {
    for (i=0; i<256; i++) {
      analogWrite(led_pins[j], i);
      delay(FADE_TIME);
    }
  }

  // LEDを暗から明へフェード
  for (j=0; j<3; j++) {
    for (i=255; i>-1; i--) {
      analogWrite(led_pins[j], i);
      delay(FADE_TIME);
    }
  }
}
