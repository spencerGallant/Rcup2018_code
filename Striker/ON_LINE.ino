void getInBounds() {
  stopMotors();
  int pointDirection; //which way the robot should point after spinning: it should spin to the clostest angle parallel to the field
  IMU_GetReadings();
  pointDirection = (abs(g_goal - g_xPos) < abs(g_goal + 180 - g_xPos)) ? g_goal : (g_goal + 180);
  IMU_spinToDirection(pointDirection);
  for (int i = 0; i < 10000; i++) {
    int x = 0;
    int y = 0;
    boolean isClear = true;
    boolean r = rightClear();
    boolean l = leftClear();
    boolean f = frontClear();
    boolean b = backClear();
    if (!r) x--, isClear = false;
    if (!l) x++, isClear = false;
    if (!f) y--, isClear = false;
    if (!b) y++, isClear = false;
    if (x == 0 && y == 0) {
      IMU_spinToDirection(pointDirection);
    } else {
      int ang = xyToAngle(x, y);
      driveToHeadingIMU(pointDirection, ang, 120);
    }
    if (isClear) break;
  }
  currentState = DOESNT_SEE_BALL;
}


