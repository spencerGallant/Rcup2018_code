void has_ball(){
  if(vl.readRange() > 50){
    currentState = DOESNT_SEE_BALL;
  }
}

void TOFinit(){
  Serial.println("Adafruit VL6180x test!");
  if (! vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
  Serial.println("Sensor found!");
}
