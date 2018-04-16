#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LIDARLite.h>
#include <algorithm>
#include <math.h>
#include "Adafruit_VL6180X.h"
#include "robotDefines.h"


void setup() {
  Serial.begin(115200);
  Serial2.begin(4800);
  Serial6.begin(9600); //xbee
  qtrInit(); //should be done last to make sure interrupt doesn't interrupt calibration

  dribblerInit();
  MotorsInit();
  buttonInit();
  IMUInit();
  RGBLEDInit();
  LIDARinit();
  TOFinit();
  delay(1000);
  setGoalAndRunProgram();
  delay(1000);
}

void loop() {
  updateDistances();
  switch (currentState) {
    case ON_LINE:
      getInBounds();
      break;
    case HAS_BALL:
      has_ball();
      break;
    case SEES_BALL:
      goToBall(230);
      break;
    case DOESNT_SEE_BALL:
      doesnt_see_ball();
      break;
  }

}

void interrupt() {
  currentState = ON_LINE;
}
