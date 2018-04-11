#include <QTRSensors.h>
#include <EEPROM.h>

#define NUM_SENSORS             4  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2
#define INTERRUPT_PIN           4    //which pin on the teensy 3.2 is sending out the interrupt to the master

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {
  0, 1, 2, 3, 4, 5
}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];
byte calibrationValues[NUM_SENSORS * 4];
boolean calibrated = false;
int medianValues[NUM_SENSORS];
int averageValues[NUM_SENSORS];
boolean onLine[NUM_SENSORS];



void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(INTERRUPT_PIN, OUTPUT);
  digitalWrite(INTERRUPT_PIN, LOW);

  calibrateQTR();
  delay(1000);
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  qtra.read(sensorValues);
  for (int i = 0; i < NUM_SENSORS; i++) {
    averageValues[i] -= averageValues[i] / 5;
    averageValues[i] += sensorValues[i] / 5;
    if (averageValues[i] < medianValues[i]) {
      onLine[i] = true;
    } else {
      onLine[i] = false;
    }
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    if (onLine[i]) {
      Serial.print(onLine[i]);
      Serial.print('\t');
      digitalWrite(INTERRUPT_PIN, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(INTERRUPT_PIN, LOW);
      break;
    }
  }
  Serial.println();
  digitalWrite(13, LOW);
}


void readCalibrationValues() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    calibrationValues[(4 * i)] = lowByte(qtra.calibratedMaximumOn[i]);
    calibrationValues[(4 * i) + 1] = highByte(qtra.calibratedMaximumOn[i]);
    calibrationValues[(4 * i) + 2] = lowByte(qtra.calibratedMinimumOn[i]);
    calibrationValues[(4 * i) + 3] = highByte(qtra.calibratedMinimumOn[i]);
  }
}

void calibrateQTR() {
  char serialInput = 0;
  int timer = millis();
  Serial.println("Type c if you would like to calibrate. If not, do nothing");
  while ((timer + 5000) > millis())  {
    if (Serial.available() > 0) {    // is a character available?
      serialInput = Serial.read();       // get the character
      if (serialInput == 'c') {
        Serial.println("CALLIBRATING");
        digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
        for (int i = 0; i < 1000; i++)  // make the calibration take about 10 seconds
        {
          qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
        }
        calibrated = true;
        writeCalibrationDataToEEPROM();
        setMedianValues();
        digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
        Serial.println("done calibrating");
      }
    }
  }
  if (calibrated == false) {
    readCalibrationDataFromEEPROM();
    setMedianValues();
  }
}

void writeCalibrationDataToEEPROM() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    calibrationValues[(4 * i)] = lowByte(qtra.calibratedMaximumOn[i]);
    calibrationValues[(4 * i) + 1] = highByte(qtra.calibratedMaximumOn[i]);
    calibrationValues[(4 * i) + 2] = lowByte(qtra.calibratedMinimumOn[i]);
    calibrationValues[(4 * i) + 3] = highByte(qtra.calibratedMinimumOn[i]);
  }
  for (int i =  0; i < NUM_SENSORS * 4; i++) {
    EEPROM.write(i, calibrationValues[i]);
  }
}

void readCalibrationDataFromEEPROM() {
  Serial.println("reading from eeprom");
  for (int i =  0; i < NUM_SENSORS * 4; i++) {
    calibrationValues[i] = EEPROM.read(i);
  }
  printCalibrationValues();
  Serial.println("finished eeprom 'calibration'");
  calibrated = true;
}


void printCalibrationValues() {
  for (int i = 0; i < NUM_SENSORS * 4; i++) {
    Serial.println(calibrationValues[i]);
  }
}


void setMedianValues() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    int mx = word(calibrationValues[(4 * i) + 1], calibrationValues[(4 * i)]);
    int mn = word(calibrationValues[(4 * i) + 3], calibrationValues[(4 * i) + 2]);
    medianValues[i] = (mx + mn) / 2;
  }
}

