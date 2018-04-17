void doesnt_see_ball() {
  calculateAngle();
  if (ballAngle != 1000) currentState = SEES_BALL;

  if (millis() - lastTimeSawBall <= 250 && spinningToBall == false) {
    setRGB(0, 0, 255);
    stopMotors();
  }
  else if (millis() - lastTimeSawBall >= 250 && millis() - lastTimeSawBall <= 2000) {
    setRGB(0, 0, 255);
    stopMotors();
  }
  else if (millis() - lastTimeSawBall >= 2000 && millis() - lastTimeSawBall <= 3000) {
    setRGB(255, 0, 255);
    IMU_spinToDirection(g_goal);
  }
  else if(millis() - lastTimeSawBall >= 3000 && millis() - lastTimeSawBall <= 7000){
    setRGB(255, 255, 255);
    int x = (rightDist >= leftDist) ? 1 : -1;
    int y = (frontDist >= backDist) ? 1 : -1;

    int lrdiff = abs(rightDist - leftDist);
    int fbdiff = abs(frontDist - backDist);

    boolean lrcentered = (lrdiff < 30 && rightDist + leftDist > 120);
    boolean fbcentered = (fbdiff < 30 && frontDist + backDist > 120);

    if (lrcentered && fbcentered ||  (millis() - lastTimeSawBall > 8000) ) {
      stopMotors();
    } else {
      driveToHeadingIMU(g_goal, xyToAngle(x, y), 200);
    }

  }
}

