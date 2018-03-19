//#define MAXONS 0//Comment this out when using POLOLU motors.

#include "robotDefines.h"


void setup() {
  Serial.begin(115200);
  Serial2.begin(4800);
  MotorsInit();
  Serial.println("Dual G2 High Power Motor Shield");
  delay(1000);
  Serial.println("Running");
}

void loop() {
  calculateAngle();
  goToBall(100);
  Serial.println(ballAngle);
}
