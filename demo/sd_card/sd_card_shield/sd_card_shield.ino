/*
 * SDカードシールドのデモ
 * - テキストファイルの読み書き
 */

#include <SD.h>

int mCount;

void setup() {
  // シリアル通信の初期化
  Serial.begin(9600);
  while (!Serial);

  // ピンを開く
  pinMode(10, OUTPUT); //Arduino unoの場合10番を開いておく必要がある。

  // SDカードの初期化処理（フォーマットではない）
  if (SD.begin(4)) { // 4番がSDカードシールドの番号
    // カードの初期化に失敗したかSDカードが挿入されていない場合
    Serial.println("Failed initialized.");
    return;
  }
  Serial.println("Success initialized.");

  mCount = 1;
}

void loop() {
  // temp.txtファイルの存在チェック
  if (SD.exists("temp.txt")) {
    Serial.println("File exists");

    // ファイルの書き込みオープン
    // ※temp.txtファイルがない場合は作成される。ある場合はファイルの最後に追加される。
    File fds = SD.open("temp.txt", FILE_WRITE);
    if (fds) {
      fds.write("test\r\n");
      Serial.print("test\r\n");
      fds.close();
    } else {
      Serial.println("Error file opening");
    }
  } else {
    Serial.println("File not exists");
  }

  mCount++;
  delay(1000);
}

