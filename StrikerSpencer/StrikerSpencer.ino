#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LIDARLite.h>
#include <algorithm>
#include <math.h>
#include "Adafruit_VL6180X.h"

LIDARLite myLidarLite;
Adafruit_VL6180X vl = Adafruit_VL6180X();

#include "robotDefines.h"


void setup() {
  Serial.begin(115200);
  Serial2.begin(2400);
  Serial6.begin(9600); //xbee
  qtrInit(); //should be done last to make sure interrupt doesn't interrupt calibration

  dribblerInit();
  MotorsInit();
  buttonInit();
  IMUInit();
  RGBLEDInit();
  LIDARinit();
  TOFInit();
  delay(1000);
  setGoalAndRunProgram();
  delay(1000);
  Serial6.print("here");
}

void loop() {
  goToBall(130);
//  updateDistances();
//  // if(hasBall()) currentState = HAS_BALL;
//
//  switch (currentState) {
//    case ON_LINE: //out of bounds
//      setRGB(255, 0, 0);
//      getInBounds();
//      break;
//    case SEES_BALL:
//      setRGB(0, 255, 0);
//      goToBall(130);
//      break;
//    case DOESNT_SEE_BALL:
//      setRGB(0, 0, 255);
//      doesnt_see_ball();
//      break;
//    case HAS_BALL:
//      scoreGoal();
//      break;
//  }

}

void interrupt() {
  currentState = ON_LINE;
}
