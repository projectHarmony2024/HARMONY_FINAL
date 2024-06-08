/*=======================================================================================================
▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
▐                                                                                                       ▌
▐ ███████╗███████╗██████╗ ██████╗ ██████╗                █████╗        ███╗   ███╗ █████╗ ██╗███╗   ██╗ ▌
▐ ██╔════╝██╔════╝██╔══██╗╚════██╗╚════██╗              ██╔══██╗██╗    ████╗ ████║██╔══██╗██║████╗  ██║ ▌
▐ █████╗  ███████╗██████╔╝ █████╔╝ █████╔╝    █████╗    ███████║╚═╝    ██╔████╔██║███████║██║██╔██╗ ██║ ▌
▐ ██╔══╝  ╚════██║██╔═══╝  ╚═══██╗██╔═══╝     ╚════╝    ██╔══██║██╗    ██║╚██╔╝██║██╔══██║██║██║╚██╗██║ ▌
▐ ███████╗███████║██║     ██████╔╝███████╗              ██║  ██║╚═╝    ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║ ▌
▐ ╚══════╝╚══════╝╚═╝     ╚═════╝ ╚══════╝              ╚═╝  ╚═╝       ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ▌
▐                                                                                                       ▌
▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
=======================================================================================================*/

#include <SPI.h>
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

/* ========== CONFIGURATION ========== */
// ESP-NOW Broadcast Address. Replace with ESP32-B MAC Address
uint8_t broadcastAddress[] = {0xCC, 0x7B, 0x5C, 0x26, 0xD6, 0x7C};

// RTC DS3231
#include <RTCManager.h>
RTCManager RTCDS3231;

// // ULTRASONIC ANEMOMETER
// #include <UltrasonicAnemometer.h>
// #define DI 25
// #define DE 26
// #define RE 27
// #define RO 14
// #define MAX485_Vcc 33
// UltrasonicAnemometer Anemometer(RO, DI, DE, RE, MAX485_Vcc);

// VOLTAGE SENSOR
#include <VoltageDivider.h>
// Solar
#define SolarVoltage_pin 35
#define Solar_R1 225000.0
#define Solar_R2 9960.0
// Wind
#define WindVoltage_pin 32
#define Wind_R1 224000.0
#define Wind_R2 9860.0
// Battery
#define BatteryVoltage_pin 36
#define Battery_R1 200000.0
#define Battery_R2 10000.0
#define BattMinVolt 10.5
#define BattMaxVolt 13.9
// Others
#define ADC_Res 4095
#define V_Ref 3.3
VoltageDivider SolarVoltage(SolarVoltage_pin, Solar_R1, Solar_R2, ADC_Res, V_Ref);
VoltageDivider WindVoltage(WindVoltage_pin, Wind_R1, Wind_R2, ADC_Res, V_Ref);
VoltageDivider BatteryVoltage(BatteryVoltage_pin, Battery_R1, Battery_R2, ADC_Res, V_Ref);

// ACS712-20A CURRENT SENSOR
#include <CurrentSensor.h>
#define SolarACSpin 39
#define WindACSpin 34
#define ADC_Res 4095
#define V_Ref 3.3
#define MV_PER_AMP 100
CurrentSensor SolarACS(SolarACSpin, V_Ref, ADC_Res, MV_PER_AMP);
CurrentSensor WindACS(WindACSpin, V_Ref, ADC_Res, MV_PER_AMP);

// PZEM004T V3 ENERGY SENSOR
#include <PZEM004Tv30.h>
#define PZEM_A_RX_PIN 5
#define PZEM_A_TX_PIN 18
PZEM004Tv30 PZEM1(&Serial2, PZEM_A_RX_PIN, PZEM_A_TX_PIN);

#define PZEM_B_RX_PIN 16
#define PZEM_B_TX_PIN 17
PZEM004Tv30 PZEM2(&Serial1, PZEM_B_RX_PIN, PZEM_B_TX_PIN);

