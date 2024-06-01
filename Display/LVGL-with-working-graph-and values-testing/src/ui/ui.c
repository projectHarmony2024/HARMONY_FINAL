// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: MonitoringUI

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_headerNotification;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_headerDate;
lv_obj_t * ui_headerTime;
lv_obj_t * ui_TabView1;
lv_obj_t * ui_SolarPage;
lv_obj_t * ui_Container1;
lv_obj_t * ui_Side2;
lv_obj_t * ui_widgetParamater3;
lv_obj_t * ui_basePanel3;
lv_obj_t * ui_solarVoltage;
lv_obj_t * ui_labelUnit3;
lv_obj_t * ui_labelTitle3;
lv_obj_t * ui_widgetParamater4;
lv_obj_t * ui_basePanel4;
lv_obj_t * ui_solarCurrent;
lv_obj_t * ui_labelUnit4;
lv_obj_t * ui_labelTitle4;
lv_obj_t * ui_widgetParamater5;
lv_obj_t * ui_basePanel5;
lv_obj_t * ui_solarPower;
lv_obj_t * ui_labelUnit5;
lv_obj_t * ui_labelTitle5;
lv_obj_t * ui_Container2;
lv_obj_t * ui_chartSolarVC;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Container3;
lv_obj_t * ui_chartSolarPower;
lv_obj_t * ui_WindPage;
lv_obj_t * ui_Container25;
lv_obj_t * ui_Side3;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Container23;
lv_obj_t * ui_speedWind;
lv_obj_t * ui_Label44;
lv_obj_t * ui_Side8;
lv_obj_t * ui_Label45;
lv_obj_t * ui_Container24;
lv_obj_t * ui_degreesWind;
lv_obj_t * ui_directionWind;
lv_obj_t * ui_Container4;
lv_obj_t * ui_Side1;
lv_obj_t * ui_widgetParamater;
lv_obj_t * ui_basePanel;
lv_obj_t * ui_windVoltage;
lv_obj_t * ui_labelUnit;
lv_obj_t * ui_labelTitle;
lv_obj_t * ui_widgetParamater1;
lv_obj_t * ui_basePanel1;
lv_obj_t * ui_windCurrent;
lv_obj_t * ui_labelUnit1;
lv_obj_t * ui_labelTitle1;
lv_obj_t * ui_widgetParamater2;
lv_obj_t * ui_basePanel2;
lv_obj_t * ui_windPower;
lv_obj_t * ui_labelUnit2;
lv_obj_t * ui_labelTitle2;
lv_obj_t * ui_Container6;
lv_obj_t * ui_chartWindVC;
lv_obj_t * ui_Label12;
lv_obj_t * ui_Container5;
lv_obj_t * ui_chartWindPower;
lv_obj_t * ui_SolarWindPage;
lv_obj_t * ui_Container29;
lv_obj_t * ui_Side5;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Container26;
lv_obj_t * ui_speedSolarWind;
lv_obj_t * ui_Label59;
lv_obj_t * ui_Side9;
lv_obj_t * ui_Label60;
lv_obj_t * ui_Container27;
lv_obj_t * ui_degreesSolarWind;
lv_obj_t * ui_directionSolarWind;
lv_obj_t * ui_Container7;
lv_obj_t * ui_Side4;
lv_obj_t * ui_widgetParamater7;
lv_obj_t * ui_basePanel10;
lv_obj_t * ui_solarWindVoltage;
lv_obj_t * ui_labelUnit9;
lv_obj_t * ui_labelTitle7;
lv_obj_t * ui_widgetParamater9;
lv_obj_t * ui_basePanel11;
lv_obj_t * ui_solarWindCurrent;
lv_obj_t * ui_labelUnit10;
lv_obj_t * ui_labelTitle9;
lv_obj_t * ui_widgetParamater10;
lv_obj_t * ui_basePanel12;
lv_obj_t * ui_solarWindPower;
lv_obj_t * ui_labelUnit11;
lv_obj_t * ui_labelTitle10;
lv_obj_t * ui_Container8;
lv_obj_t * ui_chartSolarWindVC;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Container9;
lv_obj_t * ui_chartSolarWindPower;
lv_obj_t * ui_BatteryPage;
lv_obj_t * ui_Container22;
lv_obj_t * ui_batteryBar;
lv_obj_t * ui_batteryPercent;
lv_obj_t * ui_percentIcon;
lv_obj_t * ui_Container21;
lv_obj_t * ui_chartBattery;
lv_obj_t * ui_ConsumptionPage;
lv_obj_t * ui_Side7;
lv_obj_t * ui_widgetParamater14;
lv_obj_t * ui_basePanel18;
lv_obj_t * ui_facilitiesPower;
lv_obj_t * ui_labelUnit18;
lv_obj_t * ui_labelTitle14;
lv_obj_t * ui_widgetParamater13;
lv_obj_t * ui_statusPanel;
lv_obj_t * ui_facilitiesStatus;
lv_obj_t * ui_labelTitle13;
lv_obj_t * ui_Container10;
lv_obj_t * ui_chartPower;
lv_obj_t * ui_Label26;
lv_obj_t * ui_legendsContainer1;
lv_obj_t * ui_Container14;
lv_obj_t * ui_Label29;
lv_obj_t * ui_legends1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Container30;
lv_obj_t * ui_brgyPower1;
lv_obj_t * ui_unit1;
lv_obj_t * ui_legends5;
lv_obj_t * ui_Label32;
lv_obj_t * ui_Container28;
lv_obj_t * ui_healthPower1;
lv_obj_t * ui_unit;
lv_obj_t * ui_legends2;
lv_obj_t * ui_label2;
lv_obj_t * ui_Container31;
lv_obj_t * ui_daycarePower1;
lv_obj_t * ui_unit2;
lv_obj_t * ui_Container13;
lv_obj_t * ui_chartFacilities;
lv_obj_t * ui_TabView2;
lv_obj_t * ui_TabPage1;
lv_obj_t * ui_Container16;
lv_obj_t * ui_Label21;
lv_obj_t * ui_Label22;
lv_obj_t * ui_Label23;
lv_obj_t * ui_Container19;
lv_obj_t * ui_brgyPower;
lv_obj_t * ui_brgyFreq;
lv_obj_t * ui_brgyFactor;
lv_obj_t * ui_TabPage2;
lv_obj_t * ui_Container11;
lv_obj_t * ui_Label28;
lv_obj_t * ui_Label30;
lv_obj_t * ui_Label34;
lv_obj_t * ui_Container17;
lv_obj_t * ui_healthPower;
lv_obj_t * ui_healthFreq;
lv_obj_t * ui_healthFactor;
lv_obj_t * ui_TabPage3;
lv_obj_t * ui_Container18;
lv_obj_t * ui_Label38;
lv_obj_t * ui_Label39;
lv_obj_t * ui_Label40;
lv_obj_t * ui_Container20;
lv_obj_t * ui_daycarePower;
lv_obj_t * ui_daycareFreq;
lv_obj_t * ui_daycareFactor;
lv_obj_t * ui_SensorPage;
lv_obj_t * ui_Container12;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Label7;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Label13;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Label14;
lv_obj_t * ui_Label15;
lv_obj_t * ui_Label16;
lv_obj_t * ui_Label19;
lv_obj_t * ui_Label18;
lv_obj_t * ui_Label17;
lv_obj_t * ui_Container15;
lv_obj_t * ui_statusSolarCurrent;
lv_obj_t * ui_statusWindCurrent;
lv_obj_t * ui_statusSolarVoltage;
lv_obj_t * ui_statusWindVoltage;
lv_obj_t * ui_statusBattVoltage;
lv_obj_t * ui_statusAnemo;
lv_obj_t * ui_statusPzemA;
lv_obj_t * ui_statusPzemB;
lv_obj_t * ui_statusPzemC;
lv_obj_t * ui_statusSim;
lv_obj_t * ui_statusWifi;
lv_obj_t * ui_statusCard;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}