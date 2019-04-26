#include <Arduino.h>
// https://github.com/bogde/HX711
#include "HX711.h"

#define DT_PIN 8
#define SCK_PIN 9

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  scale.begin(DT_PIN, SCK_PIN);

  Serial.print("read:");
  Serial.println(scale.read());

  scale.set_scale();
  scale.tare();

  Serial.print("calibrating...");
  delay(5000);
  Serial.println(scale.get_units(10));

  scale.set_scale(-1536.00);
  scale.tare();

  Serial.print("read (calibrated):");
  Serial.println(scale.get_units(10));
}

void loop() {
  Serial.println(scale.get_units(10), 1);

  scale.power_down();
  delay(500);
  scale.power_up();
}
