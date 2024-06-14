/**
 * ESP-A
 *
 * This table shows the pin connections in ESP-A
 *-----------------------------------------------------------------------------------
 * Pin          | Description     | Pin             | Description
 *--------------|-----------------|-----------------|--------------------------------
 * CLK          | [x]             | 5V              | 5 Vin
 * SD0          | [x]             | CMD             | [x]
 * SD1          | [x]             | SD3             | [x]
 * P15          | [Strapping pin] | SD2             | [x]
 * P2           | [Strapping pin] | P13             | Voltage Divider A (SOLAR)
 * P0           | [Strapping pin] | P12             | [Strapping pin]
 * P4           | [-]             | P14             | Voltage Divider B (WIND)
 * P16/RX2      | PZEM-A RX       | P27             | Voltage Divider C (BATTERY)
 * P17/RX2      | PZEM-A TX       | P26             | ACS712-A (SOLAR)
 * P5/CS        | 485 RO          | P25             | ACS712-B (WIND)
 * P18/CLK      | 485 RE          | P33             | RX to ESP-B
 * P19/MISO     | 485 DE          | P32             | TX to ESP-B
 * P21/SDA      | 485 DI          | P35             | [x]
 * P3/RX0       | [x] Used in BOOT| P34             | [x]
 * P1/TX0       | [x] Used in BOOT| P39/SVN         | [x]
 * P22/SCL      | [-] Not ADC     | P36/SVP         | [x]
 * P23/MOSI     | [-] Not ADC     | EN              | [x]
 * ----------------------------------------------------------------------------------
 */

#include <Arduino.h>

#include <HardwareSerial.h>
#define ESPB_RX_pin 33
#define ESPB_TX_pin 32
ulong previousMillis = 0;
const int blink = 25;
const long sendInterval = 1000 - blink;
HardwareSerial ESP32_B(1); // UART1 (Serial1) channel

#include <UltrasonicAnemometer.h>
#define DI 13
#define DE 12
#define RE 14
#define RO 27
#define MAX485 26
UltrasonicAnemometer Anemometer(RO, DI, DE, RE, MAX485);

#include <VoltageDivider.h>
#define SolarVoltageSensorPin 13
#define Solar_R1 220000.0
#define Solar_R2 10000.0
#define SolarVoltageFactor (Solar_R1 / Solar_R2) + 1 // Modify this for adjusting the reading precision
VoltageDivider SolarVoltageSensor(SolarVoltageSensorPin);
#define BatterySensorPin 27
#define Battery_R1 220000.0
#define Battery_R2 10000.0
#define BatterMinVoltage 10.5
#define BatteryMaxVoltage 13.8
#define BatteryVoltageFactor 4.919 // Modify this for adjusting the reading precision
VoltageDivider BatteryVoltageSensor(BatterySensorPin);

#include <PZEM004Tv30.h>
#define windPZEM_RX 16
#define windPZEM_TX 17
PZEM004Tv30 PZEM_Wind(&Serial2, windPZEM_TX, windPZEM_RX); // UART2 (Serial2) channel

#include <MovingAverageFilter.h>
#define NumberOfSamples 15
MovingAverageFilter SolarVoltageSensorFilter(NumberOfSamples);
MovingAverageFilter WindSpeedFilter(NumberOfSamples);
MovingAverageFilter WindVoltageFilter(NumberOfSamples);
MovingAverageFilter WindCurrentFilter(NumberOfSamples);
MovingAverageFilter WindPowerFilter(NumberOfSamples);
MovingAverageFilter WindEnergyFilter(NumberOfSamples);
MovingAverageFilter WindDirectionFilter(NumberOfSamples);
MovingAverageFilter BatteryVoltageSensorFilter(NumberOfSamples);

struct SensorData
{
  float SolarVoltage;
  float WindVoltage;
  float WindCurrent;
  float WindEnergy;
  float WindSpeed_MS;
  int WindDirection;
  float BatteryVoltage;
  float BatteryPercentage;
  // Add more fields if needed
};
SensorData sensorData;

void readSensorsData();
void blinkLED();

void setup()
{
  Serial.begin(115200);                                        // Console Logging
  ESP32_B.begin(115200, SERIAL_8N1, ESPB_TX_pin, ESPB_RX_pin); // ESP-B UART Communication
  Serial2.begin(115200, SERIAL_8N1, windPZEM_TX, windPZEM_RX); // PZEM-Wind Turbine
  pinMode(LED_BUILTIN, OUTPUT);                                // Transmitter Indicator

  Anemometer.begin();                     // Setup Anemometer
  Anemometer.setWindDirectionOffset(195); // Set Anemometer Direction Offset

  SolarVoltageSensor.begin(Solar_R1, Solar_R2);
  SolarVoltageSensor.setDivisionFactor(SolarVoltageFactor);

  BatteryVoltageSensor.begin(Battery_R1, Battery_R2);
  BatteryVoltageSensor.setDivisionFactor(BatteryVoltageFactor);
}

void loop()
{
  readSensorsData();
  ulong currentMillis = millis();

  if (currentMillis - previousMillis >= sendInterval)
  {
    previousMillis = currentMillis;
    ESP32_B.println("Hello from ESP32-A");
    blinkLED();
  }
}

void readSensorsData()
{
  Anemometer.update();

  float SolarVoltage = SolarVoltageSensor.readVoltage();
  float WindVoltage = PZEM_Wind.voltage();
  float WindCurrent = PZEM_Wind.current();
  float WindPower = PZEM_Wind.power();
  float WindEnergy = PZEM_Wind.energy();
  float WindSpeed_MS = Anemometer.getWindSpeed_ms();
  int WindDirection = Anemometer.getWindDirection();
  float BatteryVoltage = BatteryVoltageSensor.readVoltage();
  float BatteryPercentage = BatteryVoltageSensor.getPercentage(BatterMinVoltage, BatteryMaxVoltage);

  sensorData.SolarVoltage = SolarVoltageSensorFilter.addReading(SolarVoltage);
  sensorData.WindVoltage = WindVoltageFilter.addReading(WindVoltage);
  sensorData.WindCurrent = WindCurrentFilter.addReading(WindCurrent);
  sensorData.WindEnergy = WindEnergyFilter.addReading(WindEnergy);
  sensorData.WindSpeed_MS = WindSpeedFilter.addReading(WindSpeed_MS);
  sensorData.WindDirection = WindDirectionFilter.addReading(WindDirection);
  sensorData.BatteryVoltage = BatteryVoltageSensorFilter.addReading(BatteryVoltage);
  sensorData.BatteryPercentage = BatteryPercentage;
}

void blinkLED()
{
  digitalWrite(LED_BUILTIN, HIGH); // Succesfully Sent!
  delay(blink);
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
}