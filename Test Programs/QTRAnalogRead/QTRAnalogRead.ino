#define NUMSENSORS 4
int pins[NUMSENSORS] = {A0, A1, A2, A3};
void setup() {


}

void loop() {
  Serial.print(analogRead(A0));
  Serial.print("    ");
  Serial.print(analogRead(A1));
  Serial.print("    ");
  Serial.print(analogRead(A2));
  Serial.print("    ");
  Serial.print(analogRead(A3));
  Serial.println(" ");
}
