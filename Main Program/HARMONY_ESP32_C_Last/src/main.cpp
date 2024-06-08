/*=========================================================================================================
▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
▐                                                                                                        ▌
▐ ███████╗███████╗██████╗ ██████╗ ██████╗                ██████╗       ██╗      █████╗ ███████╗████████╗ ▌
▐ ██╔════╝██╔════╝██╔══██╗╚════██╗╚════██╗              ██╔════╝██╗    ██║     ██╔══██╗██╔════╝╚══██╔══╝ ▌
▐ █████╗  ███████╗██████╔╝ █████╔╝ █████╔╝    █████╗    ██║     ╚═╝    ██║     ███████║███████╗   ██║    ▌
▐ ██╔══╝  ╚════██║██╔═══╝  ╚═══██╗██╔═══╝     ╚════╝    ██║     ██╗    ██║     ██╔══██║╚════██║   ██║    ▌
▐ ███████╗███████║██║     ██████╔╝███████╗              ╚██████╗╚═╝    ███████╗██║  ██║███████║   ██║    ▌
▐ ╚══════╝╚══════╝╚═╝     ╚═════╝ ╚══════╝               ╚═════╝       ╚══════╝╚═╝  ╚═╝╚══════╝   ╚═╝    ▌
▐                                                                                                        ▌
▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
=========================================================================================================*/

#include <Arduino.h>

/* ========== CONFIGURATION ========== */
// ESP-B
#define ESP_B_init() Serial1.begin(9600, SERIAL_8N1, 14, 12) // ESP-B
#define SendTo_ESP_B(...) Serial1.printf(__VA_ARGS__)

// LVGL
#define LVGL_init() Serial2.begin(115200, SERIAL_8N1, 26, 25) // LVGL
#define SendTo_LVGL(...) Serial2.printf(__VA_ARGS__)

// SENSORS DATA
struct SmoothedSensorReadings
{
  float Solar_Voltage;
  float Solar_Current;
  float Wind_Voltage;
  float Wind_Current;
  float WindSpeed_ms;
  float WindSpeed_kph;
  int Wind_Direction;
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
  float PZEM_C_Voltage;
  float PZEM_C_Current;
  float PZEM_C_Power;
  float PZEM_C_Energy;
  float PZEM_C_Frequency;
  float PZEM_C_PowerFactor;
  String RTC_Date;
  String RTC_Time;
};
SmoothedSensorReadings SensorData;

void Read_ESP_B();
void setup()
{
  // Serial.begin(115200, SERIAL_8N1, 18, 19);  // Serial: GSM Module
  // Serial.begin(115200, SERIAL_8N1);
  ESP_B_init();
  LVGL_init();
}

uint32_t prev_time = 0;

void loop()
{
  // Read ESP-B Sensor Data
  Read_ESP_B();

  uint32_t current_time = millis();

  if (current_time - prev_time >= 1000)
  {
    prev_time = current_time;

    SendTo_LVGL("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%s,%s\n",
                SensorData.Solar_Voltage,
                SensorData.Solar_Current,
                SensorData.Wind_Voltage,
                SensorData.Wind_Current,
                SensorData.WindSpeed_ms,
                SensorData.WindSpeed_kph,
                SensorData.Wind_Direction,
                SensorData.Battery_Voltage,
                SensorData.Battery_Percentage,
                SensorData.PZEM_A_Voltage,
                SensorData.PZEM_A_Current,
                SensorData.PZEM_A_Power,
                SensorData.PZEM_A_Energy,
                SensorData.PZEM_A_Frequency,
                SensorData.PZEM_A_PowerFactor,
                SensorData.PZEM_B_Voltage,
                SensorData.PZEM_B_Current,
                SensorData.PZEM_B_Power,
                SensorData.PZEM_B_Energy,
                SensorData.PZEM_B_Frequency,
                SensorData.PZEM_B_PowerFactor,
                SensorData.PZEM_C_Voltage,
                SensorData.PZEM_C_Current,
                SensorData.PZEM_C_Power,
                SensorData.PZEM_C_Energy,
                SensorData.PZEM_C_Frequency,
                SensorData.PZEM_C_PowerFactor,
                SensorData.RTC_Date,
                SensorData.RTC_Time);
  }

  // Create a function to send SMS 
  // Low Batt = 20%
  // High power consumption:
}

void Read_ESP_B()
{
  if (Serial1.available())
  {
    String receivedData = Serial1.readStringUntil('\n');

    int startIdx = 0;
    int endIdx = receivedData.indexOf(',');
    SensorData.Solar_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.Solar_Current = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.Wind_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.Wind_Current = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.WindSpeed_ms = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.WindSpeed_kph = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.Wind_Direction = receivedData.substring(startIdx, endIdx).toInt();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.Battery_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.Battery_Percentage = receivedData.substring(startIdx, endIdx).toInt();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_A_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_A_Current = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_A_Power = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_A_Energy = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_A_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_A_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_B_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_B_Current = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_B_Power = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_B_Energy = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_B_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_B_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_C_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_C_Current = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_C_Power = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_C_Energy = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_C_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.PZEM_C_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.RTC_Date = receivedData.substring(startIdx, endIdx);

    startIdx = endIdx + 1;
    endIdx = receivedData.indexOf(',', startIdx);
    SensorData.RTC_Time = receivedData.substring(startIdx, endIdx);
  }
}