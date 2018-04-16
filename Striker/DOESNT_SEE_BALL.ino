void doesnt_see_ball() {
  if (vl.readRange() < 50) { //check if has ball now
    Serial.println(vl.readRange());
    currentState = HAS_BALL;
    return;
  }
  calculateAngle();
  if (ballAngle != 1000) { //check if sees ball now
    currentState = SEES_BALL;
  }
  if (millis() - lastTimeSawBall >= 300 && millis() - lastTimeSawBall <= 1000) {
    stopMotors();
  }
  else if (millis() - lastTimeSawBall >= 1000 && millis() - lastTimeSawBall <= 1200) {
    IMU_spinToDirection(g_goal);
  }
  else {
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

