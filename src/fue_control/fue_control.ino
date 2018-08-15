/*
 * Philips Hueを発光させる
 * - ESP-WROOM-02よりPUTで設定済みのカラーパターンを制御
 */

#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID "SSID"
#define PASSWORD "PASS"
#define HOST_NAME "192.168.0.1" // hue bridge host

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

  Serial.println("setup complete");
}

void loop(void)
{
  // TCPで接続
  wifi.createTCP(HOST_NAME, 80);

  // PUT
  sprintf(sendStr, "PUT /api/<username>/lights/11/state HTTP/1.1\r\nHost: %s\r\nContent-type: text/plain\r\ncontent-length: 12\r\n\r\n{\"on\": true}\r\n", HOST_NAME);

  Serial.println(sendStr);

  if (wifi.send((const uint8_t*)sendStr, strlen(sendStr))) {
    Serial.print("send back ok\r\n");
  } else {
    Serial.print("send back ng\r\n");
  }

  delay(500);
}
