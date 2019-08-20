void setup() {
  delay(3000);

  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  uint8_t switchState = digitalRead(5) * 8 + digitalRead(4) * 4 + digitalRead(3) * 2 + digitalRead(2);
  Serial.println(switchState);

  Serial.print(digitalRead(5));
  Serial.print(" ");
  Serial.print(digitalRead(4));
  Serial.print(" ");
  Serial.print(digitalRead(3));
  Serial.print(" ");
  Serial.print(digitalRead(2));
  Serial.println("");

  delay(300);
}