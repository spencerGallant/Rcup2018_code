#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

void setup()
{
  int numLidars = 4;
  int lidarPinArray[] = {5, 20, 17, 16}; //5 is a random pin because one lidar in the USA 2018 version doesn't have a slave select pin
  char lidarI2cAdress[] = {0x64, 0x66, 0x68, 0x62}; //0x62 must always be the last one
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(115200);
  initializeLidarDigPins(numLidars, lidarPinArray);
  lidarChangeMultAddress(numLidars, lidarPinArray, lidarI2cAdress);
   Serial.println("loop starting");
}

void loop()
{

  Serial.print("FRONT: ");
  Serial.print(myLidarLite.distance(true, 0x64));
  Serial.print(" LEFT: ");
  Serial.print(myLidarLite.distance(true, 0x66));
  Serial.print(" BACK: ");
  Serial.print(myLidarLite.distance(true, 0x68));
  Serial.print(" RIGHT: ");
  Serial.println(myLidarLite.distance(true, 0x62));
}

void initializeLidarDigPins(int numLidars, int lidarPinArray[]) {
  for (int i = 0; i < numLidars; i++) {
    pinMode(lidarPinArray[i], OUTPUT);
    digitalWrite(lidarPinArray[i], LOW);
  }
}

void lidarChangeMultAddress(int numLidars, int lidarPinArray[], char lidarI2cAdress[]) {
  for (int i = 0; i < numLidars; i++) {
    if (i != 4) {
      digitalWrite(lidarPinArray[i], HIGH);
      delay(200);
      myLidarLite.begin(0, true, 0x62); // Set configuration to default and I2C to 400 kHz
      lidarChangeAddress(lidarI2cAdress[i], 0x62);
      myLidarLite.configure(0, lidarI2cAdress[i]); // Change this number to try out alternate configurations
    }
  }
  for (int i = 0; i < numLidars; i++) {
    digitalWrite(lidarPinArray[i], HIGH);
  }
}
void lidarChangeAddress(char newI2cAddress, char currentLidarLiteAddress) {
  if (newI2cAddress != currentLidarLiteAddress) {
    unsigned char serialNumber[2];
    //  Read two bytes from 0x96 to get the serial number
    myLidarLite.read(0x96, 2, serialNumber, false, currentLidarLiteAddress);
    //  Write the low byte of the serial number to 0x18
    myLidarLite.write(0x18, serialNumber[0], currentLidarLiteAddress);
    //  Write the high byte of the serial number of 0x19
    myLidarLite.write(0x19, serialNumber[1], currentLidarLiteAddress);
    //  Write the new address to 0x1a
    myLidarLite.write(0x1a, newI2cAddress, currentLidarLiteAddress);
    myLidarLite.write(0x1e, 0x08, currentLidarLiteAddress);
  }
  else {
  }
}

