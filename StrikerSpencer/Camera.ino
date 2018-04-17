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

    xPos = xPos - 320;
    yPos = yPos - 240;

    xPos = xPos * -1;
    yPos = yPos * -1;
    double m = (float)(yPos) / (float)(xPos);
    ballAngle = atan((double)m);
    ballAngle = ballAngle * 57296 / 1000;
    if (xPos < 0 && yPos < 0) ballAngle = ballAngle + 180;
    else if (xPos > 0 && yPos < 0) ballAngle = ballAngle + 360;
    else if (xPos < 0 && yPos > 0) ballAngle = ballAngle + 180;

    //comment two lines out if orientation is flipped 180 degrees
    ballAngle = ballAngle + 180;
    if(ballAngle > 360) ballAngle = ballAngle - 360;
    
    ballAngle = ballAngle - 180;

    if (m == .75) {
      ballAngle = 1000; //ballAngle = 1000 when robot doesn't see ball
      setRGB(0, 0, 255);
    }
    else setRGB(0, 255, 0);

  }
}

void spinToBall() {
  calculateAngle();
  float k = .8;

  if (ballAngle != 1000) spin(ballAngle * k);
  else stopMotors();

}
