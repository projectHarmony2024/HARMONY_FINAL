#include "Firebase.h"
#include "UltrasonicAnemometer.h"


#define baudRate 115200


void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudRate);

  setupUltrasonicAnemometer();

  WiFi_Init();

  firebaseUserAuth();

  firebaseConfig();
}

void loop() {
  // put your main code here, to run repeatedly:
  syncAnemometerBytes();
  readAndTransmitUltrasonicAnemometer();
  checkUltrasonicAnemometerNumBytes();
  readDataUltrasonicAnemometer();

  

  delay(1000);
}
