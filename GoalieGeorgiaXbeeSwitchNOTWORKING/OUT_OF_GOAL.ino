void stayInGoal() {
  if (abs(IMU_calcError(g_goal)) < 30) IMU_spinToDirection(g_goal);
  dribblerOff();
  calculateAngleGoalie();
  if ((millis() - notMovingTimer) > 2000) {
    currentState = GO_TO_BALL;
    return;
  }
  if (inGoal() == true) {
    currentState = DOESNT_SEE_BALL;
    return;
  }
  if (rightDist + leftDist > 150) { //not blocked
    if (rightDist < 70 && backDist > 90) {
      driveToHeadingIMU(g_goal, 225, 170);
      return;
    }
    else if (leftDist < 70 && backDist > 90) {
      driveToHeadingIMU(g_goal, 135, 170);
      return;
    }
    else if (rightDist < 70) { //backDist <=90
      if (yPos > 0 && yPos < 2000) stopMotors();
      else driveToHeadingIMU(g_goal, 270, 170);
      return;
    }
    else if (leftDist < 70) { //backDist <=90
      if (yPos < 0) stopMotors();
      else driveToHeadingIMU(g_goal, 90, 170);
      return;
    }
  }
  if (backDist > 80) {
    driveToHeadingIMU(g_goal, 180, 90 + backDist);
    return;
  }
  if (backDist < 60) {
    driveToHeadingIMU(g_goal, 0, 100);
    return;
  }
}

void getToGoal() {
  dribblerOff();
  calculateAngleGoalie();
  if (abs(rightDist - leftDist) < 20 && backDist < 90 && backDist > 40) {
    currentState = DOESNT_SEE_BALL;
    return;
  }
  if ((rightDist - leftDist) > 20) {
    if (frontDist > 90) driveToHeadingIMU(g_goal + 180, 45, 90 + frontDist);
    else driveToHeadingIMU(g_goal + 180, 90, 80 + ((rightDist - leftDist) * 1.5));
    return;
  }
  else if ((leftDist - rightDist) > 20) {
    if (frontDist > 90) driveToHeadingIMU(g_goal + 180, 315, 90 + frontDist);
    else driveToHeadingIMU(g_goal + 180, 270, 80 + ((leftDist - rightDist) * 1.5));
    return;
  }
  else if (frontDist > 90) { //backDist <=90
    driveToHeadingIMU(g_goal + 180, 0, 90 + frontDist);
    return;
  }
  else if (IRDistance() > 20) driveToHeadingIMU(g_goal + 180, 90, 130);
  else if (frontDist < 40 || backDist < 150) driveToHeadingIMU(g_goal + 180, 90, 130);
  else {
    IMU_spinToDirection(g_goal);
    previouslyInGoal = true;
  }
}


boolean inGoal() {
  if (rightDist + leftDist > 150) { //not blocked
    if (rightDist < 70) return false;
    else if (leftDist < 70) return false;
  }
  if (backDist > 80) return false;
  if (backDist < 60) return false;

  previouslyInGoal = true;
  return true;

}
