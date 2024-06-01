#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>

#include <WiFi.h>
#include <lvglTextUpdater.h>
#include <sensorStatus.h>
#include <powerConsumptionStatus.h>

#include "chartUpdater.h"
#include "espNow.h"

/* ------------- VARIABLES -------------*/
double solarPower;
double windPower;
double solarWindVoltage;
double solarWindCurrent;
double solarWindPower;
double totalConsumed;

String windDirection;
String powerStatus;

int id = 0;
/* ------------- END OF VARIABLES -------------*/

/* ------------- FUNCTION DECLARATION ------------- */
void forBatt();
String direction(double);
void facilityStatus(double);
void forLabels();
void forCharts();
void backLight();
/* ------------- END OF FUNCTION DECLARATION ------------- */

/* ------------- SETUP ------------- */
void setup()
{
  smartdisplay_init();
  auto disp = lv_disp_get_default();
  lv_disp_set_rotation(disp, LV_DISP_ROT_90);
  ui_init();
  Serial.begin(115200);
  wifiNowSetup();
}
/* ------------- END OF SETUP ------------- */

/* ------------- LOOP ------------- */
void loop()
{
  checkWiFiConnection();

  sensorStatus(ui_statusBattVoltage, SENSOR_ERROR);
  static uint32_t prev_millis = 0;
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
  lv_bar_set_value(ui_batteryBar, battPercent, LV_ANIM_OFF);         // updates battery bar
  lv_label_set_text(ui_batteryPercent, String(battPercent).c_str()); // updates battery percent label
  chartBattUpdate(battPercent, id);                                  // updates battery chart

  // updates chart every hour and resets it every day
  if (id >= 23)
  {
    id = 0;
  }
  else
  {
    id++;
  }
}
/* ------------- END OF BATTERY -------------*/

/* ------------- LABELS -------------*/
String direction(double windDegrees)
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

void facilityStatus(double totalConsumed)
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
  /* ------------- SOLAR VALUES ------------- */
  solarPower = solarVoltage * solarCurrent;
  lv_label_set_text(ui_solarVoltage, String(solarVoltage).c_str());
  lv_label_set_text(ui_solarCurrent, String(solarCurrent).c_str());
  lv_label_set_text(ui_solarPower, String(solarPower).c_str());

  /* ------------- WIND VALUES ------------- */
  windPower = windVoltage * windCurrent;
  lv_label_set_text(ui_windVoltage, String(windVoltage).c_str());
  lv_label_set_text(ui_windCurrent, String(windCurrent).c_str());
  lv_label_set_text(ui_windPower, String(windPower).c_str());

  /* ------------- SOLAR & WIND VALUES ------------- */
  solarWindVoltage = solarVoltage + windVoltage;
  solarWindCurrent = solarCurrent + windCurrent;
  solarWindPower = solarWindVoltage * solarWindCurrent;
  lv_label_set_text(ui_solarWindVoltage, String(solarWindVoltage).c_str());
  lv_label_set_text(ui_solarWindCurrent, String(solarWindCurrent).c_str());
  lv_label_set_text(ui_solarWindPower, String(solarWindPower).c_str());

  lv_label_set_text(ui_speedWind, String(windSpeed).c_str());
  lv_label_set_text(ui_degreesWind, String(windDegrees).c_str());
  lv_label_set_text(ui_speedSolarWind, String(windSpeed).c_str());
  lv_label_set_text(ui_degreesSolarWind, String(windDegrees).c_str());

  windDirection = direction(windDegrees);

  lv_label_set_text(ui_directionWind, windDirection.c_str());
  lv_label_set_text(ui_directionSolarWind, windDirection.c_str());

  /* ------------- CONSUMPTION VALUES ------------- */
  totalConsumed = brgyHall[0] + healthCenter[0] + daycare[0];
  facilityStatus(totalConsumed);
  // for brgy hall
  lv_label_set_text(ui_brgyPower, String(brgyHall[0]).c_str());
  lv_label_set_text(ui_brgyPower1, String(brgyHall[0]).c_str());
  lv_label_set_text(ui_brgyFreq, String(brgyHall[1]).c_str());
  lv_label_set_text(ui_brgyFactor, String(brgyHall[2]).c_str());
  // for health center
  lv_label_set_text(ui_healthPower, String(healthCenter[0]).c_str());
  lv_label_set_text(ui_healthPower1, String(healthCenter[0]).c_str());
  lv_label_set_text(ui_healthFreq, String(healthCenter[1]).c_str());
  lv_label_set_text(ui_healthFactor, String(healthCenter[2]).c_str());
  // for daycare center
  lv_label_set_text(ui_daycarePower, String(daycare[0]).c_str());
  lv_label_set_text(ui_daycarePower, String(daycare[0]).c_str());
  lv_label_set_text(ui_daycareFreq, String(daycare[1]).c_str());
  lv_label_set_text(ui_daycareFactor, String(daycare[2]).c_str());
}

void forCharts()
{
  chartSolarWindUpdate(1, solarVoltage, solarCurrent, solarPower);             // solar voltage, current, power chart
  chartSolarWindUpdate(2, windVoltage, windCurrent, windPower);                // wind voltage, current, power chart
  chartSolarWindUpdate(3, solarWindVoltage, solarWindCurrent, solarWindPower); // solar and wind voltage, current, power chart

  chartConsumptionUpdate(totalConsumed, brgyHall[0], healthCenter[0], daycare[0]); // total consumed brgy hall, health center, daycare chart
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
