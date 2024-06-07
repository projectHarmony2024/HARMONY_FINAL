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
#include <lvglTextUpdater.h>
#include <sensorStatus.h>
#include <powerConsumptionStatus.h>

#include "chartUpdater.h"
#include "espNow.h"

/* ------------- VARIABLES -------------*/
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

  float Solar_Power;
  float Wind_Power;

  float Total_Power_Consumption;
  float Toal_Energy_Consumption;
};

SmoothedSensorReadings SensorData;

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
  lv_disp_set_rotation(disp, LV_DISP_ROT_270);
  ui_init();

  Serial2.begin(115200, SERIAL_8N1, 35, 22);

  Serial.begin(115200, SERIAL_8N1);
  wifiNowSetup();
}
/* ------------- END OF SETUP ------------- */

/* ------------- LOOP ------------- */
void loop()
{
  checkWiFiConnection();

  if (Serial2.available())
  {
    String receivedData = Serial2.readStringUntil('\n');

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

  SensorData.Solar_Power = SensorData.Solar_Voltage * SensorData.Solar_Current;
  SensorData.Wind_Power = SensorData.Wind_Voltage * SensorData.Wind_Current;

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
  lv_bar_set_value(ui_batteryBar, SensorData.Battery_Percentage, LV_ANIM_OFF);         // updates battery bar
  lv_label_set_text(ui_batteryPercent, String(SensorData.Battery_Percentage).c_str()); // updates battery percent label
  chartBattUpdate(SensorData.Battery_Percentage, id);                                  // updates battery chart

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
  lv_label_set_text(ui_headerDate, String(SensorData.RTC_Date).c_str());
  lv_label_set_text(ui_headerTime, String(SensorData.RTC_Time).c_str());

  /* ------------- SOLAR VALUES ------------- */
  lv_label_set_text(ui_solarVoltage, String(SensorData.Solar_Voltage).c_str());
  lv_label_set_text(ui_solarCurrent, String(SensorData.Solar_Current).c_str());
  lv_label_set_text(ui_solarPower, String(SensorData.Solar_Power).c_str());

  /* ------------- WIND VALUES ------------- */
  lv_label_set_text(ui_windVoltage, String(SensorData.Wind_Voltage).c_str());
  lv_label_set_text(ui_windCurrent, String(SensorData.Wind_Current).c_str());
  lv_label_set_text(ui_windPower, String(SensorData.Wind_Power).c_str());

  /* ------------- SOLAR & WIND VALUES ------------- */
  float solarWindVoltage = SensorData.Solar_Voltage + SensorData.Solar_Current;
  float solarWindCurrent = SensorData.Solar_Current + SensorData.Wind_Current;
  float solarWindPower = SensorData.Solar_Power + SensorData.Wind_Power;
  lv_label_set_text(ui_solarWindVoltage, String(solarWindVoltage).c_str());
  lv_label_set_text(ui_solarWindCurrent, String(solarWindCurrent).c_str());
  lv_label_set_text(ui_solarWindPower, String(solarWindPower).c_str());

  lv_label_set_text(ui_speedWind, String(SensorData.WindSpeed_kph).c_str());
  lv_label_set_text(ui_degreesWind, String(SensorData.Wind_Direction).c_str());
  lv_label_set_text(ui_speedSolarWind, String(SensorData.WindSpeed_kph).c_str());
  lv_label_set_text(ui_degreesSolarWind, String(SensorData.Wind_Direction).c_str());

  windDirection = direction(SensorData.Wind_Direction);

  lv_label_set_text(ui_directionWind, windDirection.c_str());
  lv_label_set_text(ui_directionSolarWind, windDirection.c_str());

  /* ------------- CONSUMPTION VALUES ------------- */
  SensorData.Total_Power_Consumption = SensorData.PZEM_A_Power + SensorData.PZEM_B_Power + SensorData.PZEM_C_Power;
  facilityStatus(SensorData.Total_Power_Consumption);
  // for brgy hall
  lv_label_set_text(ui_brgyPower, String(SensorData.PZEM_A_Power).c_str());
  lv_label_set_text(ui_brgyPower1, String(SensorData.PZEM_A_Power).c_str());
  lv_label_set_text(ui_brgyEnergy, String(SensorData.PZEM_A_Energy).c_str());
  lv_label_set_text(ui_brgyFactor, String(SensorData.PZEM_A_PowerFactor).c_str());
  // for health center
  lv_label_set_text(ui_healthPower, String(SensorData.PZEM_B_Power).c_str());
  lv_label_set_text(ui_healthPower1, String(SensorData.PZEM_B_Power).c_str());
  lv_label_set_text(ui_healthEnergy, String(SensorData.PZEM_B_Energy).c_str());
  lv_label_set_text(ui_healthFactor, String(SensorData.PZEM_B_PowerFactor).c_str());
  // for daycare center
  lv_label_set_text(ui_daycarePower, String(SensorData.PZEM_C_Power).c_str());
  lv_label_set_text(ui_daycarePower, String(SensorData.PZEM_C_Power).c_str());
  lv_label_set_text(ui_daycareEnergy, String(SensorData.PZEM_C_Energy).c_str());
  lv_label_set_text(ui_daycareFactor, String(SensorData.PZEM_C_PowerFactor).c_str());
}

void forCharts()
{
  chartSolarWindUpdate(1, SensorData.Solar_Voltage, SensorData.Solar_Current, SensorData.Solar_Power);                                                                                   // solar voltage, current, power chart
  chartSolarWindUpdate(2, SensorData.Wind_Voltage, SensorData.Wind_Current, SensorData.Wind_Power);                                                                                      // wind voltage, current, power chart
  chartSolarWindUpdate(3, (SensorData.Solar_Voltage + SensorData.Wind_Voltage), (SensorData.Solar_Current + SensorData.Wind_Current), (SensorData.Solar_Power + SensorData.Wind_Power)); // solar and wind voltage, current, power chart

  chartConsumptionUpdate(SensorData.Total_Power_Consumption, SensorData.PZEM_A_Power, SensorData.PZEM_B_Power, SensorData.PZEM_C_Power); // total consumed brgy hall, health center, daycare chart
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