// MOVING AVERAGE FILTER
#include <MovingAverageFilter.h>
enum SensorChannel
{
  SOLAR_VOLTAGE,
  SOLAR_CURRENT,
  WIND_VOLTAGE,
  WIND_CURRENT,
  BATTERY_VOLTAGE,
  BATTERY_PERCENTAGE,
  // WIND_SPEED_MS,
  // WIND_SPEED_KPH,
  // WIND_DIRECTION,
  PZEM_A_VOLTAGE,
  PZEM_A_CURRENT,
  PZEM_A_POWER,
  PZEM_A_ENERGY,
  PZEM_A_FREQUENCY,
  PZEM_A_POWERFACTOR,
  PZEM_B_VOLTAGE,
  PZEM_B_CURRENT,
  PZEM_B_POWER,
  PZEM_B_ENERGY,
  PZEM_B_FREQUENCY,
  PZEM_B_POWERFACTOR,
  NUM_OF_CHANNELS
};
#define WINDOW_SIZE 15
MovingAverageFilter Filter(WINDOW_SIZE, NUM_OF_CHANNELS);

// SENSORS DATA
struct SmoothedSensorReadings
{
  float Solar_Voltage;
  float Solar_Current;
  float Wind_Voltage;
  float Wind_Current;
  // float WindSpeed_ms;
  // float WindSpeed_kph;
  // int Wind_Direction;
  float Battery_Voltage;
  int Battery_Percentage;
  float PZEM_A_Voltage;
  float PZEM_A_Current;
  float PZEM_A_Power;
  float PZEM_A_Energy;
  float PZEM_A_Frequency;
  float PZEM_A_PowerFactor;
  float PZEM_B_Voltage;
  float PZEM_B_Current;
  float PZEM_B_Power;
  float PZEM_B_Energy;
  float PZEM_B_Frequency;
  float PZEM_B_PowerFactor;
  // float PZEM_C_Voltage;
  // float PZEM_C_Current;
  // float PZEM_C_Power;
  // float PZEM_C_Energy;
  // float PZEM_C_Frequency;
  // float PZEM_C_PowerFactor;
  String RTC_Date;
  String RTC_Time;
  String RTC_Timestamp;
  int RTC_TimeInt;
};
SmoothedSensorReadings SensorData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  // Serial.print("\r\nLast Packet Send Status:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// FUNCTIONS
void SensorReadings();
void DisplayReadings();
/* ========== END OF CONFIGURATION ========== */

/* ========== SETUP ========== */
void setup()
{
  RTCDS3231.init();
  RTCDS3231.setTimezoneOffset(4);

  // Anemometer.begin();
  // Anemometer.setDirectionOffset(195);

  SolarACS.begin();
  WindACS.begin();
  BatteryVoltage.setBatteryVoltageRange(BattMinVolt, BattMaxVolt);

  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}
/* ========== END OF SETUP ========== */

ulong previousMillis = 0;

/* ========== LOOP ========== */
void loop()
{
  SensorData.RTC_Date = RTCDS3231.getDate("YYYY:MM:DD");
  SensorData.RTC_Time = RTCDS3231.getTime("HH:MMp");
  SensorData.RTC_TimeInt = RTCDS3231.getTimeInt();
  // SensorData.RTC_Date = "2024-06-08";
  // SensorData.RTC_Time = "10:48";

  ulong currentMillis = millis();

  SensorReadings();

  if ((currentMillis - previousMillis >= 1000))
  {
    previousMillis = currentMillis;

    SensorData.Solar_Voltage;
    SensorData.Solar_Current;
    SensorData.Wind_Voltage;
    SensorData.Wind_Current;
    SensorData.Battery_Voltage;
    SensorData.Battery_Percentage;
    SensorData.PZEM_A_Voltage;
    SensorData.PZEM_A_Current;
    SensorData.PZEM_A_Power;
    SensorData.PZEM_A_Energy;
    SensorData.PZEM_A_Frequency;
    SensorData.PZEM_A_PowerFactor;
    SensorData.PZEM_B_Voltage;
    SensorData.PZEM_B_Current;
    SensorData.PZEM_B_Power;
    SensorData.PZEM_B_Energy;
    SensorData.PZEM_B_Frequency;
    SensorData.PZEM_B_PowerFactor;
    SensorData.RTC_Date;
    SensorData.RTC_Time;
    SensorData.RTC_Timestamp;

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&SensorData, sizeof(SensorData));

    // if (result == ESP_OK)
    // {
    //   Serial.println("Sent with success");
    // }
    // else
    // {
    //   Serial.println("Error sending the data");
    // }
    DisplayReadings();
  }
}
/* ========== END OF LOOP ========== */

