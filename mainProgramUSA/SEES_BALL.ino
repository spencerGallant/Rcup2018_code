
void goToBall(int speed) {
  float k = 2.5; //130--> 2; 200--> 3
  lastTimeSawBall = millis();
  if (abs(ballAngle) < 20) dribblerIn();
  else dribblerOff();
  if (ballAngle == 10000) { //doesn't see ball. switch state
    stopMotors();
    currentState = DOESNT_SEE_BALL;
  }
  else if (ballAngle == 2000) { //not getting right readings
    stopMotors();
    clearCameraBuffer();
  }
  else if (abs(ballAngle > 20)) { //if the ball is behind the robot just spin to it
    spinToBall();
    spinningToBall = true;

  }
  else { //otherwise use PID to go to ball
    spinningToBall = false;
    float rad = getRad(0);
    float proportionals[] = {sin(-rad + 3.92699082), sin(-rad + 5.28834763), sin(-rad + 0.994837674), sin(-rad + 2.35619449)};

    setM1Speed((speed * proportionals[0] - (ballAngle * k)));
    setM2Speed((speed * proportionals[1] - (ballAngle * k)));
    setM3Speed((speed * proportionals[2] - (ballAngle * k)));
    setM4Speed((speed * proportionals[3] - (ballAngle * k)));
  }
}

void blockBall() {
  if (inGoal() == false  && (xPos > 800 || xPos < 300)) {
    currentState = OUT_OF_GOAL;
    return;
  }
  int oldXposDerivative = xPos;
  calculateAngleGoalie();
  float pk = 2; //for PID
  if (xPos > 450 && abs(yPos) > 50) pk = 3;
  if (yPos < 2000 && abs(yPos) > 50 && xPos < 1000) {
    float dk = 10;
    int derivative = (abs(oldXposDerivative - xPos))*dk;
    int blockingSpeed = (yPos * pk) + derivative;
    if (blockingSpeed > 255) blockingSpeed = 255;
    else if (blockingSpeed < -255) blockingSpeed = -255;
    driveToHeadingIMU(g_goal, 90, blockingSpeed);
    lastTimeSawBall = millis();
  }
  else if ((millis() - notMovingTimer) > 4000) currentState = GO_TO_BALL;
  else if (abs(yPos) < 50) IMU_spinToDirection(g_goal);
  else currentState = DOESNT_SEE_BALL;
}

