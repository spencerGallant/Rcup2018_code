/*
  Maxon motors require a PWM frequency > 50kHz.  This needs to be changed on the Te1nsy
  using pins 3, 4, 29, 30
*/


// Set speed for motor 1, speed is a number between -1023 and 1023
// Set speed for motor 1, speed is a number between -1023 and 1023
void setM1Speed(int speed)
{
  if (speed < 0) // if reverse is
  {
    digitalWrite(_M1DIR, HIGH);
    speed = -speed;
  }
  else
  {
    digitalWrite(_M1DIR, LOW);
  }
  analogWrite(_M1PWM, speed);
}

void setM2Speed(int speed)
{
  if (speed < 0) // if reverse is
  {
    digitalWrite(_M2DIR, HIGH);
    speed = -speed;
  }
  else
  {
    digitalWrite(_M2DIR, LOW);
  }
  analogWrite(_M2PWM, speed);
}

void setM3Speed(int speed)
{
  if (speed < 0) // if reverse is
  {
    digitalWrite(_M3DIR, HIGH);
    speed = -speed;
  }
  else
  {
    digitalWrite(_M3DIR, LOW);
  }
  analogWrite(_M3PWM, speed);
}
void setM4Speed(int speed)
{
  if (speed < 0) // if reverse is
  {
    digitalWrite(_M4DIR, HIGH);
    speed = -speed;
  }
  else
  {
    digitalWrite(_M4DIR, LOW);
  }
  analogWrite(_M4PWM, speed);
}
/*void setM3Speed(int speed)
  {
  boolean reverse = false;
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = true;  // Preserve the direction
  }

  #if MAXONS
  analogWrite(_M1PWM, speed);  // takes a speed from 0-1023
  #else
  // map speed of 0-1023 (used for Maxon) to 0-255
  analogWrite(_M1PWM, speed / 4); //takes a speed from 0-255 (so need to remap)
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;
  #endif

  if (reverse) // if reverse is TRUE
  {
    digitalWrite(_M1DIR, HIGH);
  }
  else
  {
    digitalWrite(_M1DIR, LOW);
  }
  }
  void setM4Speed(int speed)
  {
  boolean reverse = false;
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = true;  // Preserve the direction
  }

  #if MAXONS
  analogWrite(_M1PWM, speed);  // takes a speed from 0-1023
  #else
  // map speed of 0-1023 (used for Maxon) to 0-255
  analogWrite(_M1PWM, speed / 4); //takes a speed from 0-255 (so need to remap)
  if (speed > 255)  // Max PWM dutycycle
    speed = 255;
  #endif

  if (reverse) // if reverse is TRUE
  {
    digitalWrite(_M1DIR, HIGH);
  }
  else
  {
    digitalWrite(_M1DIR, LOW);
  }
  }


  // Set speed for all four motors
  void setSpeeds(int m1Speed, int m2Speed, int m3Speed, int m4Speed)
  {
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
  setM3Speed(m3Speed);
  setM4Speed(m4Speed);
  }*/
void setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}


// Return M1 current value in milliamps
unsigned int getM1CurrentMilliamps()
{
  // 18v18 results in 244 mA per count.
  unsigned int mAPerCount = 244;
  int reading = (getM1CurrentReading() - _offsetM1) ;
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}

// Return M2 current value in milliamps
unsigned int getM2CurrentMilliamps()
{
  // 18v18 results in 244 mA per count.
  unsigned int mAPerCount = 244;
  int reading = (getM2CurrentReading() - _offsetM2) ;
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}

// Return M3 current value in milliamps
unsigned int getM3CurrentMilliamps()
{
  // 18v18 results in 244 mA per count.
  unsigned int mAPerCount = 244;
  int reading = (getM3CurrentReading() - _offsetM3) ;
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}

// Return M4 current value in milliamps
unsigned int getM4CurrentMilliamps()
{
  // 18v18 results in 244 mA per count.
  unsigned int mAPerCount = 244;
  int reading = (getM4CurrentReading() - _offsetM4) ;
  if (reading > 0)
  {
    return reading * mAPerCount;
  }
  return 0;
}

unsigned int getM1CurrentReading()
{
  return analogRead(_M1CS);
}

unsigned int getM2CurrentReading()
{
  return analogRead(_M2CS);
}

unsigned int getM3CurrentReading()
{
  return analogRead(_M3CS);
}

unsigned int getM4CurrentReading()
{
  return analogRead(_M4CS);
}

void spin(int mSpeed)
{
  setM1Speed(-mSpeed);
  setM2Speed(mSpeed);
  setM3Speed(mSpeed);
  setM4Speed(mSpeed);

}


//Converts degrees to radians
float getRad(float angle) {
  return angle * 0.01745329251;
}

void stopMotors()
{
  setM1Speed(0);
  setM2Speed(0);
  setM3Speed(0);
  setM4Speed(0);

}

void dribblerIn(){
  digitalWrite(11, LOW);
  digitalWrite(32, HIGH);
  analogWrite(8, 255);
}
void dribblerOut(){
  digitalWrite(11, HIGH);
  digitalWrite(32, LOW);
  analogWrite(8, 255);
}


