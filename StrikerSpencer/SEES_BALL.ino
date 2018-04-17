
void goToBall(int speed) {
  //dribblerIn();
  int k = 3;
  lastTimeSawBall = millis();
  calculateAngle();
  if (ballAngle == 1000) {
    currentState = DOESNT_SEE_BALL;
  }
  else if ((ballAngle > 90) || (ballAngle < -90)) {
    spinToBall();
    spinningToBall = true;
  }
  else {
    spinningToBall = false;
    float rad = getRad(0);
    float proportionals[] = {sin(-rad + 3.92699082), sin(-rad + 5.28834763), sin(-rad + 0.994837674), sin(-rad + 2.35619449)};
    setM1Speed(-(speed * proportionals[0] + (ballAngle * k)));
    setM2Speed(speed * proportionals[1] + (ballAngle * k));
    setM3Speed(speed * proportionals[2] + (ballAngle * k));
    setM4Speed(speed * proportionals[3] + (ballAngle * k));
  }
}
