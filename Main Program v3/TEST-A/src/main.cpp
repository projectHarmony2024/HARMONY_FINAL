#include <Arduino.h>

#include <HardwareSerial.h>
#define RX_pin 33
#define TX_pin 32
HardwareSerial ESP32_B(1); // UART1 channel

#include <PZEM004Tv30.h>
#define windPZEM_RX 17
#define windPZEM_TX 16
PZEM004Tv30 windPZEM(Serial2, windPZEM_RX, windPZEM_TX); // UART2 (Serial2) channel

#include <UltrasonicAnemometer.h>
#define DI 21
#define DE 19
#define RE 18
#define RO 5
UltrasonicAnemometer anemometer(DI, DE, RE, RO);

#include <VoltageDivider.h>
#define Vref 3.3
#define solarVoltagePin 14
#define solarR1 225000.0
#define solarR2 9960.0
#define solarVoltageOffset 1.2899
VoltageDivider solar(solarVoltagePin, solarR1, solarR2, solarVoltageOffset, Vref);
#define windVoltagePin 13
#define windR1 226000.0
#define windR2 9920.0
#define windVoltageOffset 3.1525
VoltageDivider wind(solarVoltagePin, solarR1, solarR2, solarVoltageOffset, Vref);
#define batteryVoltagePin 27
#define batteryR1 29800.0
#define batteryR2 7500.0
#define batteryVoltageOffset 0.94567
#define batMinVolt 10.5
#define batMaxVolt 13.8
VoltageDivider battery(batteryVoltagePin, batteryR1, batteryR2, batteryVoltageOffset, Vref);

void blinkLED(int);

void setup()
{
  Serial.begin(115200);
  ESP32_B.begin(115200, SERIAL_8N1, TX_pin, RX_pin); // TX=17, RX=16
  pinMode(LED_BUILTIN, OUTPUT);

  solar.begin();
  wind.begin();
  battery.begin();

  anemometer.begin();
  anemometer.setWindDirectionOffset(195);
}

ulong previousMillis = 0;

void loop()
{
  float solarVoltage = solar.readVoltage();
  float solarCurrent = random(0, 100);
  float windVoltage = wind.readVoltage();
  float windCurrent = windPZEM.current();
  float windSpeed_kph = anemometer.getWindSpeed_kph();
  int windDirection = anemometer.getWindDirection();
  float batteryVoltage = battery.readVoltage();
  float batteryPercentage = battery.readPercentage(batMinVolt, batMaxVolt);

  if (millis() - previousMillis >= 1000)
  {
    previousMillis = millis();
    Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f\n",
                  solarVoltage,
                  solarCurrent,
                  windVoltage,
                  windCurrent,
                  windSpeed_kph,
                  windDirection,
                  batteryVoltage,
                  batteryPercentage);
    ESP32_B.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f\n",
                   solarVoltage,
                   solarCurrent,
                   windVoltage,
                   windCurrent,
                   windSpeed_kph,
                   windDirection,
                   batteryVoltage,
                   batteryPercentage);
    Serial.println("Sent to ESP-B");
    blinkLED(25);
  }
}

void blinkLED(int interval)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(LED_BUILTIN, LOW);
}
