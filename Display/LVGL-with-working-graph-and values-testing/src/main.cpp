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

#include <lvglTextUpdater.h>
#include <sensorStatus.h>
#include <powerConsumptionStatus.h>

#include "chartUpdater.h"

#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

// static const char *ssid = "realme 3 Pro";
// static const char *password = "rafrafraf";

/* ------------- VARIABLES -------------*/
// SENSORS DATA TO RECEIVE FROM ESP32-B
typedef struct SensorsData
{
  float SolarVoltage;
  float SolarCurrent;

  float WindVoltage;
  float WindCurrent;
  float WindSpeed_MS;
  int WindDirection;

  float BatteryVoltage;
  float BatteryPercentage;

  float brgyVoltage;
  float brgyCurrent;
  float brgyPower;
  float brgyEnergy;
  float brgyPowerFactor;

  float healthVoltage;
  float healthCurrent;
  float healthPower;
  float heatlhEnergy;
  float healthPowerFactor;

  float daycareVoltage;
  float daycareCurrent;
  float daycarePower;
  float daycareEnergy;
  float daycarePowerFactor;

  String time;
  String date;
  int hour;
  // Add more fields if needed
} SensorsData;
SensorsData sensorsData;

float checkNaN(float value)
{
  if (isnan(value))
  {
    return 0;
  }
  return value;
}

float Solar_Power;
float Wind_Power;
float Total_Power_Consumption;
String windDirection;
String powerStatus;
/* ------------- END OF VARIABLES -------------*/

