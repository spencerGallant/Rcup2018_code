
void checkGoalieSwitch() {
  if (digitalRead(27) == HIGH) goalie = true;
  else goalie = false;
}