/* ========== SENSOR READINGS ========== */
void SensorReadings()
{
  // RAW READINGS
#define SAMPLEDATA 0
#if SAMPLEDATA == 1
  static float Solar_Voltage = SolarVoltage.readVoltage();
  static float Solar_Current = SolarACS.readCurrent();
  static float Wind_Voltage = WindVoltage.readVoltage();
  static float Wind_Current = WindACS.readCurrent();
  // static float WindSpeed_ms;
  // static float WindSpeed_kph;
  // static int Wind_Direction;
  static float Battery_Voltage = BatteryVoltage.readVoltage();
  static int Battery_Percentage = BatteryVoltage.readBatteryPercentage();
  static float PZEM1_Voltage = PZEM1.voltage();
  static float PZEM1_Current = PZEM1.current();
  static float PZEM1_Power = PZEM1.power();
  static float PZEM1_Energy = PZEM1.energy();
  static float PZEM1_Frequency = PZEM1.frequency();
  static float PZEM1_PowerFactor = PZEM1.pf();
  static float PZEM2_Voltage = PZEM2.voltage();
  static float PZEM2_Current = PZEM2.current();
  static float PZEM2_Power = PZEM2.power();
  static float PZEM2_Energy = PZEM2.energy();
  static float PZEM2_Frequency = PZEM2.frequency();
  static float PZEM2_PowerFactor = PZEM2.pf();

  if (!isnan(Anemometer.readData()))
  {
    // Anemometer Data successfully read
    WindSpeed_ms = Anemometer.getWindSpeed_ms();
    WindSpeed_kph = Anemometer.getWindSpeed_kph();
    Wind_Direction = Anemometer.getWind_Direction();
  }
  else
  {
    // Handle error: No anemometer data received
    // windSpeed_ms and wind_Direction will be nan
    Serial.printf("Anemometer Error: No data received\n");
  }

  // ADD RAW READINGS TO MOVING AVERAGE FILTER
  Filter.addReading(Solar_Voltage, SOLAR_VOLTAGE);
  Filter.addReading(Solar_Current, SOLAR_CURRENT);
  Filter.addReading(Wind_Voltage, WIND_VOLTAGE);
  Filter.addReading(Wind_Current, WIND_CURRENT);
  Filter.addReading(WindSpeed_ms, WIND_SPEED_MS);
  Filter.addReading(WindSpeed_kph, WIND_SPEED_KPH);
  Filter.addReading(Wind_Direction, WIND_DIRECTION);
  Filter.addReading(Battery_Voltage, BATTERY_VOLTAGE);
  Filter.addReading(Battery_Percentage, BATTERY_PERCENTAGE);
  Filter.addReading(PZEM1_Voltage, PZEM_A_VOLTAGE);
  Filter.addReading(PZEM1_Current, PZEM_A_CURRENT);
  Filter.addReading(PZEM1_Power, PZEM_A_POWER);
  Filter.addReading(PZEM1_Energy, PZEM_A_ENERGY);
  Filter.addReading(PZEM1_Frequency, PZEM_A_FREQUENCY);
  Filter.addReading(PZEM1_PowerFactor, PZEM_A_POWERFACTOR);
  Filter.addReading(PZEM2_Voltage, PZEM_B_VOLTAGE);
  Filter.addReading(PZEM2_Current, PZEM_B_CURRENT);
  Filter.addReading(PZEM2_Power, PZEM_B_POWER);
  Filter.addReading(PZEM2_Energy, PZEM_B_ENERGY);
  Filter.addReading(PZEM2_Frequency, PZEM_B_FREQUENCY);
  Filter.addReading(PZEM2_PowerFactor, PZEM_B_POWERFACTOR);

  // GET SMOOTHED READINGS AND UPDATE STRUCT DATA
  SensorData.Solar_Voltage = Filter.getAverage(SOLAR_VOLTAGE);
  SensorData.Solar_Current = Filter.getAverage(SOLAR_CURRENT);
  SensorData.Wind_Voltage = Filter.getAverage(WIND_VOLTAGE);
  SensorData.Wind_Current = Filter.getAverage(WIND_CURRENT);
  // SensorData.WindSpeed_ms = Filter.getAverage(WIND_SPEED_MS);
  // SensorData.WindSpeed_kph = Filter.getAverage(WIND_SPEED_KPH);
  SensorData.Battery_Voltage = Filter.getAverage(BATTERY_VOLTAGE);
  SensorData.Battery_Percentage = Filter.getAverage(BATTERY_PERCENTAGE);
  SensorData.PZEM_A_Voltage = Filter.getAverage(PZEM_A_VOLTAGE);
  SensorData.PZEM_A_Current = Filter.getAverage(PZEM_A_CURRENT);
  SensorData.PZEM_A_Power = Filter.getAverage(PZEM_A_POWER);
  SensorData.PZEM_A_Energy = Filter.getAverage(PZEM_A_ENERGY);
  SensorData.PZEM_A_Frequency = Filter.getAverage(PZEM_A_FREQUENCY);
  SensorData.PZEM_A_PowerFactor = Filter.getAverage(PZEM_A_POWERFACTOR);
  SensorData.PZEM_B_Voltage = Filter.getAverage(PZEM_B_VOLTAGE);
  SensorData.PZEM_B_Current = Filter.getAverage(PZEM_B_CURRENT);
  SensorData.PZEM_B_Power = Filter.getAverage(PZEM_B_POWER);
  SensorData.PZEM_B_Energy = Filter.getAverage(PZEM_B_ENERGY);
  SensorData.PZEM_B_Frequency = Filter.getAverage(PZEM_B_FREQUENCY);
  SensorData.PZEM_B_PowerFactor = Filter.getAverage(PZEM_B_POWERFACTOR);

#else
  SensorData.Solar_Voltage = random(0, 60);
  SensorData.Solar_Current = random(0, 60);
  SensorData.Wind_Voltage = random(0, 60);
  SensorData.Wind_Current = random(0, 60);
  SensorData.Battery_Voltage = random(0, 60);
  SensorData.Battery_Percentage = random(0, 60);

  float PZEM1_Voltage = PZEM1.voltage();
  float PZEM1_Current = PZEM1.current();
  float PZEM1_Power = PZEM1.power();
  float PZEM1_Energy = PZEM1.energy();
  float PZEM1_Frequency = PZEM1.frequency();
  float PZEM1_PowerFactor = PZEM1.pf();
  Filter.addReading(PZEM1_Voltage, PZEM_A_VOLTAGE);
  Filter.addReading(PZEM1_Current, PZEM_A_CURRENT);
  Filter.addReading(PZEM1_Power, PZEM_A_POWER);
  Filter.addReading(PZEM1_Energy, PZEM_A_ENERGY);
  Filter.addReading(PZEM1_Frequency, PZEM_A_FREQUENCY);
  Filter.addReading(PZEM1_PowerFactor, PZEM_A_POWERFACTOR);
  SensorData.PZEM_A_Voltage = Filter.getAverage(PZEM_A_VOLTAGE);
  SensorData.PZEM_A_Current = Filter.getAverage(PZEM_A_CURRENT);
  SensorData.PZEM_A_Power = Filter.getAverage(PZEM_A_POWER);
  SensorData.PZEM_A_Energy = Filter.getAverage(PZEM_A_ENERGY);
  SensorData.PZEM_A_Frequency = Filter.getAverage(PZEM_A_FREQUENCY);
  SensorData.PZEM_A_PowerFactor = Filter.getAverage(PZEM_A_POWERFACTOR);
  // SensorData.PZEM_A_Voltage = random(0, 60);
  // SensorData.PZEM_A_Current = random(0, 60);
  // SensorData.PZEM_A_Power = random(0, 60);
  // SensorData.PZEM_A_Energy = random(0, 60);
  // SensorData.PZEM_A_Frequency = random(0, 60);
  // SensorData.PZEM_A_PowerFactor = random(0, 60);
  SensorData.PZEM_B_Voltage = random(0, 60);
  SensorData.PZEM_B_Current = random(0, 60);
  SensorData.PZEM_B_Power = random(0, 60);
  SensorData.PZEM_B_Energy = random(0, 60);
  SensorData.PZEM_B_Frequency = random(0, 60);
  SensorData.PZEM_B_PowerFactor = random(0, 60);
#endif
}
/* ========== END OF SENSOR READINGS ========== */