/* ------------- FUNCTION DECLARATION ------------- */
void sensorPage();
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
  memcpy(&sensorsData, incomingData, sizeof(sensorsData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%s,%s,%d\n",
                sensorsData.SolarVoltage,
                sensorsData.SolarCurrent,
                sensorsData.WindVoltage,
                sensorsData.WindCurrent,
                sensorsData.WindSpeed_MS,
                sensorsData.WindDirection,
                sensorsData.BatteryVoltage,
                sensorsData.BatteryPercentage,
                sensorsData.brgyVoltage,
                sensorsData.brgyCurrent,
                sensorsData.brgyPower,
                sensorsData.brgyEnergy,
                sensorsData.brgyPowerFactor,
                sensorsData.healthVoltage,
                sensorsData.healthCurrent,
                sensorsData.healthPower,
                sensorsData.heatlhEnergy,
                sensorsData.healthPowerFactor,
                sensorsData.daycareVoltage,
                sensorsData.daycareCurrent,
                sensorsData.daycarePower,
                sensorsData.daycareEnergy,
                sensorsData.daycarePowerFactor,
                sensorsData.time,
                sensorsData.date,
                sensorsData.hour);
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

  WiFi.mode(WIFI_STA);
  // WiFi.mode(WIFI_AP_STA);
  // WiFi.setSleep(false);
  // WiFi.begin(ssid, password);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
/* ------------- END OF SETUP ------------- */
static uint32_t prev_millis = 0;
/* ------------- LOOP ------------- */
void loop()
{
  sensorPage();
  Solar_Power = sensorsData.SolarVoltage * sensorsData.SolarCurrent;
  Wind_Power = sensorsData.WindVoltage * sensorsData.WindCurrent;
  if (isnan(sensorsData.brgyPower))
  {
    sensorsData.brgyPower = 0;
  }
  if (isnan(sensorsData.healthPower))
  {
    sensorsData.healthPower = 0;
  }
  if (isnan(sensorsData.daycarePower))
  {
    sensorsData.daycarePower = 0;
  }
  Total_Power_Consumption = checkNaN(sensorsData.brgyPower) + checkNaN(sensorsData.healthPower) + checkNaN(sensorsData.daycarePower);

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
void forBatt()
{
  int battPercent = (int)sensorsData.BatteryPercentage;
  chartBattUpdate(battPercent, sensorsData.hour);
  lv_bar_set_value(ui_batteryBar, battPercent, LV_ANIM_OFF);         // updates battery bar
  lv_label_set_text(ui_batteryPercent, String(battPercent).c_str()); // updates battery percent label
  if (battPercent >= 0)
  {
    sensorStatus(ui_statusBattVoltage, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusBattVoltage, SENSOR_ERROR);
  }
}

/* ------------- END OF BATTERY -------------*/

void sensorPage()
{
  // Solar Current
  if (!isnan(sensorsData.SolarCurrent))
  {
    sensorStatus(ui_statusSolarCurrent, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusSolarCurrent, SENSOR_ERROR);
  }
  // Wind Current
  if (!isnan(sensorsData.WindCurrent))
  {
    sensorStatus(ui_statusWindCurrent, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusWindCurrent, SENSOR_ERROR);
  }
  // Solar Voltage
  if (!isnan(sensorsData.SolarVoltage))
  {
    sensorStatus(ui_statusSolarVoltage, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusSolarVoltage, SENSOR_ERROR);
  }
  // Wind Voltage
  if (!isnan(sensorsData.WindVoltage))
  {
    sensorStatus(ui_statusWindVoltage, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusWindVoltage, SENSOR_ERROR);
  }
  // Battery Voltage
  if (!isnan(sensorsData.BatteryVoltage))
  {
    sensorStatus(ui_statusBattVoltage, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusBattVoltage, SENSOR_ERROR);
  }
  // Anemometer
  if (!isnan(sensorsData.WindSpeed_MS))
  {
    sensorStatus(ui_statusAnemo, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusAnemo, SENSOR_ERROR);
  }
  // PZEM Brgy Hall
  if (!isnan(sensorsData.brgyPower))
  {
    sensorStatus(ui_statusPzemA, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusPzemA, SENSOR_UNAVAILABLE);
  }
  // PZEM Health Center
  if (!isnan(sensorsData.healthPower))
  {
    sensorStatus(ui_statusPzemB, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusPzemB, SENSOR_UNAVAILABLE);
  }
  // PZEM Daycare
  if (!isnan(sensorsData.daycarePower))
  {
    sensorStatus(ui_statusPzemC, SENSOR_OK);
  }
  else
  {
    sensorStatus(ui_statusPzemC, SENSOR_UNAVAILABLE);
  }
  // GSM Module
  sensorStatus(ui_statusSim, SENSOR_NOT_CONNECTED);
  // WIFI
  sensorStatus(ui_statusWifi, SENSOR_CONNECTED);
  // MICRO SD CARD
  sensorStatus(ui_statusCard, SENSOR_CONNECTED);
}

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
    return "UNKNOWN";
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
  else if (totalConsumed > 900)
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
  lv_label_set_text(ui_headerDate, String(sensorsData.date).c_str());
  lv_label_set_text(ui_headerTime, String(sensorsData.time).c_str());

  /* ------------- SOLAR VALUES ------------- */
  lv_label_set_text(ui_solarVoltage, String(sensorsData.SolarVoltage).c_str());
  lv_label_set_text(ui_solarCurrent, String(sensorsData.SolarCurrent).c_str());
  lv_label_set_text(ui_solarPower, String(Solar_Power).c_str());

  /* ------------- WIND VALUES ------------- */
  lv_label_set_text(ui_windVoltage, String(sensorsData.WindVoltage).c_str());
  lv_label_set_text(ui_windCurrent, String(sensorsData.WindCurrent).c_str());
  lv_label_set_text(ui_windPower, String(Wind_Power).c_str());

  lv_label_set_text(ui_speedWind, String(sensorsData.WindSpeed_MS).c_str());
  lv_label_set_text(ui_degreesWind, String(sensorsData.WindDirection).c_str());

  /* ------------- SOLAR & WIND VALUES ------------- */
  float solarWindVoltage = sensorsData.SolarVoltage + sensorsData.WindVoltage;
  float solarWindCurrent = sensorsData.SolarCurrent + sensorsData.SolarCurrent;
  float solarWindPower = Solar_Power + Wind_Power;
  lv_label_set_text(ui_solarWindVoltage, String(solarWindVoltage).c_str());
  lv_label_set_text(ui_solarWindCurrent, String(solarWindCurrent).c_str());
  lv_label_set_text(ui_solarWindPower, String(solarWindPower).c_str());

  lv_label_set_text(ui_speedSolarWind, String(sensorsData.WindSpeed_MS).c_str());
  lv_label_set_text(ui_degreesSolarWind, String(sensorsData.WindDirection).c_str());

  windDirection = direction(sensorsData.WindDirection);

  lv_label_set_text(ui_directionWind, windDirection.c_str());
  lv_label_set_text(ui_directionSolarWind, windDirection.c_str());

  /* ------------- CONSUMPTION VALUES ------------- */
  Total_Power_Consumption = sensorsData.brgyPower + sensorsData.healthPower + sensorsData.daycarePower;
  facilityStatus(Total_Power_Consumption);
  // for brgy hall
  lv_label_set_text(ui_brgyPower, String(sensorsData.brgyPower).c_str());
  lv_label_set_text(ui_brgyPower1, String(sensorsData.brgyPower).c_str());
  lv_label_set_text(ui_brgyEnergy, String(sensorsData.brgyEnergy).c_str());
  lv_label_set_text(ui_brgyFactor, String(sensorsData.brgyPowerFactor).c_str());
  // for health center
  lv_label_set_text(ui_healthPower, String(sensorsData.healthPower).c_str());
  lv_label_set_text(ui_healthPower1, String(sensorsData.healthPower).c_str());
  lv_label_set_text(ui_healthEnergy, String(sensorsData.heatlhEnergy).c_str());
  lv_label_set_text(ui_healthFactor, String(sensorsData.healthPowerFactor).c_str());
  // for daycare center
  lv_label_set_text(ui_daycarePower, String(sensorsData.daycarePower).c_str());
  lv_label_set_text(ui_daycarePower1, String(sensorsData.daycarePower).c_str());
  lv_label_set_text(ui_daycareEnergy, String(sensorsData.daycareEnergy).c_str());
  lv_label_set_text(ui_daycareFactor, String(sensorsData.daycarePowerFactor).c_str());
}

void forCharts()
{
  chartSolarWindUpdate(1, sensorsData.SolarVoltage, sensorsData.SolarCurrent, Solar_Power);                                                                        // solar voltage, current, power chart
  chartSolarWindUpdate(2, sensorsData.WindVoltage, sensorsData.WindCurrent, Wind_Power);                                                                           // wind voltage, current, power chart
  chartSolarWindUpdate(3, (sensorsData.SolarVoltage + sensorsData.WindVoltage), (sensorsData.SolarCurrent + sensorsData.WindCurrent), (Solar_Power + Wind_Power)); // solar and wind voltage, current, power chart

  chartConsumptionUpdate(Total_Power_Consumption, sensorsData.brgyPower, sensorsData.healthPower, sensorsData.daycarePower); // total consumed brgy hall, health center, daycare chart
}

void backLight()
{
  if (lv_disp_get_inactive_time(NULL) > 60000)
  {
    if (lv_disp_get_inactive_time(NULL) > 90000)
    {
      if (lv_disp_get_inactive_time(NULL) > 120000)
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