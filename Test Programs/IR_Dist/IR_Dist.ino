void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(4800/(analogRead(A15) - 20));
}


