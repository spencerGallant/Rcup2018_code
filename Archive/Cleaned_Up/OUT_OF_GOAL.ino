void getToGoal() {
  calculateAngleGoalie();
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
      if(yPos > 0 && yPos < 2000) stopMotors();
      else driveToHeadingIMU(g_goal, 270, 170);
      return;
    }
    else if (leftDist < 70) { //backDist <=90
      if(yPos < 0) stopMotors();
      else driveToHeadingIMU(g_goal, 90, 170);
      return;
    }
  }
  if (backDist > 90) {
    driveToHeadingIMU(g_goal, 180, 170);
      return;
  }
  if (backDist < 40) {
    driveToHeadingIMU(g_goal, 0, 170);
      return;
  }
}


boolean inGoal() {
  if (rightDist + leftDist > 150) { //not blocked
    if (rightDist < 70) return false;
    else if (leftDist < 70) return false;
  }
  if (backDist > 90) return false;
  return true;

}

