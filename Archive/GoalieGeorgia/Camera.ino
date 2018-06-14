void calculateAngle() {
  // Only run this if you are in fact recieving x and y data. Otherwise, ballAngle does not change
  getCameraReadings();     // read the incoming camera x and y pos
  if (xPos > 1280 || yPos > 960) { //filter out and bad readings. 2000 is sign of bad readings
    ballAngle = 2000;
    setRGB(255, 0, 255); //purple
  } else {
    xPos = xPos - 640; //makes the center of the screen (640*480) 0 instead of having it be top left corner
    yPos = yPos - 480;

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
    if (ballAngle > 360) ballAngle = ballAngle - 360;

    ballAngle = ballAngle - 180;

    if (m == .75) { //needs to be at end so overrides any other calculations
      ballAngle = 10000; //ballAngle = 10000 when robot doesn't see ball
    }
  }
}

void getCameraReadings() {
  char lc = Serial2.read();
  long bTimer = millis();
  while (word(0, lc) != 254) {
    lc = Serial2.read();
    if(bTimer + 400 < millis()) {
      clearCameraBuffer();
      bTimer = millis();
    }
  }
  while (Serial2.available() < 2);
  char highChar1 = Serial2.read();
  char lowChar1 = Serial2.read();
  while (Serial2.available() < 2);
  char highChar2 = Serial2.read();
  char lowChar2 = Serial2.read();
  while (Serial2.available() < 2);
  char highChar3 = Serial2.read();
  char lowChar3 = Serial2.read();
  while (Serial2.available() < 2);
  char highChar4 = Serial2.read();
  char lowChar4 = Serial2.read();
  // say what you got:
  xPos = word(highChar1, lowChar1);
  yPos = word(highChar2, lowChar2);
  tPos = word(highChar3, lowChar3);
  oPos = word(highChar4, lowChar4);

  if (abs(oldXpos - xPos) > 10 || abs(oldYpos - yPos) > 10 || (yPos == 0 && xPos == 0) && goalieGoingToBall == false) notMovingTimer = millis();

  oldXpos = xPos;
  oldYpos = yPos;

}

void calculateAngleGoalie() {
  if (Serial2.available() > 0) {
    getCameraReadings();     // read the incoming camera x pos
    if (xPos == 0 && yPos == 0) { //needs to be at end so overrides any other calculations
      yPos = 10000; //xPos & yPos = 10000 when robot doesn't see ball
      xPos = 10000;
    }
    if (yPos > 960 || xPos > 1280 ) { //filter out and bad readings. 2000 is sign of bad readings
      yPos = 2000;
      xPos = 2000;
      setRGB(255, 0, 255);
      clearCameraBuffer();
      return;
    } else {
      yPos = yPos - 480; //makes the center of the screen (640*480) 0 instead of having it be top left corner
    }
  }
}
void spinToBall() {
  float k = 1;
  spin(ballAngle * k);
}

void clearCameraBuffer() {
  Serial2.clear();
}

