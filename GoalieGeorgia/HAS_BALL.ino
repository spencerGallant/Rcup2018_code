void scoreGoal() {
  updateDistances();
  printDistances();
  boolean forwards = abs(IMU_calcError(g_goal)) < 90;
  if (checkPossession() == false) {
    setRGB(100, 100, 0);
    facingGoal = false;
    currentState = DOESNT_SEE_BALL;
    dribblerOff();
    clearCameraBuffer();
  }
  else if (forwards == true) {
    Serial6.print("forwards: ");
    if (facingGoal == false) {
      Serial6.println("spinning ");
      dribblerIn();
      spinSlowCheckPossesion(g_goal);
      facingGoal = true;
      updateDistances();
    }
    if (frontDist + backDist > 200 && frontDist >= 40) { //clear in front and back direction
      straightForwardsShoot();
    }
    else { //not clear view in front or back
      if (frontDist < 40 || IRDistance() < 15) { //blocked in front
        Serial6.println("blocked ");
        dribblerIn();
        spinSlowCheckPossesion(g_goal + 180);
      }
      else { //not sure where you are just go forward
        Serial6.println("not sure ");
        setDribbler(-20);
        driveToHeadingIMU(g_goal, 0, forwardSpeedWithBall);
      }
    }
  } //end of if facing forwards
  else { //facing backwards
    Serial6.println("backwards: ");
    if (facingGoal == false) {
      dribblerIn();
      spinSlowCheckPossesion(g_goal + 180);
      Serial6.println("spinning ");
      facingGoal = true;
      updateDistances();
    }
    if (frontDist + backDist > 200 && backDist >= 40) { //clear in front and back direction
      straightBackwardsShoot();
    }
    else { //not clear in front or back direction
      if (backDist < 40) {
        Serial6.println("blocked ");
        dribblerIn();
        moveToOpenSide();
      }
      else { //not blocked in direction you are going, but blocked somewhere
        if (IRDistance() < 15) {
          Serial6.println("trailed ");
          dribblerIn();
          spinSlowCheckPossesion(g_goal);
        }
        else { //not blocked in back so probably read the goalie in "not clear" reading
          Serial6.println("blocked somewhere");
          dribblerIn();
          moveToOpenSide();
        }
      }
    }
  }
}

void moveToOpenSide() {
  checkWhichHemisphere();
  if (hemisphere == 'r') {
    driveToHeadingIMU(g_goal + 180, 90, sideSpeedWithBall);
  }
  else {
    driveToHeadingIMU(g_goal + 180, 270, sideSpeedWithBall);
  }
}

boolean checkPossession() {
  uint8_t range = vl.readRange();
  if (range < 50) {
    return true;
  }
  else return false;
}

void straightForwardsShoot() {
  checkWhichHemisphere();
  if (frontDist > 90) {
    Serial6.println("shooting: moving forward");
    setDribbler(-20);
    driveToHeadingIMU(g_goal, 0, forwardSpeedWithBall);
  }
  else {
    dribblerIn();
    if (hemisphere == 'r') {
      Serial6.println("shooting: right hemisphere");
      spinSlowCheckPossesion(g_goal - 45);

    }
    else if (hemisphere == 'l') {
      Serial6.println("shooting: left hemisphere");
      spinSlowCheckPossesion(g_goal + 45);
    }
    else {
      Serial6.println("shooting: center hemisphere");
      stopMotors();
    }
    kick();
  }
}

void straightBackwardsShoot() {
  checkWhichHemisphere();

  if (backDist > 90) {
    Serial6.println("shooting: moving backwards");
    dribblerIn();
    driveToHeadingIMU(g_goal + 180, 180, backwardSpeedWithBall);
  }
  else {
    dribblerIn();
    if (hemisphere == 'r') { //actually closer to left side
      Serial6.println("shooting: left hemisphere");
      spinSlowCheckPossesion(g_goal - 90);
      spinSlowCheckPossesion(g_goal + 45);
    }
    else if (hemisphere == 'l') { //actually closer to right side
      Serial6.println("shooting: right hemisphere");
      spinSlowCheckPossesion(g_goal + 90);
      spinSlowCheckPossesion(g_goal - 45);
    }
    else {
      Serial6.println("shooting: center hemisphere");
      if (rightDist > leftDist) {
        spinSlowCheckPossesion(g_goal + 90);
        spinSlowCheckPossesion(g_goal);
      }
      else {
        spinSlowCheckPossesion(g_goal - 90);
        spinSlowCheckPossesion(g_goal);
      }
    }
    kick();
  }
}


void checkWhichHemisphere() {
  if ((rightDist + leftDist) > 150) { //if the side sensors add up to around the width of the field or greater
    if (rightDist > 80 && rightDist < 110) {
      hemisphere = 'c';
    }
    else if (rightDist < leftDist) { //robot is on the right side
      hemisphere = 'r';
    }
    else {
      hemisphere = 'l';
    }
  }
}

void getToLeftCornerBackwards() {
  updateDistances();//MAKE SURE YOU DONT DO THIS TWICE
  printDistances();
  dribblerIn();
  if (abs(IMU_calcError(g_goal + 180)) > 20) {
    spinSlowCheckPossesion(g_goal + 180);
    updateDistances();
  }
  if (backDist < 80 && rightDist < 55 && frontDist + backDist > 220) {
    leftBackwardsShoot();
  }
  else if (backDist >= 80) {
    int diff = rightDist - 55;
    diff = diff * 2;
    if (diff > 90) diff = 90;
    if (diff < -90) diff = -90;
    driveToHeadingIMU(g_goal + 180, 180 - diff, 100);
  }
  else if (backDist < 100 && rightDist >= 55) {
    driveToHeadingIMU(g_goal + 180, 90, 100);
  }
}



void getToRightCornerBackwards() {
  updateDistances();//MAKE SURE YOU DONT DO THIS TWICE
  printDistances();
  dribblerIn();
  if (abs(IMU_calcError(g_goal + 180)) > 20) {
    spinSlowCheckPossesion(g_goal + 180);
    updateDistances();
  }
  if (backDist < 80 && leftDist < 55 && frontDist + backDist > 220) {
    rightBackwardsShoot();
  }
  else if (backDist >= 80) {
    int diff = leftDist - 55;
    diff = diff * 2;
    if (diff > 90) diff = 90;
    if (diff < -90) diff = -90;
    driveToHeadingIMU(g_goal + 180, 180 + diff, 100);
  }
  else if (backDist < 100 && leftDist >= 55) {
    driveToHeadingIMU(g_goal + 180, 270, 100);
  }
}
void rightBackwardsShoot() {
  spinSlowCheckPossesion(g_goal + 90);
  spinSlowCheckPossesion(g_goal - 45);
  kick();
}

void leftBackwardsShoot() {
  Serial6.print("SPINNING 90");
  spinSlowCheckPossesion(g_goal - 90);
  Serial6.print("SPINNING 45");
  //spinSlowCheckPossesion(g_goal + 45);
  kick();
}


