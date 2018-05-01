
void checkGoalieSwitch() {
  if (digitalRead(27) == HIGH) goalie = true;
  else goalie = false;
}

void strikerToGoalie() { // robot is in striker mode and is converting to goalie mode
  if (Serial6.available() > 0) {
    char received = Serial6.read();
    while (Serial6.available() > 0) Serial6.read();
    if (received == 'g') {
      Serial.println("received ");
      Serial6.write((char)'r');
      goalie = true;
      setRGB(255, 0, 0);
    }
  }
}

void goalieToStriker() {// robot is in goalie mode and is converting to striker mode
  Serial.println("goalie to striker beginning");
  char input = 'g';
  Serial6.write((char)input);
  Serial.println((char)input);
  if (Serial6.available() > 0) {
    char received = Serial6.read();
    while (Serial6.available()) Serial6.read();
    if (received == 'r') {
      Serial.println("echoed");
      goalie = false;
      setRGB(0, 0, 255);
      Serial.println("I DA CAPTAIN NOW");
    }
  }
}

