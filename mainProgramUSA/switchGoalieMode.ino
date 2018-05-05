
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
      delay(50);
      Serial6.write((char)'r');
      delay(50);
      Serial.println("I'M GOALIE");
      goalie = true;
      currentState = OUT_OF_GOAL;
    }
  }
}

void goalieToStriker() {// robot is in goalie mode and is converting to striker mode
  Serial.println("goalie to striker beginning");
  char input = 'g';
  Serial6.write((char)input);
  Serial.println((char)input);
  float currentTime = millis();
  while (millis() - currentTime < 500) {
    if (Serial6.available() > 0) {
      char received = Serial6.read();
      if (received == 'r') {
        Serial.println("now I am Striker");
        goalie = false;
        currentState = DOESNT_SEE_BALL;
      }
    }
  }
}

