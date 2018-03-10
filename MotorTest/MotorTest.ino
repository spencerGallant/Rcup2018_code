//#define MAXONS 0//Comment this out when using POLOLU motors.

#include "robotDefines.h"


void setup() {
  Serial.begin(115200);
  MotorsInit();
  Serial.println("Dual G2 High Power Motor Shield");
  delay(1000);
  Serial.println("Running");
}

void loop() {
setM1Speed(100);
setM2Speed(100);
setM3Speed(100);
setM4Speed(100);
}
