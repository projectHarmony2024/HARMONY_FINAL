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
#include <SoftwareSerial.h>
#define DI 5
#define DE 18
#define RE 19
#define RO 21
// UltrasonicAnemometer anemometer(DI, DE, RE, RO);
const byte anemometer[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};
byte values[9];

SoftwareSerial ultrasonicAnemometer(RO, DI, false);

#include <VoltageDivider.h>
#define Vref 3.3
#define solarVoltagePin 14
#define solarR1 225000.0
#define solarR2 9960.0
#define solarVoltageOffset 1.0299
VoltageDivider solar(solarVoltagePin, solarR1, solarR2, solarVoltageOffset, Vref);
#define windVoltagePin 13
#define windR1 226000.0
#define windR2 9920.0
#define windVoltageOffset 29.4525
float vIn;
float vOut;
float voltageSensorVal;
// VoltageDivider wind(solarVoltagePin, solarR1, solarR2, solarVoltageOffset, Vref);
#define batteryVoltagePin 27
#define batteryR1 29800.0
#define batteryR2 7500.0
#define batteryVoltageOffset 1.10567
#define batMinVolt 10.5
#define batMaxVolt 13.7
VoltageDivider battery(batteryVoltagePin, batteryR1, batteryR2, batteryVoltageOffset, Vref);

#define SolarCurrentPin 26
#define WindCurrentPin 25
float sensorValue = 0;
const float calibrationFactor = 100.0;           // 100mV per Ampere for ACS712-20A
const float ACS712_FULL_SCALE_CURRENT = 20;      // 20A for ACS712-20A
const float SOLAR_VOLTAGE_DIVIDER_RATIO = 1.865; // Adjust this based on your voltage divider
const float WIND_VOLTAGE_DIVIDER_RATIO = 1.79;
const float ZERO_CURRENT_VOLTAGE = 2.4; // Assuming 2.5V at zero current (adjust if needed)

void blinkLED(int);

void setup()
{
  Serial.begin(115200);
  ESP32_B.begin(115200, SERIAL_8N1, TX_pin, RX_pin); // TX=17, RX=16
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SolarCurrentPin, INPUT);
  pinMode(WindCurrentPin, INPUT);

  solar.begin();
  // wind.begin();
  battery.begin();
  ultrasonicAnemometer.begin(4800);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  // anemometer.begin();
  // anemometer.setWindDirectionOffset(195);
}

ulong previousMillis = 0;
float Wind_Speed_m_s, Wind_Speed_kph;
int Wind_Direction;

void loop()
{
  while (true)
  {
    // Check for the start of frame marker
    if (ultrasonicAnemometer.peek() == -1)
    {
      // Start of frame detected, exit the synchronization loop
      break;
    }
    // Discard any bytes until the start of frame is found
    ultrasonicAnemometer.read();
  }

  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  ultrasonicAnemometer.write(anemometer, sizeof(anemometer));

  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(10);

  unsigned long startTime = millis();
  while (ultrasonicAnemometer.available() < 9 && millis() - startTime < 1000)
  {
    delay(1);
  }

  if (ultrasonicAnemometer.available() >= 9)
  {
    // Read the response
    byte index = 0;
    while (ultrasonicAnemometer.available() && index < 9)
    {
      values[index] = ultrasonicAnemometer.read();
      // Serial.print(values[index], HEX);
      // Serial.print(" ");
      index++;
    }
    // Serial.println();

    // Parse the Wind Speed value
    int Wind_Speed_Int = int(values[3] << 8 | values[4]);
    Wind_Speed_m_s = Wind_Speed_Int / 100.0;
    Wind_Speed_kph = Wind_Speed_m_s * 3.6; // Conversion to km/h

    // Parse the Wind Direction value
    Wind_Direction = int(values[5] << 8 | values[6]);

    if (Wind_Speed_m_s <= 0)
    {
      Wind_Speed_kph = 0;
      Wind_Direction = 0;
    }
  }
  else
  {
    Serial.println("Sensor timeout or incomplete frame");
  }

  voltageSensorVal = analogRead(windVoltagePin);
  vOut = (voltageSensorVal / 4095) * Vref;
  vIn = vOut * windVoltageOffset;

  int SolarAnalogValue = analogRead(SolarCurrentPin);
  int WindAnalogValue = analogRead(WindCurrentPin);

  // Convert analog reading to voltage (assuming 3.3V ADC reference)
  float SolarSensorCurrent = SolarAnalogValue * (3.3 / 4095.0);
  float WindSensorCurrent = WindAnalogValue * (3.3 / 4095.0);

  // Adjust for the voltage divider
  SolarSensorCurrent *= SOLAR_VOLTAGE_DIVIDER_RATIO;
  WindSensorCurrent *= WIND_VOLTAGE_DIVIDER_RATIO;

  // Calculate the offset voltage from the zero-current voltage
  float SolarOffsetVoltage = SolarSensorCurrent - ZERO_CURRENT_VOLTAGE;
  float WindOffsetVoltage = WindSensorCurrent - ZERO_CURRENT_VOLTAGE;

  // Calculate current (mV per Ampere)
  float SolarCurrent = SolarOffsetVoltage / (calibrationFactor / 1000.0);
  float WindCurrent = WindOffsetVoltage / (calibrationFactor / 1000.0);
  if (SolarCurrent < 0.2)
  {
    SolarCurrent = 0;
  }
  if (WindCurrent < 0.2)
  {
    WindCurrent = 0;
  }

  float solarVoltage = solar.readVoltage();
  float solarCurrent = SolarCurrent;
  float windVoltage;
  float windCurrent = WindCurrent;
  float windSpeed_kph = Wind_Speed_kph;
  int windDirection = Wind_Direction;
  float batteryVoltage = battery.readVoltage();
  float batteryPercentage = battery.readPercentage(batMinVolt, batMaxVolt);

  windVoltage = windSpeed_kph * 1.488416988;

  if (windVoltage < 0)
  {
    windVoltage = 0;
  }

  if (millis() - previousMillis >= 500)
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
