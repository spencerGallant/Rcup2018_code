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
  Serial6.begin(9600); //xbee

  dribblerInit();
  MotorsInit();
  qtrInit();
  buttonInit();
  IMUInit();
  RGBLEDInit();
  LIDARinit();
  delay(1000);
  setGoalAndRunProgram();

}

void loop() {
  //  switch (currentState) {
  //    case ON_LINE: //out of bounds
  //      setRGB(255, 0, 0);
  //      getInBounds();
  //      break;
  //    case SEES_BALL:
  //      setRGB(0, 255, 0);
  //      //  goToBall(200);
  //      break;
  //    case DOESNT_SEE_BALL:
  ////      setRGB(0, 255, 0);
  ////      if (ballAngle != 1000) currentState = SEES_BALL; //TEMPORARY: if sees ball change state
  ////      else currentState = SEES_BALL; //doesnt see ball and stops
  //      break;
  //    case HAS_BALL:
  //      break;
  //  }
}

void interrupt() {
  setRGB(255, 0, 0);
  currentState = ON_LINE;
}
