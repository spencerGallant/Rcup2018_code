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
  Serial2.begin(19200);
  Serial6.begin(9600); //xbee
  qtrInit();
  dribblerInit();
  MotorsInit();
  buttonInit();
  IMUInit();
  RGBLEDInit();
  LIDARinit();
  TOFInit();
  //setGoalAndRunProgram();
  //delay(1000);
  currentState = DOESNT_SEE_BALL; //CHANGE TO DOESN'T SEE BALL//initialize at this state because interrupt can be triggered while calibrating
  checkGoalieSwitch();
  clearCameraBuffer();
}

int finalMotorSpeed = 0;

void loop() {
    Serial.println(currentState);
    getCameraReadings();     // read the incoming camera x and y pos
    if (goalie == true) {
    setRGB(255, 0, 0);
    updateDistances();
    if (checkPossession() == true && currentState != ON_LINE) currentState = HAS_BALL;
    switch (currentState) {
      case ON_LINE: //out of bounds
        getInBounds();
        break;
      case SEES_BALL:
        blockBall();
        goalieGoingToBall = false;
        break;
      case DOESNT_SEE_BALL:
        if (goalieGoingToBall) {
          driveToHeadingIMU(g_goal, 0, 130);
          delay(250);
          clearCameraBuffer();
          getCameraReadings();
          calculateAngleGoalie();
          if (checkPossession()) currentState = HAS_BALL;
          else if (yPos < 2000) currentState = SEES_BALL;
          else goalieGoingToBall = false;
        }
        else  goalieFindBall();
        break;
      case HAS_BALL:
       // if (goalieGoingToBall) {
          if (checkPossession()) {
            goalieToStriker();

            //            pickScoringMethodAndScore();
            //            calculateGoalAngle();
            previouslyInGoal = false;
          }
          else currentState = DOESNT_SEE_BALL;
    //        }
    //        else {
    //          checkPossessionKick();
    //          currentState = DOESNT_SEE_BALL;
    //        }
        break;
      case OUT_OF_GOAL:
        if (previouslyInGoal) stayInGoal();
        else getToGoal();
        break;
      case GO_TO_BALL:
        calculateAngle();
        goToBall(180);
        goalieGoingToBall = true;
        break;
    }
    }
    else { //striker mode
    strikerToGoalie();
    setRGB(0, 0, 255);
    calculateGoalAngle();
    calculateAngle();
    switch (currentState) {
      case ON_LINE: //out of bounds
        getInBounds(); //can switch to DOESNT_SEE_BALL
        break;
      case SEES_BALL:
        goToBall(180);
        break;
      case DOESNT_SEE_BALL:
        if (checkPossession() == true) {
          currentState = HAS_BALL;
          stopMotors();
        }
        else doesnt_see_ball();
        break;
      case HAS_BALL:
        if (checkPossession() == false) { //first time loses possession of the ball
          facingGoal = false;
          driveToHeading(0, 100);
          delay(250);
          currentState = DOESNT_SEE_BALL;
          clearCameraBuffer();
        }
        else pickScoringMethodAndScore();
        break;
    }

    }

  
}

void interrupt() {
  currentState = ON_LINE;
}

void moveWithBall() {
  finalMotorSpeed = sendNumbersViaXbee();

  checkToSetGoal();
  if (checkPossession() == true) {
    dribblerIn();
    driveToHeadingIMU(g_goal, 180, finalMotorSpeed);
  }
  else {
    dribblerOff();
    stopMotors();
  }
}

