
void goToBall(int speed) {
  int k = 3;
  if(vl.readRange() < 50){ //check if has ball now
    currentState = HAS_BALL;
    return;
  }
  calculateAngle();
  if (ballAngle == 1000) { //check if doesn't see ball now
    currentState = DOESNT_SEE_BALL;
    return;
  }
  else if ((ballAngle > 90) || (ballAngle < -90)) spinToBall();
  else {
    float rad = getRad(0);
    float proportionals[] = {sin(-rad + 3.92699082), sin(-rad + 5.28834763), sin(-rad + 0.994837674), sin(-rad + 2.35619449)};
    setM1Speed(-(speed * proportionals[0] + (ballAngle * k)));
    setM2Speed(speed * proportionals[1] + (ballAngle * k));
    setM3Speed(speed * proportionals[2] + (ballAngle * k));
    setM4Speed(speed * proportionals[3] + (ballAngle * k));
    lastTimeSawBall = millis();
  }
}
