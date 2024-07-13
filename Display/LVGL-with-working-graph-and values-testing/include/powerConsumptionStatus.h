#include <Arduino.h>
#include <ui/ui.h>
#include <map>
#include <esp32_smartdisplay.h>
#include <WiFi.h>

enum PowerConsumptionState
{
    POWER_NORMAL,
    POWER_WARNING,
    POWER_HIGH,
    POWER_CRITICAL
};

// Define the structure for the value type stored in the map
struct PowerStatusData
{
    const char *text;
    uint32_t color;
    std::array<uint8_t, 3> rgb;
};

std::map<PowerConsumptionState, PowerStatusData> powerStatusMap = {
    {POWER_NORMAL, {"NORMAL", 0x2DA041, {0, 1, 0}}},
    {POWER_WARNING, {"WARNING", 0xFFC841, {1, 1, 0}}},
    {POWER_HIGH, {"HIGH", 0xFF41E2, {1, 0, 1}}},
    {POWER_CRITICAL, {"CRITICAL!", 0xEA3030, {1, 0, 0}}}};

void powerConsumptionStatus(lv_obj_t *ui_object, PowerConsumptionState powerState)
{
    const auto &statusData = powerStatusMap[powerState];
    if (ui_object != nullptr)
    {

        lv_label_set_text(ui_object, statusData.text);
        lv_obj_set_style_text_color(ui_object, lv_color_hex(statusData.color), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}
