/*
 * 人感センサーのデモ
 * - ピン(GND, GPIO, IN)
 */

#define PIR 2
#define LED 13 // 検知時に光らせる

int state = LOW;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(PIR)) {
    if(state == LOW) {
      Serial.println("on");
      state = HIGH;
    }
  } else {
    if (state == HIGH){
      Serial.println("off");
      state = LOW;
    }
  }
  digitalWrite(LED, state);

  delay(500);
}
