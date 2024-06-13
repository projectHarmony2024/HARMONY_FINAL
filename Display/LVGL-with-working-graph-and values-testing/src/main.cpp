/*===========================================================================================
▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
▐ ███████╗███████╗██████╗ ██████╗ ██████╗               ██╗    ██╗   ██╗ ██████╗ ██╗      ▌
▐ ██╔════╝██╔════╝██╔══██╗╚════██╗╚════██╗              ██║    ██║   ██║██╔════╝ ██║      ▌
▐ █████╗  ███████╗██████╔╝ █████╔╝ █████╔╝    █████╗    ██║    ██║   ██║██║  ███╗██║      ▌
▐ ██╔══╝  ╚════██║██╔═══╝  ╚═══██╗██╔═══╝     ╚════╝    ██║    ╚██╗ ██╔╝██║   ██║██║      ▌
▐ ███████╗███████║██║     ██████╔╝███████╗              ███████╗╚████╔╝ ╚██████╔╝███████╗ ▌
▐ ╚══════╝╚══════╝╚═╝     ╚═════╝ ╚══════╝              ╚══════╝ ╚═══╝   ╚═════╝ ╚══════╝ ▌
▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
===========================================================================================*/

#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>

#include <WiFi.h>
#include <esp_now.h>
#include <lvglTextUpdater.h>
#include <sensorStatus.h>
#include <powerConsumptionStatus.h>

#include "chartUpdater.h"
// #include "espNow.h"

/* ------------- VARIABLES -------------*/
// SENSORS DATA TO RECEIVE FROM ESP32-B
struct SmoothedSensorReadingsLCD
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
  String RTC_Timestamp;
  int RTC_TimeInt;
};
SmoothedSensorReadingsLCD SensorDataLCD;

float Solar_Power;
float Wind_Power;
float Total_Power_Consumption;
String windDirection;
String powerStatus;

int id;
/* ------------- END OF VARIABLES -------------*/

/* ------------- FUNCTION DECLARATION ------------- */
void forBatt();
String direction(int);
void facilityStatus(float);
void forLabels();
void forCharts();
void backLight();
void DisplayResult();
/* ------------- END OF FUNCTION DECLARATION ------------- */

/* ------------- RECEIVING DATA USING ESP-NOW ------------*/
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&SensorDataLCD, incomingData, sizeof(SensorDataLCD));
  Serial.print("Bytes received: ");
  Serial.println(len);
  DisplayResult();
}
/*--------------END OF RECEIVING DATA USING ESP-NOW -------------*/

