void setup() {
  pinMode(17, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(17) == LOW) {
    Serial.println("LOW");
  }
  delay(1000);
}
