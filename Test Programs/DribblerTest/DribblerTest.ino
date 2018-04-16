void setup() {
  pinMode(11, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  }

void loop() {
  digitalWrite(11, LOW);
  digitalWrite(32, HIGH);
  analogWrite(8, 100);
  //Serial.println(analogRead(A14));
}


