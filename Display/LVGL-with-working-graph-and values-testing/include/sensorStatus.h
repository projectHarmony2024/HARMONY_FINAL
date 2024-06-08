#include <Arduino.h>
#include <ui/ui.h>
#include <map>

enum SensorState
{
    SENSOR_OK,
    SENSOR_CONNECTED,
    SENSOR_UNAVAILABLE,
    SENSOR_NOT_CONNECTED,
    SENSOR_ERROR
};

std::map<SensorState, std::pair<const char *, uint32_t>> statusMap = {
    {SENSOR_OK, {"OK", 0x8ac926}},
    {SENSOR_CONNECTED, {"CONNECTED", 0x8ac926}},
    {SENSOR_UNAVAILABLE, {"UNAVAILABLE", 0xffcf00}}, 
    {SENSOR_NOT_CONNECTED, {"NOT CONNECTED", 0xee6123}},
    {SENSOR_ERROR, {"ERROR!", 0xfa003f}}
};

void sensorStatus(lv_obj_t *ui_object, SensorState sensorState)
{
    if (ui_object != nullptr)
    {
        const auto &statusData = statusMap[sensorState];
        lv_label_set_text(ui_object, statusData.first);
        lv_obj_set_style_text_color(ui_object, lv_color_hex(statusData.second), LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}
