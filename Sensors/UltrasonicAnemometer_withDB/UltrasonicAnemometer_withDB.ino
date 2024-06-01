#include <SoftwareSerial.h>
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "FIREBASE.h"
#include "UltrasonicAnemometer.h"

//for firebase
unsigned long sendDataPrevMillis = 0;

//for ultrasonic anemometer
#define baudRate 115200


void setup() {
  Serial.begin(baudRate);
  ultrasonicAnemometer.begin(4800);

  pinMode(MAX485, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  WiFi_Init();

  //Ultrasonic anemometer init
  Serial.print("Initializing Ultrasonic Anemometer");
  for (int i = 0; i < 10; i++) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");

  digitalWrite(MAX485, HIGH);
}

void loop() {
  ultrasonicAnemometer_bytesync();
  // Now that synchronization is achieved, proceed to read the rest of the data frame

  // Transmit the request to the sensor
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  ultrasonicAnemometerWrite();

  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(10);

  // Wait until we have the expected number of bytes or timeout
  unsigned long startTime = millis();
  while (ultrasonicAnemometer.available() < 9 && millis() - startTime < 1000) {
    delay(1);
  }

  readUltrasonicAnemometer();

  //Send average data to DB
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    float AveWindSpeed_ms = TotalWindSpeed_ms / 5;
    float AveWindSpeed_kph = TotalWindSpeed_kph / 5;
    float AveWindDirection = TotalWindDirection / 5;

    sendToDbFloat("anemometer/AveWindDirection", AveWindDirection);
    sendToDbFloat("anemometer/AveWindSpeed_ms", AveWindSpeed_ms);
    sendToDbFloat("anemometer/AveWindSpeed_kph", AveWindSpeed_kph);
  }

  delay(1000);
}