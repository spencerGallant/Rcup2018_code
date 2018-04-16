void has_ball() {
  //  if (vl.readRange() > 50) { //check if doesn't have ball now
  //    currentState = DOESNT_SEE_BALL;
  //    return;
  //  }
  //  else {
  if (vl.readRange() <= 50) {
    dribblerIn();
    if (spunToShoot == false) { //COME BACK TO spunToShoot variable because need to change it to false in the other states (look at doesn't see ball)
      IMU_spinToDirection(g_goal);
      spunToShoot = true;
      updateDistances();
    }
    else { //already spun
      driveToHeadingIMU(g_goal, 0, 150);
    }
  }
  //  }
}

void score() {
  //  if (finishedScoring) finishedScoring = false;
  //  //Serial4.println("in function");
  //  IMUGetReadings();
  //  boolean forwards = abs(calcError(g_goal)) < 90;
  //  if (forwards == true) {
  //    //Serial4.println("FORWARDS");
  //    if (spunToShoot == false) { //under all circumstances (no matter if coast is clear or not) should face goal
  //      spunToShoot = true;
  //      spinToShoot(0);
  //      updateDistances();
  //    }
  //    if (((frontDist + backDist) > 200)) { //front and back have a clear view of the field
  //      //Serial4.println("CLEAR VIEW");
  //      forwardsShoot();
  //    }
  //    else { //blocked in forward direction
  //      if (frontDist < 25) {
  //        //Serial4.println("BLOCKED, SPIN BACKWARDS");
  //        spinToShoot(180); //spin backwards if blocked
  //      }
  //      else { //know idea where you are just go forward
  //        //Serial4.println("JUST GO FORWARDS");
  //        setDribbler(-100);
  //        driveToHeadingIMU(g_goal, 0, 100);
  //      }
  //    }
}

