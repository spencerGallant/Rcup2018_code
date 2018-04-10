//LED Defines
#define RED_PIN   21
#define GREEN_PIN 23
#define BLUE_PIN  22

void setup() {
  initializeRGBLED();
}

void loop() {
  setRGB(255, 255, 0);
}


void initializeRGBLED() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(13, HIGH);
}

void setRGB(int red, int green, int blue)
{
  red = 255 - red;
  blue = 255 - blue;
  green = 255 - green;

  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, blue);
  analogWrite(BLUE_PIN, green);
}
