boolean hasBall() {
  uint8_t range = vl.readRange();
  if (range < 50) return true;
  else return false;
}

void scoreGoal() {
  uint8_t range = vl.readRange();
  dribblerIn();
  if (range > 50) currentState = DOESNT_SEE_BALL;
  driveToHeadingIMU(g_goal, 180, 130);
}

