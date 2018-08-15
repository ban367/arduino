/*
 * RFIDリーダー(RC522)のデモ
 * - ワンタッチで1回検出、再度タッチし直して再検出
 */

/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read new NUID from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 *
 * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 *
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool cardset;     // MFRC522にカードが検知されているかどうか
int timeoutcount; // MFRC522からカードが連続で離れた回数を記録

String uid_id = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522

  cardset = false;
  timeoutcount = 0;
}

void loop() {

  // カードの検出
  if (!mfrc522.PICC_IsNewCardPresent()) {
    // 検出されなかった場合の処理
    if (cardset) {
      // 検出後、タイムアウトと検出を繰り返すので対策
      if (timeoutcount > 4) {
        cardset = false;
        timeoutcount = 0;
        // Serial.println("離したときの処理");
      } else {
        // 4回以内なら連続未検出回数を増やす
        timeoutcount++;
      }
    } else {
    }
    delay(5);
    return;
  }

  // カードデータの読み込み
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // カードが初めてor改めてセットされた場合
  if (!cardset) {
    uid_id = "";
    // uidの読み込み
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      String uid_head = String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      String uid_main = String(mfrc522.uid.uidByte[i], HEX);

      uid_id.concat(uid_head);
      uid_id.concat(uid_main);
    }
    Serial.println(uid_id);
    cardset = true;
  }

  timeoutcount = 0;
  delay(100);
}
