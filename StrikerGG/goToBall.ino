
void goToBall(int speed) {
  int k = 2;
  calculateAngle();

  if (ballAngle == 1000) {
    stopMotors();
    currentState = DOESNT_SEE_BALL;
  }
  else if ((ballAngle > 90) || (ballAngle < -90)) spinToBall();
  else {
    float rad = getRad(0);
    float proportionals[] = {cos(rad - 0.785398), cos(rad - 2.14675), cos(rad - 4.13643), cos(rad - 5.49779)};

    setM1Speed((speed * proportionals[0]) - (ballAngle * k));
    setM2Speed((-speed * proportionals[1]) + (ballAngle * k));
    setM3Speed((-speed * proportionals[2]) + (ballAngle * k));
    setM4Speed((-speed * proportionals[3]) + (ballAngle * k));
  }
}
