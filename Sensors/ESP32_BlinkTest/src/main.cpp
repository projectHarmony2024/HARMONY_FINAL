#include <Arduino.h>
#include "DigitalBlink.h"
#include "AnalogBlink.cpp"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //setupLED();

}

void loop() {
  // put your main code here, to run repeatedly:
  //blinkLED();
  analogBlink();
}
