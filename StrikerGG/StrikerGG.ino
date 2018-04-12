#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LIDARLite.h>
#include <algorithm>
#include <math.h>

LIDARLite myLidarLite;

#include "robotDefines.h"


void setup() {
  Serial.begin(115200);
  Serial2.begin(4800);

  dribblerInit();
  MotorsInit();
  qtrInit();
  buttonInit();
  IMUInit();
  RGBLEDInit();
  LIDARinit();
  delay(1000);

  Serial.print("Set goal");
  setGoalAndRunProgram();
  Serial.print("Running");
  delay(1000);


}

void loop() {
  driveToHeadingIMU(g_goal, 0, 120);

   // dribblerIn();
 //   driveToHeadingIMU(g_goal, g_goal+180, 130);
  //  switch (currentState) {
  //    case ON_LINE: //out of bounds
  //      getInBounds();
  //      break;
  //    case SEES_BALL:
  //      goToBall(200);
  //      break;
  //    case DOESNT_SEE_BALL:
  //      if(ballAngle != 1000) currentState = SEES_BALL; //TEMPORARY: if sees ball change state
  //      else currentState = SEES_BALL; //doesnt see ball and stops
  //      break;
  //    case HAS_BALL:
  //      break;
  //  }
}

void interrupt() {
  currentState = ON_LINE;
}
