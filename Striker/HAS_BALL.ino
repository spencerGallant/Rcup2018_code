void has_ball(){
  if(vl.readRange() > 60){ //check if doesn't have ball now
    currentState = DOESNT_SEE_BALL;
    return;
  }
  else{
    dribblerIn();
    delay(100);
    IMU_spinToDirection(g_goal);
    driveToHeadingIMU(g_goal, 0, 150);
  }
}