/* ------------- SETUP ------------- */
void setup()
{
  smartdisplay_init();
  auto disp = lv_disp_get_default();
  lv_disp_set_rotation(disp, LV_DISP_ROT_270);
  ui_init();

  Serial.begin(115200);
  // wifiNowSetup();

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
/* ------------- END OF SETUP ------------- */
static uint32_t prev_millis = 0;
/* ------------- LOOP ------------- */
void loop()
{
  // checkWiFiConnection();

  Solar_Power = SensorDataLCD.Solar_Voltage * SensorDataLCD.Solar_Current;
  Wind_Power = SensorDataLCD.Wind_Voltage * SensorDataLCD.Wind_Current;

  sensorStatus(ui_statusBattVoltage, SENSOR_OK);
  uint32_t current_millis = millis();

  if (current_millis - prev_millis >= 1000)
  {
    prev_millis = current_millis;

    forBatt();
    forLabels();
    forCharts();
  }

  backLight();
  lv_timer_handler();
}
/* ------------- END OF LOOP -------------*/

/* ------------- BATTERY -------------*/
int id_time(int current_time)
{
  return current_time / 100;
}

void forBatt()
{
  chartBattUpdate(90, 0);
  chartBattUpdate(SensorDataLCD.Battery_Percentage, 1);
  chartBattUpdate(SensorDataLCD.Battery_Percentage, 2);
  id = id_time(SensorDataLCD.RTC_TimeInt);
  lv_bar_set_value(ui_batteryBar, SensorDataLCD.Battery_Percentage, LV_ANIM_OFF);         // updates battery bar
  lv_label_set_text(ui_batteryPercent, String(SensorDataLCD.Battery_Percentage).c_str()); // updates battery percent label
  // chartBattUpdate(SensorDataLCD.Battery_Percentage, id);                                  // updates battery chart

  // updates chart every hour and resets it every day
  // if (id >= 23)
  // {
  //   id = 0;
  // }
  // else
  // {
  //   // updates id every hour
  //   if (prev_millis >= 3600000)
  //   {
  //     id++;
  //   }
  // }
}

/* ------------- END OF BATTERY -------------*/

/* ------------- LABELS -------------*/
String direction(int windDegrees)
{
  if (windDegrees > 337 || windDegrees <= 25)
  {
    return "N";
  }
  else if (windDegrees > 25 && windDegrees <= 67)
  {
    return "NE";
  }
  else if (windDegrees > 67 && windDegrees <= 112)
  {
    return "E";
  }
  else if (windDegrees > 112 && windDegrees <= 157)
  {
    return "SE";
  }
  else if (windDegrees > 157 && windDegrees <= 202)
  {
    return "S";
  }
  else if (windDegrees > 202 && windDegrees <= 247)
  {
    return "SW";
  }
  else if (windDegrees > 247 && windDegrees <= 292)
  {
    return "W";
  }
  else if (windDegrees > 292 || windDegrees <= 337)
  {
    return "SW";
  }
  else
  {
    return "UKNOWN";
  }
}

void facilityStatus(float totalConsumed)
{
  if (totalConsumed <= 500)
  {
    powerConsumptionStatus(ui_facilitiesStatus, POWER_NORMAL);
    updateLvglText(ui_facilitiesPower, String(totalConsumed).c_str(), TEXT_DEFAULT);
  }
  else if (totalConsumed <= 700)
  {
    powerConsumptionStatus(ui_facilitiesStatus, POWER_WARNING);
    updateLvglText(ui_facilitiesPower, String(totalConsumed).c_str(), TEXT_WARNING);
  }
  else if (totalConsumed <= 800)
  {
    powerConsumptionStatus(ui_facilitiesStatus, POWER_HIGH);
    updateLvglText(ui_facilitiesPower, String(totalConsumed).c_str(), TEXT_HIGH);
  }
  else if (totalConsumed > 801)
  {
    powerConsumptionStatus(ui_facilitiesStatus, POWER_CRITICAL);
    updateLvglText(ui_facilitiesPower, String(totalConsumed).c_str(), TEXT_CRITICAL);
  }
  else
  {
    powerConsumptionStatus(ui_facilitiesStatus, POWER_NORMAL);
    updateLvglText(ui_facilitiesPower, String(totalConsumed).c_str(), TEXT_DEFAULT);
  }
}

void forLabels()
{
  /* ------------- TIME AND DATE ------------- */
  lv_label_set_text(ui_headerDate, String(SensorDataLCD.RTC_Date).c_str());
  lv_label_set_text(ui_headerTime, String(SensorDataLCD.RTC_Time).c_str());

  /* ------------- SOLAR VALUES ------------- */
  lv_label_set_text(ui_solarVoltage, String(SensorDataLCD.Solar_Voltage).c_str());
  lv_label_set_text(ui_solarCurrent, String(SensorDataLCD.Solar_Current).c_str());
  lv_label_set_text(ui_solarPower, String(Solar_Power).c_str());

  /* ------------- WIND VALUES ------------- */
  lv_label_set_text(ui_windVoltage, String(SensorDataLCD.Wind_Voltage).c_str());
  lv_label_set_text(ui_windCurrent, String(SensorDataLCD.Wind_Current).c_str());
  lv_label_set_text(ui_windPower, String(Wind_Power).c_str());

  /* ------------- SOLAR & WIND VALUES ------------- */
  float solarWindVoltage = SensorDataLCD.Solar_Voltage + SensorDataLCD.Wind_Voltage;
  float solarWindCurrent = SensorDataLCD.Solar_Current + SensorDataLCD.Wind_Current;
  float solarWindPower = Solar_Power + Wind_Power;
  lv_label_set_text(ui_solarWindVoltage, String(solarWindVoltage).c_str());
  lv_label_set_text(ui_solarWindCurrent, String(solarWindCurrent).c_str());
  lv_label_set_text(ui_solarWindPower, String(solarWindPower).c_str());

  lv_label_set_text(ui_speedWind, String(SensorDataLCD.WindSpeed_kph).c_str());
  lv_label_set_text(ui_degreesWind, String(SensorDataLCD.Wind_Direction).c_str());
  lv_label_set_text(ui_speedSolarWind, String(SensorDataLCD.WindSpeed_kph).c_str());
  lv_label_set_text(ui_degreesSolarWind, String(SensorDataLCD.Wind_Direction).c_str());

  windDirection = direction(SensorDataLCD.Wind_Direction);

  lv_label_set_text(ui_directionWind, windDirection.c_str());
  lv_label_set_text(ui_directionSolarWind, windDirection.c_str());

  /* ------------- CONSUMPTION VALUES ------------- */
  Total_Power_Consumption = SensorDataLCD.PZEM_A_Power + SensorDataLCD.PZEM_B_Power + SensorDataLCD.PZEM_C_Power;
  facilityStatus(Total_Power_Consumption);
  // for brgy hall
  lv_label_set_text(ui_brgyPower, String(SensorDataLCD.PZEM_A_Power).c_str());
  lv_label_set_text(ui_brgyPower1, String(SensorDataLCD.PZEM_A_Power).c_str());
  lv_label_set_text(ui_brgyEnergy, String(SensorDataLCD.PZEM_A_Energy).c_str());
  lv_label_set_text(ui_brgyFactor, String(SensorDataLCD.PZEM_A_PowerFactor).c_str());
  // for health center
  lv_label_set_text(ui_healthPower, String(SensorDataLCD.PZEM_B_Power).c_str());
  lv_label_set_text(ui_healthPower1, String(SensorDataLCD.PZEM_B_Power).c_str());
  lv_label_set_text(ui_healthEnergy, String(SensorDataLCD.PZEM_B_Energy).c_str());
  lv_label_set_text(ui_healthFactor, String(SensorDataLCD.PZEM_B_PowerFactor).c_str());
  // for daycare center
  lv_label_set_text(ui_daycarePower, String(SensorDataLCD.PZEM_C_Power).c_str());
  lv_label_set_text(ui_daycarePower, String(SensorDataLCD.PZEM_C_Power).c_str());
  lv_label_set_text(ui_daycareEnergy, String(SensorDataLCD.PZEM_C_Energy).c_str());
  lv_label_set_text(ui_daycareFactor, String(SensorDataLCD.PZEM_C_PowerFactor).c_str());
}

void forCharts()
{
  chartSolarWindUpdate(1, SensorDataLCD.Solar_Voltage, SensorDataLCD.Solar_Current, Solar_Power);                                                                              // solar voltage, current, power chart
  chartSolarWindUpdate(2, SensorDataLCD.Wind_Voltage, SensorDataLCD.Wind_Current, Wind_Power);                                                                                 // wind voltage, current, power chart
  chartSolarWindUpdate(3, (SensorDataLCD.Solar_Voltage + SensorDataLCD.Wind_Voltage), (SensorDataLCD.Solar_Current + SensorDataLCD.Wind_Current), (Solar_Power + Wind_Power)); // solar and wind voltage, current, power chart

  chartConsumptionUpdate(Total_Power_Consumption, SensorDataLCD.PZEM_A_Power, SensorDataLCD.PZEM_B_Power, SensorDataLCD.PZEM_C_Power); // total consumed brgy hall, health center, daycare chart
}

void backLight()
{
  if (lv_disp_get_inactive_time(NULL) > 15000)
  {
    if (lv_disp_get_inactive_time(NULL) > 30000)
    {
      if (lv_disp_get_inactive_time(NULL) > 60000)
      {
        smartdisplay_lcd_set_backlight(0);
      }
      else
      {
        smartdisplay_lcd_set_backlight(0.01);
      }
    }
    else
    {
      smartdisplay_lcd_set_backlight(0.5);
    }
  }
  else
  {
    smartdisplay_lcd_set_backlight(1);
  }
}

// For Debugging Only
void DisplayResult()
{
  Serial.println("\n=== TIME ===");
  Serial.printf("Date: %s  Time: %s\n", SensorDataLCD.RTC_Date.c_str(), SensorDataLCD.RTC_Time.c_str());
  Serial.println("=== SOLAR ===");
  Serial.printf("Voltage: %0.2f  Current: %0.2f\n", SensorDataLCD.Solar_Voltage, SensorDataLCD.Solar_Current);
  Serial.println("=== WIND ===");
  // Serial.printf("Voltage: %0.2f  Current: %0.2f  Wind Speed: %0.2fkph  Wind Direction: %d\n", SensorData.Wind_Voltage, SensorData.Wind_Current, SensorData.WindSpeed_kph, SensorData.Wind_Direction);
  Serial.printf("Voltage: %0.2f  Current: %0.2f\n", SensorDataLCD.Wind_Voltage, SensorDataLCD.Wind_Current);
  Serial.println("=== BATTERY ===");
  Serial.printf("Voltage: %0.2f  Percentage: %d%\n", SensorDataLCD.Battery_Voltage, SensorDataLCD.Battery_Percentage);
  Serial.println("=== ENERGY CONSUMPTION ===");
  Serial.printf("PZEM-A: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_A_Voltage, SensorDataLCD.PZEM_A_Current, SensorDataLCD.PZEM_A_Power, SensorDataLCD.PZEM_A_Energy, SensorDataLCD.PZEM_A_Frequency, SensorDataLCD.PZEM_A_PowerFactor);
  Serial.printf("PZEM-B: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_B_Voltage, SensorDataLCD.PZEM_B_Current, SensorDataLCD.PZEM_B_Power, SensorDataLCD.PZEM_B_Energy, SensorDataLCD.PZEM_B_Frequency, SensorDataLCD.PZEM_B_PowerFactor);
  Serial.printf("PZEM-C: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_C_Voltage, SensorDataLCD.PZEM_C_Current, SensorDataLCD.PZEM_C_Power, SensorDataLCD.PZEM_C_Energy, SensorDataLCD.PZEM_C_Frequency, SensorDataLCD.PZEM_C_PowerFactor);
  Serial.printf("Wind Speed: %0.2f  Wind Direction: %d\n", SensorDataLCD.WindSpeed_kph, SensorDataLCD.Wind_Direction);
  Serial.println(SensorDataLCD.RTC_TimeInt);
  Serial.println(id);
}