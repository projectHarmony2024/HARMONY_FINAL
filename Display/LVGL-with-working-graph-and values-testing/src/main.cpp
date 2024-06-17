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
#include <WiFi.h>

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
  // Add more fields if needed
} SensorsData;
SensorsData sensorsData;

float Solar_Power;
float Wind_Power;
float Total_Power_Consumption = sensorsData.brgyPower + sensorsData.healthPower + sensorsData.daycarePower;
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
  memcpy(&sensorsData, incomingData, sizeof(sensorsData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f\n",
                sensorsData.SolarVoltage,
                sensorsData.SolarCurrent,
                sensorsData.WindVoltage,
                sensorsData.WindCurrent,
                sensorsData.WindSpeed_MS,
                sensorsData.WindDirection,
                sensorsData.BatteryVoltage,
                sensorsData.BatteryPercentage);
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
  // checkWiFiConnection();

  Solar_Power = sensorsData.SolarVoltage * sensorsData.SolarCurrent;
  Wind_Power = sensorsData.WindVoltage * sensorsData.WindCurrent;

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
  chartBattUpdate(sensorsData.BatteryPercentage, 1);
  chartBattUpdate(sensorsData.BatteryPercentage, 2);
  // id = id_time(SensorDataLCD.RTC_TimeInt);
  lv_bar_set_value(ui_batteryBar, sensorsData.BatteryPercentage, LV_ANIM_OFF);         // updates battery bar
  lv_label_set_text(ui_batteryPercent, String(sensorsData.BatteryPercentage).c_str()); // updates battery percent label
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
  // lv_label_set_text(ui_headerDate, String(SensorDataLCD.RTC_Date).c_str());
  // lv_label_set_text(ui_headerTime, String(SensorDataLCD.RTC_Time).c_str());

  /* ------------- SOLAR VALUES ------------- */
  lv_label_set_text(ui_solarVoltage, String(sensorsData.SolarVoltage).c_str());
  lv_label_set_text(ui_solarCurrent, String(sensorsData.SolarCurrent).c_str());
  lv_label_set_text(ui_solarPower, String(Solar_Power).c_str());

  /* ------------- WIND VALUES ------------- */
  lv_label_set_text(ui_windVoltage, String(sensorsData.WindVoltage).c_str());
  lv_label_set_text(ui_windCurrent, String(sensorsData.WindCurrent).c_str());
  lv_label_set_text(ui_windPower, String(Wind_Power).c_str());

  lv_label_set_text(ui_speedWind, String(sensorsData.WindSpeed_MS * 3.6).c_str());
  lv_label_set_text(ui_degreesWind, String(sensorsData.WindDirection).c_str());

  /* ------------- SOLAR & WIND VALUES ------------- */
  float solarWindVoltage = sensorsData.SolarVoltage + sensorsData.WindVoltage;
  float solarWindCurrent = sensorsData.SolarCurrent + sensorsData.SolarCurrent;
  float solarWindPower = Solar_Power + Wind_Power;
  lv_label_set_text(ui_solarWindVoltage, String(solarWindVoltage).c_str());
  lv_label_set_text(ui_solarWindCurrent, String(solarWindCurrent).c_str());
  lv_label_set_text(ui_solarWindPower, String(solarWindPower).c_str());

  lv_label_set_text(ui_speedSolarWind, String(sensorsData.WindSpeed_MS * 3.6).c_str());
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
  lv_label_set_text(ui_daycarePower, String(sensorsData.daycarePower).c_str());
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
// void DisplayResult()
// {
//   Serial.println("\n=== TIME ===");
//   Serial.printf("Date: %s  Time: %s\n", sensorsData.date.c_str(), sensorsData.time.c_str());
//   Serial.println("=== SOLAR ===");
//   Serial.printf("Voltage: %0.2f  Current: %0.2f\n", sensorsData.SolarVoltage, sensorsData.SolarCurrent);
//   Serial.println("=== WIND ===");
//   Serial.printf("Voltage: %0.2f  Current: %0.2f  Wind Speed: %0.2fkph  Wind Direction: %d\n", sensorsData.WindVoltage, sensorsData.WindCurrent, round(sensorsData.WindSpeed_MS * 3.6, 2), sensorsData.WindDirection);
//   Serial.println("=== BATTERY ===");
//   Serial.printf("Voltage: %0.2f  Percentage: %d%\n", SensorDataLCD.Battery_Voltage, SensorDataLCD.Battery_Percentage);
//   Serial.println("=== ENERGY CONSUMPTION ===");
//   Serial.printf("PZEM-A: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_A_Voltage, SensorDataLCD.PZEM_A_Current, SensorDataLCD.PZEM_A_Power, SensorDataLCD.PZEM_A_Energy, SensorDataLCD.PZEM_A_Frequency, SensorDataLCD.PZEM_A_PowerFactor);
//   Serial.printf("PZEM-B: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_B_Voltage, SensorDataLCD.PZEM_B_Current, SensorDataLCD.PZEM_B_Power, SensorDataLCD.PZEM_B_Energy, SensorDataLCD.PZEM_B_Frequency, SensorDataLCD.PZEM_B_PowerFactor);
//   Serial.printf("PZEM-C: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_C_Voltage, SensorDataLCD.PZEM_C_Current, SensorDataLCD.PZEM_C_Power, SensorDataLCD.PZEM_C_Energy, SensorDataLCD.PZEM_C_Frequency, SensorDataLCD.PZEM_C_PowerFactor);
//   Serial.printf("Wind Speed: %0.2f  Wind Direction: %d\n", SensorDataLCD.WindSpeed_kph, SensorDataLCD.Wind_Direction);
//   Serial.println(SensorDataLCD.RTC_TimeInt);
//   Serial.println(id);
// }