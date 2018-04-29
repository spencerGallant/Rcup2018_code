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
}

void loop() {
  checkGoalieSwitchOn();
  checkToSetGoal();
  dribblerIn();
  Serial6.print(g_goal);
  Serial6.print(" ");
  Serial6.print(g_xPos);
  spinSlowCheckPossesion(g_goal - 90);
  delay(1000);
  spinSlowCheckPossesion(g_goal + 45);
  delay(3000);
  /*

    if (goalie == true) {
      updateDistances();
      switch (currentState) {
        case ON_LINE: //out of bounds
          getInBounds();
          break;
        case SEES_BALL:
          blockBall();
          break;
        case DOESNT_SEE_BALL:
          goalieFindBall();
          break;
        case HAS_BALL:
          break;
        case OUT_OF_GOAL:
          getToGoal();
          break;
      }
    }
    else {
      if (checkPossession() == true) {
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
    /* switch (currentState) {
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
      } */
}

void interrupt() {
  currentState = ON_LINE;
}
