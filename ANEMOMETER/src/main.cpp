#include <Arduino.h>

#include <UltrasonicAnemometer.h>
UltrasonicAnemometer anemometer(21, 5, 18, 9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  anemometer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(anemometer.getWindSpeed_kph());
  delay(500);

}

