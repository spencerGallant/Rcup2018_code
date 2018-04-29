#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LIDARLite.h>
#include <algorithm>
#include <math.h>
#include "Adafruit_VL6180X.h"
#include <SharpIR.h>

LIDARLite myLidarLite;
Adafruit_VL6180X vl = Adafruit_VL6180X();

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
  LIDARinit();
  TOFInit();
  delay(1000);
  setGoalAndRunProgram();
  delay(1000);
  currentState = DOESNT_SEE_BALL; //initialize at this state because interrupt can be triggered while calibrating
  checkGoalieSwitchOn();
  setRGB(255, 255, 255);
}

void loop() {
  Serial.print(goalie);
  Serial.print(" ");
  Serial.print(currentState);
  Serial.print(" ");
  Serial.println(checkPossession());
  checkToSetGoal();
  if (goalie == true) {
    setRGB(255, 0, 0);
    updateDistances();
    switch (currentState) {
      case ON_LINE: //out of bounds
        getInBounds();
        break;
      case SEES_BALL:
        if (checkPossession() == true) {
          currentState = HAS_BALL;
          stopMotors();
        }
        //blockBall();
        break;
      case DOESNT_SEE_BALL:
        goalieFindBall();
        break;
      case HAS_BALL:
        goalieToStriker();
        break;
      case OUT_OF_GOAL:
        getToGoal();
        break;
    }
  }
  else { //striker mode
    setRGB(0, 0, 255);
    strikerToGoalie();
    switch (currentState) {
      case ON_LINE: //out of bounds
        getInBounds();
        break;
      case SEES_BALL:
        goToBall(180);
        break;
      case DOESNT_SEE_BALL:
        doesnt_see_ball();
        break;
      case HAS_BALL:
        scoreGoal();
        break;
    }
  }
  /*if (checkPossession() == true) {
    if (randomGenerated == true) {
      if (shootingRight == true) {
        getToRightCornerBackwards();
      }
      else {
        getToLeftCornerBackwards();
      }
    }
    else {
      shootingRight = random(0, 2);
      randomGenerated = true;
    }
    }
    else {
    stopMotors();
    }
    }
  */
}

void interrupt() {
  currentState = ON_LINE;
}
