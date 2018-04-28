void setup() {
  pinMode(31, OUTPUT); //dribbler init

}

void loop() {
  kick();
}


void kick() {
  digitalWrite(31, HIGH);
  delay(120);
  digitalWrite(31, LOW);
  delay(5000);
}

