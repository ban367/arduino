/*
 * 人感センサー検知時にAPI送信
 * - 任意のIDを送信
 */

// ESP8266 Wifi
#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID "SSID"
#define PASSWORD "PASS"
#define HOST_NAME "192.168.0.1"

#define PIR_PIN 8 // 人感センサー

#define RX_PIN 2
#define TX_PIN 3

SoftwareSerial mySerial(RX_PIN, TX_PIN);
ESP8266 wifi(mySerial);

char sendStr[128]; // GET request

int state = LOW;

String standFront = "uuid";

/*
 * Initialize
 */
void setup(void) {
  Serial.begin(9600);
  while (!Serial);

  // Wifi
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

  pinMode(PIR_PIN, INPUT);
}

/*
 * Main loop
 */
void loop(void) {
  if (digitalRead(PIR_PIN)) {
    if (state == LOW) {
      Serial.println("on");
      getResponse(standFront);
      state = HIGH;
    }
  } else {
    if (state == HIGH){
      Serial.println("off");
      state = LOW;
    }
  }

  delay(500);
}

/*
 * API send
 */
int getResponse(String uuid) {
  // TCPで接続
  wifi.createTCP(HOST_NAME, 5000);

  sprintf(sendStr, "GET /?uuid=%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: arduino\r\n\r\n", uuid.c_str(), HOST_NAME);

  if (wifi.send((const uint8_t*)sendStr, strlen(sendStr))) {
    Serial.print("send back ok\r\n");
    return 0;
  } else {
    Serial.print("send back ng\r\n");
    return 1;
  }
}
