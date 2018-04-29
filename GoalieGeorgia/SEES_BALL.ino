
void goToBall(int speed) {
  int k = 3; //130--> 2; 200--> 3
  lastTimeSawBall = millis();
  calculateAngle();
  if(abs(ballAngle) < 20) dribblerIn();
  else dribblerOff();
  if (ballAngle == 10000) { //doesn't see ball. switch state
    stopMotors();
    currentState = DOESNT_SEE_BALL;
  }
  else if (ballAngle == 2000) { //not getting right readings
    setRGB(255, 255, 255);
    stopMotors();
    clearCameraBuffer();
  }
  else if ((ballAngle > 30) || (ballAngle < -30)) { //if the ball is behind the robot just spin to it
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
  int k = 2;
  if (inGoal() == false) {
    currentState = OUT_OF_GOAL;
    return;
  }
  calculateAngleGoalie();
  if (yPos < 2000) {
    int blockingSpeed = yPos * k;
    if (blockingSpeed > 200) blockingSpeed = 200;
    else if (blockingSpeed < -200) blockingSpeed = -200;
    driveToHeadingIMU(g_goal, 90, blockingSpeed);
  }
  else currentState = DOESNT_SEE_BALL;
}

