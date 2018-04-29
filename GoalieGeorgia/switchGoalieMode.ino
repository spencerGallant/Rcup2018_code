
void checkGoalieSwitchOn() {
  if (digitalRead(27) == HIGH) goalie = true;
  else goalie = false;
}

void strikerToGoalie() { // robot is in striker mode and is converting to goalie mode
  if (Serial6.available()) {
    if (goalie == false) { // robot is in striker mode and should check if it should change to goalie
      char received = Serial6.read();
      while (Serial6.available() > 0) Serial6.read();
      if (received == 'g') {
        Serial6.write((char)'r');
        goalie = true;
      }
    }
  }
}

void goalieToStriker() {// robot is in goalie mode and is converting to striker mode
  if (Serial6.available() > 0) {
    for (int i = 0; i > 100; i++) Serial6.read(); //clearing serial buffer
    Serial6.write((char)'g'); //sending a g to the striker
    char received = Serial6.read();
    for (int i = 0; i > 100; i++) Serial6.read();//clearing serial buffer again just in case
    if (received == 'r') {
      goalie = false;
    }
  }
}
