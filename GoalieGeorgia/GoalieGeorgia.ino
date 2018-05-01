#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LIDARLite.h>
#include <algorithm>
#include <math.h>
#include "Adafruit_VL6180X.h"
#include <SharpIR.h>
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
  delay(1000); //???
  setGoalAndRunProgram();
  delay(1000);
  currentState = DOESNT_SEE_BALL; //CHANGE TO DOESN'T SEE BALL//initialize at this state because interrupt can be triggered while calibrating
  checkGoalieSwitchOn();
}

void loop() {
  checkToSetGoal();
  Serial6.println(currentState);
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
        if (checkPossession() == true) {
          currentState = HAS_BALL;
          stopMotors();
        }
        else dribblerOff();
        // goToBall(180);
        break;
      case DOESNT_SEE_BALL:
        dribblerOff();
        doesnt_see_ball();
        break;
      case HAS_BALL:
        if (checkPossession() == true) {
          digitalWrite(28, HIGH);
          setRGB(255, 0, 0);
          if (randomGenerated == true) {
            if (strategyChoice == 0) {
              Serial6.println("right corner");
              getToRightCornerBackwards();
            }
            else if (strategyChoice == 1) {
              Serial6.println("left corner");
              getToLeftCornerBackwards();
            }
            else if (strategyChoice == 2) { //regular scoring
              Serial6.println("regular scoring");
              scoreGoal();
            }
          }
          else {
            strategyChoice = random(0, 3);
            randomGenerated = true;
          }
          break;
        }
        else currentState = DOESNT_SEE_BALL;
    }
  }
}

void interrupt() {
  currentState = ON_LINE;
}