/* ========== DISPLAY READINGS ========== */
// For Debugging Only
void DisplayReadings()
{
  Serial.println("\n=== TIME ===");
  Serial.printf("Date: %s  Time: %s\n", SensorData.RTC_Date.c_str(), SensorData.RTC_Time.c_str());
  Serial.println("=== SOLAR ===");
  Serial.printf("Voltage: %0.2f  Current: %0.2f\n", SensorData.Solar_Voltage, SensorData.Solar_Current);
  Serial.println("=== WIND ===");
  // Serial.printf("Voltage: %0.2f  Current: %0.2f  Wind Speed: %0.2fkph  Wind Direction: %d\n", SensorData.Wind_Voltage, SensorData.Wind_Current, SensorData.WindSpeed_kph, SensorData.Wind_Direction);
  Serial.printf("Voltage: %0.2f  Current: %0.2f\n", SensorData.Wind_Voltage, SensorData.Wind_Current);
  Serial.println("=== BATTERY ===");
  Serial.printf("Voltage: %0.2f  Percentage: %d%\n", SensorData.Battery_Voltage, SensorData.Battery_Percentage);
  Serial.println("=== ENERGY CONSUMPTION ===");
  Serial.printf("PZEM-A: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorData.PZEM_A_Voltage, SensorData.PZEM_A_Current, SensorData.PZEM_A_Power, SensorData.PZEM_A_Energy, SensorData.PZEM_A_Frequency, SensorData.PZEM_A_PowerFactor);
  Serial.printf("PZEM-B: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorData.PZEM_B_Voltage, SensorData.PZEM_B_Current, SensorData.PZEM_B_Power, SensorData.PZEM_B_Energy, SensorData.PZEM_B_Frequency, SensorData.PZEM_B_PowerFactor);
  Serial.printf("PZEM-C: 0.00 , 0.00 , 0.00 , 0.00 , 0.00 , 0.00\n");
  Serial.printf("Wind Speed: 0.00  Wind Direction: 0.00\n");
  Serial.println(SensorData.RTC_TimeInt);
}
/* ========== END OF DISPLAY READINGS ========== */

// void Read_ESP32B_PZEM_C()
// {
//   if (Serial2.available())
//   {
//     String receivedData = Serial2.readStringUntil('\n');
//     int commaIndex1 = receivedData.indexOf(',');
//     int commaIndex2 = receivedData.indexOf(',', commaIndex1 + 1);
//     int commaIndex3 = receivedData.indexOf(',', commaIndex2 + 1);
//     int commaIndex4 = receivedData.indexOf(',', commaIndex3 + 1);
//     int commaIndex5 = receivedData.indexOf(',', commaIndex4 + 1);

//     SensorData.PZEM_C_Voltage = receivedData.substring(0, commaIndex1).toFloat();
//     SensorData.PZEM_C_Current = receivedData.substring(commaIndex1 + 1, commaIndex2).toFloat();
//     SensorData.PZEM_C_Power = receivedData.substring(commaIndex2 + 1, commaIndex3).toFloat();
//     SensorData.PZEM_C_Energy = receivedData.substring(commaIndex3 + 1, commaIndex4).toFloat();
//     SensorData.PZEM_C_Frequency = receivedData.substring(commaIndex4 + 1, commaIndex5).toFloat();
//     SensorData.PZEM_C_PowerFactor = receivedData.substring(commaIndex5 + 1).toFloat();

// Serial.print("Received PZEM_C Voltage: ");
// Serial.println(SensorData.PZEM_C_Voltage);
// Serial.print("Received PZEM_C Current: ");
// Serial.println(SensorData.PZEM_C_Current);
// Serial.print("Received PZEM_C Power: ");
// Serial.println(SensorData.PZEM_C_Power);
// Serial.print("Received PZEM_C Energy: ");
// Serial.println(SensorData.PZEM_C_Energy);
// Serial.print("Received PZEM_C Frequency: ");
// Serial.println(SensorData.PZEM_C_Frequency);
// Serial.print("Received PZEM_C PowerFactor: ");
// Serial.println(SensorData.PZEM_C_PowerFactor);
//   }
// }