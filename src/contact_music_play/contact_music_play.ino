/*
 * dfplayer_miniの再生停止制御
 * - フォトリフレクタが塞がれたタイミングで音楽再生
 */

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// フォトリフレクター
#define REF_VAL 1000 // 反応させる閾値

#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(9600);

  // SoftwareSerialとDFPlayerの初期化
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    while(true);
  }
  myDFPlayer.volume(10); // 音量の設定(0～30)
}

void loop() {
  int ref_result = analogRead(A0);

  if (REF_VAL > ref_result) {
    myDFPlayer.play(1);
    delay(5000);
  }

  delay(5);
}
