void setup() {
  pinMode(11, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  }

void loop() {
  digitalWrite(11, HIGH);
  digitalWrite(32, LOW);
  analogWrite(8, 255);
  //Serial.println(analogRead(A14));
}


