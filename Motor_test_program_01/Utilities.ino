void MotorsInit() {
  // Define pinMode for the pins and set the frequency for timers 1 and 2.
  pinMode(_M1PWM, OUTPUT);
  pinMode(_M1CS, INPUT);
  pinMode(_M1DIR, OUTPUT);
  pinMode(_M2PWM, OUTPUT);
  pinMode(_M2CS, INPUT);
  pinMode(_M2DIR, OUTPUT);
  pinMode(_M3PWM, OUTPUT);
  pinMode(_M3CS, INPUT);
  pinMode(_M3DIR, OUTPUT);
  pinMode(_M4CS, INPUT);
  pinMode(_M4DIR, OUTPUT);

#ifdef MAXONS
  Serial.println("Using Maxon Motors");
  //add change frequency code for Maxon motors
#else
  Serial.println("Using Pololu Motors");
#endif
  //get current offset for each motor
  setSpeeds( 0, 0, 0, 0);
  delay(1);
  _offsetM1 = getM1CurrentReading();
  _offsetM2 = getM2CurrentReading();
  _offsetM3 = getM3CurrentReading();
  _offsetM4 = getM4CurrentReading();
}


