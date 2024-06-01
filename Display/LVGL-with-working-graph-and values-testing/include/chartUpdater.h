#include <Arduino.h>
#include <ui/ui.h>

// SET COLOR OF CHART POINTS HERE ----------------------
lv_color_t voltageColor = lv_color_hex(0x8ECAE6);
lv_color_t currentColor = lv_color_hex(0xF6AE2D);
lv_color_t powerColor = lv_color_hex(0x9AC6C5);
lv_color_t battColor = lv_color_hex(0xAFFC41);
lv_color_t brgyColor = lv_color_hex(0x4A98FE);
lv_color_t healthColor = lv_color_hex(0xF6B639);
lv_color_t daycareColor = lv_color_hex(0x9CC6C5);

// FOR SOLAR AND WIND CHARTS ---------------------------
void chartVC(lv_obj_t *chartName, lv_chart_series_t *&chartSeriesV, lv_chart_series_t *&chartSeriesC, double vValue, double cValue)
{
    if (chartSeriesV == nullptr && chartSeriesC == nullptr)
    {
        chartSeriesV = lv_chart_add_series(chartName, voltageColor, LV_CHART_AXIS_PRIMARY_Y);
        chartSeriesC = lv_chart_add_series(chartName, currentColor, LV_CHART_AXIS_PRIMARY_Y);
    }

    lv_chart_set_next_value(chartName, chartSeriesV, vValue);
    lv_chart_set_next_value(chartName, chartSeriesC, cValue);
}

void chartPWR(lv_obj_t *chartName, lv_chart_series_t *&chartSeriesPWR, double pValue)
{
    if (chartSeriesPWR == nullptr)
    {
        chartSeriesPWR = lv_chart_add_series(chartName, powerColor, LV_CHART_AXIS_PRIMARY_Y);
    }

    lv_chart_set_next_value(chartName, chartSeriesPWR, pValue);
}

void chartSolarWindUpdate(int index, double vValue, double cValue, double pValue)
{
    switch (index)
    {
    case 1: // solar voltage, current, power chart
        static lv_chart_series_t *solarVSeries = nullptr;
        static lv_chart_series_t *solarCSeries = nullptr;
        static lv_chart_series_t *solarPWRSeries = nullptr;
        chartVC(ui_chartSolarVC, solarVSeries, solarCSeries, vValue, cValue);
        chartPWR(ui_chartSolarPower, solarPWRSeries, pValue);
        break;
    case 2: // wind voltage, current, power chart
        static lv_chart_series_t *windVSeries = nullptr;
        static lv_chart_series_t *windCSeries = nullptr;
        static lv_chart_series_t *windPWRSeries = nullptr;
        chartVC(ui_chartWindVC, windVSeries, windCSeries, vValue, cValue);
        chartPWR(ui_chartWindPower, windPWRSeries, pValue);
        break;
    case 3: // solar and wind voltage, current, power, chart
        static lv_chart_series_t *solarwindVSeries = nullptr;
        static lv_chart_series_t *solarwindCSeries = nullptr;
        static lv_chart_series_t *solarwindPWRSeries = nullptr;
        chartVC(ui_chartSolarWindVC, solarwindVSeries, solarwindCSeries, vValue, cValue);
        chartPWR(ui_chartSolarWindPower, solarwindPWRSeries, pValue);
        break;
    }
}

// FOR FACILITIES CHART ---------------------------------
void chartTotal(lv_obj_t *chartName, lv_chart_series_t *&chartSeries, double tValue)
{
    if (chartSeries == nullptr)
    {
        chartSeries = lv_chart_add_series(chartName, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
    }

    lv_chart_set_next_value(chartName, chartSeries, tValue);
}

void chartFacilities(lv_obj_t *chartName, lv_chart_series_t *&chartBSeries, lv_chart_series_t *&chartHSeries, lv_chart_series_t *&chartDSeries, double bValue, double hValue, double dValue)
{
    if (chartBSeries == nullptr && chartHSeries == nullptr && chartDSeries == nullptr)
    {
        chartBSeries = lv_chart_add_series(chartName, brgyColor, LV_CHART_AXIS_PRIMARY_Y);
        chartHSeries = lv_chart_add_series(chartName, healthColor, LV_CHART_AXIS_PRIMARY_Y);
        chartDSeries = lv_chart_add_series(chartName, daycareColor, LV_CHART_AXIS_PRIMARY_Y);
    }

    lv_chart_set_next_value(chartName, chartBSeries, bValue);
    lv_chart_set_next_value(chartName, chartHSeries, hValue);
    lv_chart_set_next_value(chartName, chartDSeries, dValue);
}

void chartConsumptionUpdate(double tValue, double bValue, double hValue, double dValue)
{
    static lv_chart_series_t *total = nullptr;
    static lv_chart_series_t *chartBSeries = nullptr;
    static lv_chart_series_t *chartHSeries = nullptr;
    static lv_chart_series_t *chartDSeries = nullptr;

    chartTotal(ui_chartPower, total, tValue);
    chartFacilities(ui_chartFacilities, chartBSeries, chartHSeries, chartDSeries, bValue, hValue, dValue);
}

// FOR BATTERY CHART ------------------------------------
void chartBatt(lv_obj_t *chartName, lv_chart_series_t *&chartSeries, int value, int id)
{
    if (chartSeries == nullptr)
    {
        chartSeries = lv_chart_add_series(chartName, battColor, LV_CHART_AXIS_PRIMARY_Y);
    }

    if (id == 0)
    {
        lv_chart_set_all_value(chartName, chartSeries, 0);
    }

    lv_chart_set_value_by_id(chartName, chartSeries, id, value);
}

void chartBattUpdate(int value, int id)
{
    static lv_chart_series_t *battSeries = nullptr;

    chartBatt(ui_chartBattery, battSeries, value, id);
}
