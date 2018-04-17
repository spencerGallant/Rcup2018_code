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
  qtrInit();
  dribblerInit();
  MotorsInit();
  buttonInit();
  IMUInit();
  RGBLEDInit();
  LIDARinit(); //if prints nack then LIDARs are not connected
  TOFinit();
  delay(1000);
  setGoalAndRunProgram();
}

void loop() {
  updateDistances();
  Serial.println(currentState);
  switch (currentState) {
    case ON_LINE:
      setRGB(255, 0, 0);
      currentState = DOESNT_SEE_BALL;
      //getInBounds();
      break;
    case HAS_BALL:
      setRGB(0, 255, 0);
      break;
    case SEES_BALL:
      setRGB(0, 0, 255);
      goToBall(230);
      break;
    case DOESNT_SEE_BALL:
      setRGB(255, 0, 255);
      doesnt_see_ball();
      break;
  }
}

void interrupt() {
  currentState = ON_LINE;
}
