/*
 * dfplayer_miniのデモ
 */

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

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

  myDFPlayer.volume(10);  // 音量の設定(0～30)
}

void loop() {
  myDFPlayer.play(1);
  delay(10000);
}
