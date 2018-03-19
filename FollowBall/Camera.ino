void calculateAngle() {
  // send data only when you receive data:
  if (Serial2.available() > 0) {
    // read the incoming byte:
    char highChar1 = Serial2.read();
    char lowChar1 = Serial2.read();
    char highChar2 = Serial2.read();
    char lowChar2 = Serial2.read();
    // say what you got:
    double xPos = word(highChar1, lowChar1);
    double yPos = word(highChar2, lowChar2);
    xPos = xPos - 640;
    yPos = yPos - 480;

    xPos = xPos * -1;
    yPos = yPos * -1;
    double m = (float)(yPos) / (float)(xPos);
    ballAngle = atan((double)m);
    ballAngle = ballAngle * 57296 / 1000;
    if (xPos < 0 && yPos < 0) ballAngle = ballAngle + 180;
    else if (xPos > 0 && yPos < 0) ballAngle = ballAngle + 360;
    else if (xPos < 0 && yPos > 0) ballAngle = ballAngle + 180;

    ballAngle = ballAngle - 180;

    if (m == .75) ballAngle = 1000;
  }
}

void spinToBall() {
  int k = 4;

  if (ballAngle != 1000) spin(ballAngle * k);
  else spin(0);

}

void goToBall(int speed) {
  int k = 2;
    if(ballAngle == 1000) spin(0);
  else if((ballAngle > 90) || (ballAngle < -90)) spinToBall();
  else {
    float rad = getRad(0);
    float proportionals[] = {cos(rad - 0.785398), cos(rad - 2.14675), cos(rad - 4.13643), cos(rad - 5.49779)};

    setM1Speed((-speed * proportionals[0]) -(ballAngle*k));
    setM2Speed((-speed * proportionals[1]) -(ballAngle*k));
    setM3Speed((speed * proportionals[2]) + (ballAngle*k));
    setM4Speed((speed * proportionals[3]) + (ballAngle*k));
  }
}

