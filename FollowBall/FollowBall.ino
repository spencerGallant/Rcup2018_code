//#define MAXONS 0//Comment this out when using POLOLU motors.

#include "robotDefines.h"


void setup() {
  Serial.begin(115200);
  Serial2.begin(4800);
  MotorsInit();
  buttonInit();
  Serial.println("Dual G2 High Power Motor Shield");
  delay(1000);
  Serial.println("Running");
  runProgramWhenButtonHit();
  Serial.print("Waiting for data...");

}

void loop() {
  calculateAngle();
  goToBall(150);
}
