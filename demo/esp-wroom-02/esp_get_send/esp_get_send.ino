/*
 * ESP-WROOM-02のデモ
 * - ArduinoからGETで送信
 */

// WeeESP8266
// https://github.com/itead/ITEADLIB_Arduino_WeeESP8266

// 参考サイト
// http://nn-hokuson.hatenablog.com/entry/2017/04/09/091148

#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID "SSID"
#define PASSWORD "PASS"
#define HOST_NAME "192.168.0.1"

int n = 0; // デバック用
char sendStr[256];

#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial mySerial(RX_PIN, TX_PIN);
ESP8266 wifi(mySerial);

void setup(void)
{
  Serial.begin(9600);

  while(1) {
    if (wifi.setOprToStation()) {
      Serial.println("to station ok");
      break;
    } else {
      Serial.println("to station error");
      Serial.println("retrying...");
      delay(5000);
    }
  }

  while(1) {
    if (wifi.joinAP(SSID, PASSWORD)) {
      Serial.println("connect success");
      break;
    } else {
      Serial.println("connect error");
      Serial.println("retrying...");
      delay(5000);
    }
  }

  while(1) {
    if (wifi.disableMUX()) {
      Serial.println("disable mux success");
      break;
    } else {
      Serial.println("disable mux error");
      Serial.println("retrying...");
      delay(5000);
    }
  }

  Serial.println("--- setup complete ---");
}

void loop(void)
{
  // TCPで接続
  wifi.createTCP(HOST_NAME, 80);

  char data[128] = "abcd1234";

  // GET
  sprintf(sendStr, "GET /?data=%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: arduino\r\n\r\n", data, HOST_NAME);

  if (wifi.send((const uint8_t*)sendStr, strlen(sendStr))) {
    Serial.print("send back ok\r\n");
  } else {
    Serial.print("send back ng\r\n");
  }

  delay(500);
}
