// 東芝 TA7291P

#define PIN_1 = 8;
#define PIN_2 = 9;
#define PWN = 10;

void setup() {
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PWN, OUTPUT);
}

void loop() {
  analogWrite(PWN, 100);

  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, LOW);
  delay(2000);

  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, HIGH);
  delay(2000);

  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, HIGH);
  delay(2000);

  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, HIGH);
  delay(2000);
}